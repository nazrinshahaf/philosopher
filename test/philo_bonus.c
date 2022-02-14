/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfernand <nfernand@student.42kl.edu.m      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 10:43:28 by nfernand          #+#    #+#             */
/*   Updated: 2022/02/14 19:07:33 by nfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philo_bonus.h"

typedef struct s_data t_data;

typedef struct	s_philo
{
	int			id;
	long		time_since_meal;
	int			eat_count;
	int			eat_lock;
	pid_t		ph_pid;
	sem_t		*eat_count_sem;
	sem_t		*eating;
	t_data		*data;
}				t_philo;

typedef struct	s_data
{
	int			number_of_philos;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			no_of_eat;
	long		start_time;
	t_philo		philo[250];
	sem_t		*forks;
	sem_t		*dead;
	sem_t		*print;
	sem_t		*print_dead;
	sem_t		*sync;
}				t_data;

long	get_time()
{
	struct timeval	t;
	long int	time;

	gettimeofday(&t, NULL);
	time = t.tv_sec;
	time = (time * 1000) + (t.tv_usec / 1000);
	return (time);
}

void	custom_sleep(int time)
{
	long int	start;
	long int	end;

	start = get_time();
	while (1)
	{
		end = get_time();
		if ((end - start) >= time)
			break;
		usleep(500);
	}
}

void	print_rules(t_data *data)
{
	printf(GREEN "number of philosopher(s) = \t[%d]\n", data->number_of_philos);
	printf("time to die = \t\t\t[%d ms]\n", data->time_to_die);
	printf("time to eat = \t\t\t[%d ms]\n", data->time_to_eat);
	printf("time to sleep = \t\t[%d ms]\n", data->time_to_sleep);
	if (data->no_of_eat == -1)
		printf("number of eat = \t\t[∞]\n");
	else
		printf("number of eat = \t\t[%d]\n", data->no_of_eat);
	printf("start time = \t\t\t[%ld]\n\n" RESET, get_time());
}

void	init_philosophers(t_data *data)
{
	int	i;
	int	temp;

	i = 0;
	while (i < data->number_of_philos)
	{
		data->philo[i].id = i;
		data->philo[i].time_since_meal = 0;
		data->philo[i].data = data;
		data->philo[i].eat_count = 0;
		data->philo[i].eat_lock = 0;
		i++;
	}
}

void	init_semaphores(t_data *data)
{
	int		i;
	char	*str;

	i = 0;
	sem_unlink("/forks_sem");
	sem_unlink("/dead_sem");
	sem_unlink("/print_sem");
	sem_unlink("/printdead_sem");
	sem_unlink("/sync_sem");
	data->forks = sem_open("/forks_sem", O_CREAT, S_IRWXU, data->number_of_philos);
	data->dead = sem_open("/dead_sem", O_CREAT, S_IRWXU, 0);
	data->print = sem_open("/print_sem", O_CREAT, S_IRWXU, 1);
	data->print_dead = sem_open("/printdead_sem", O_CREAT, S_IRWXU, 1);
	data->sync = sem_open("/sync_sem", O_CREAT, S_IRWXU, 0);
	while (i < data->number_of_philos)
	{
		str = ft_strjoin("/eating_sem", ft_itoa(i));
		sem_unlink(str);
		data->philo[i].eating = sem_open(str, O_CREAT, S_IRWXU, 1);
		str = ft_strjoin("/eatcount_sem", ft_itoa(i));
		sem_unlink(str);
		data->philo[i].eat_count_sem = sem_open(str, O_CREAT, S_IRWXU, 0);
		i++;
	}
}

int	init_data(t_data *data, int argc, char **argv)
{
	data->number_of_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
//	if (data->time_to_die <= 0 || data->number_of_philos <= 0
//			|| data->time_to_eat < 0 || data->time_to_sleep < 0
//			|| data->number_of_philos >= 201)
//		return (1);
	if (argc == 6)
	{
		data->no_of_eat = ft_atoi(argv[5]);
		if (data->no_of_eat <= 0)
			return (1);
	}
	else
		data->no_of_eat = -1;
	init_philosophers(data);
	init_semaphores(data);
	return (0);
}

void	print_action(t_data *data, int action, int id)
{
	sem_wait(data->print);
	sem_wait(data->print_dead);
	if (action == 1)
		printf(BLUE "%ld %d has taken a fork\n" RESET, get_time(), id);
	else if (action == 2)
		printf(MAGENTA "%ld %d is eating\n" RESET, get_time(), id);
	else if (action == 3)
		printf(CYAN "%ld %d is sleeping\n" RESET, get_time(), id);
	else if (action == 4)
		printf(YELLOW "%ld %d is thinking\n" RESET, get_time(), id);
	else if (action == 5)
		printf(RED "%ld %d died\n" RESET, get_time(), id);
	if (action < 5)
		sem_post(data->print_dead);
	sem_post(data->print);
}

void	handle_eat(t_philo *philo)
{
	sem_wait(philo->data->forks);
	print_action(philo->data, 1, philo->id);
	sem_wait(philo->data->forks);
	print_action(philo->data, 1, philo->id);

	sem_wait(philo->eating);
	philo->eat_lock = 1;
	print_action(philo->data, 2, philo->id);
	philo->eat_count++;
	philo->time_since_meal = get_time();
	custom_sleep(philo->data->time_to_eat);
	philo->eat_lock = 0;
	sem_post(philo->eating);
	//printf("%ld %d let go of fork\n", get_time(), philo->id);

	sem_post(philo->eat_count_sem);
	sem_post(philo->data->forks);
	sem_post(philo->data->forks);
}

void	handle_sleep(t_philo *philo)
{
	print_action(philo->data, 3, philo->id);
	custom_sleep(philo->data->time_to_sleep);
}

void	*death_check(void *void_philo)
{
	t_philo	*philo;
	t_data	*d;
	long	current_time;

	philo = (t_philo *)void_philo;
	d = philo->data;
	while (1)
	{
		current_time = get_time();
		sem_wait(philo->eating);
		if (current_time - philo->time_since_meal >= d->time_to_die && !philo->eat_lock)
		{
			print_action(philo->data, 5, philo->id);
			sem_post(philo->eating);
			sem_post(d->dead);
			printf(RESET "===========================\n");
			printf("philo = %d\n", philo->id);
			printf("eat count = %d\n", philo->eat_count);
			printf("current time = 		%ld\n", current_time);
			printf("time since last meal = 	%ld\n", (long)philo->time_since_meal);
			printf("elapsed time  = 		  %ld\n", (long)(current_time - philo->time_since_meal));
			printf("philo = %d IS DEAD\n", philo->id);
			printf(RESET"===========================\n"RESET);
			return (NULL);
		}
		sem_post(philo->eating);
		usleep(1000);
		//custom_sleep(10);
	}
	return (NULL);
}

void	*eat_check(void *void_data)
{
	t_data	*d;
	int		i;
	int		j;

	d = (t_data *)void_data;
	i = 0;
	while (i < d->no_of_eat)
	{
		j = 0;
		while (j < d->number_of_philos)
			sem_wait(d->philo[j++].eat_count_sem);
		i++;
	}
	sem_post(d->dead);
	return (NULL);
}

void	routine(t_philo *philo)
{
	pthread_t	death_tid;
	t_data		*d;

	d = (t_data *)philo->data;
	sem_wait(philo->data->sync);
	philo->time_since_meal = get_time();
	//printf("%ld %d entered\n", philo->time_since_meal, philo->id);
	if (pthread_create(&death_tid, NULL, &death_check, (void *)philo))
		return ;
	pthread_detach(death_tid);
	if (philo->id % 2)
		custom_sleep(d->time_to_eat / 2);
	while (1)
	{
		if (d->no_of_eat > 0 && philo->eat_count >= d->no_of_eat)
			break ;
		handle_eat(philo);
		handle_sleep(philo);
		print_action(philo->data, 4, philo->id);
	}
}

void	philosophers(t_data *data)
{
	int			i;
	int			status;
	//pthread_t	eat_tid;

	i = 0;
	//if (data->no_of_eat > 0)
	//{
	//	pthread_create(&eat_tid, NULL, &eat_check, (void *)data);
	//	pthread_detach(eat_tid);
	//}
	while (i < data->number_of_philos)
	{
		data->philo[i].ph_pid = fork();
		if (data->philo[i].ph_pid == 0)
		{
			routine(&(data->philo[i]));
			exit(0);
		}
		else if (data->philo[i].ph_pid < 0)
			printf("Error with forking\n");
		i++;
	}
	i = 0;
	while (i++ < data->number_of_philos)
		sem_post(data->sync);
	i = 0;
	sem_wait(data->dead);
	//printf(RED "%ld entered kill()\n" RESET, get_time());
	while (i < data->number_of_philos)
		kill(data->philo[i++].ph_pid, SIGKILL);
		//waitpid(data->philo[i++].ph_pid, &status, 0);
}

int	main(int argc, char **argv)
{
	t_data	data;
	pthread_t	eat_tid;

	if (argc > 6 || argc < 5)
	{
		printf(GREEN "\"./philo [no_of_philos] [time_to_die] ");
		printf("[time_to_eat] [time_to_sleep] ");
		printf(CYAN "[no_of_times_philos_must_eat]"GREEN"\"\n" RESET);
		return (0);
	}
	init_data(&data, argc, argv);
	print_rules(&data);
	if (data.no_of_eat > 0)
	{
		pthread_create(&eat_tid, NULL, &eat_check, (void *)&data);
		pthread_detach(eat_tid);
	}
	philosophers(&data);
}
