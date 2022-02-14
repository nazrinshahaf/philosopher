/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfernand <nfernand@student.42kl.edu.m      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 10:43:28 by nfernand          #+#    #+#             */
/*   Updated: 2022/02/08 11:45:56 by nfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philo_bonus.h"

typedef struct s_data t_data;

typedef struct	s_philo
{
	int			id;
	long		time_since_meal;
	int			eat_count;
	pid_t		ph_pid;
	pthread_t	death_tid;
	t_data		*data;
	sem_t		*eating;
}				t_philo;

typedef struct	s_data
{
	int			number_of_philos;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			no_of_eat;
	int			dead;
	long		start_time;
	pid_t		prg_pid;
	t_philo		philo[250];
	sem_t		*all_eat;
	sem_t		*forks;
	sem_t		*print;
	sem_t		*death;
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
		data->philo[i].eat_count = 0;
		data->philo[i].data = data;
		i++;
	}
}

void	init_semaphores(t_data *data)
{
	int		i;
	char	*name;

	i = 0;
	sem_unlink("/forks_sem");
	sem_unlink("/print_sem");
	sem_unlink("/death_sem");
	sem_unlink("/alleat_sem");
	//S_IRWXU read, write, execute permissions for user.
	data->forks = sem_open("/forks_sem", O_CREAT, S_IRWXU, data->number_of_philos);
	data->print = sem_open("/print_sem", O_CREAT, S_IRWXU, 1);
	data->death = sem_open("/death_sem", O_CREAT, S_IRWXU, 0);
	data->all_eat = sem_open("/alleat_sem", O_CREAT, S_IRWXU, data->number_of_philos);
	while (i < data->number_of_philos)
	{
		name = ft_strjoin("/eating_sem", ft_itoa(i));
		sem_unlink(name);
		data->philo[i].eating = sem_open(name, O_CREAT, S_IRWXU, 1);
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
	data->dead = 0;
	init_philosophers(data);
	init_semaphores(data);
	return (0);
}

void	print_action(t_data *data, int action, int id)
{
	sem_wait(data->print);
	if (data->dead == 0)
	{
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
	}
	sem_post(data->print);
}

int	all_eat(t_data *data)
{
	int i;

	i = 0;
	while (i < data->number_of_philos)
	{
		if (data->philo[i].eat_count != data->no_of_eat)
			return (0);
		i++;
	}
	return (1);
}
void	terminate_programs(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philos)
	{
		kill(data->philo[i].ph_pid, SIGKILL);
		i++;
	}
}

void	*check_death(void *void_philo)
{
	long	current_time;
	t_philo	*philo;
	t_data	*d;

	philo = (t_philo *)void_philo;
	d = (t_data *)philo->data;
	while (d->dead == 0)
	{
		current_time = get_time();	
		sem_wait(philo->eating);
		if ((current_time - philo->time_since_meal) >= d->time_to_die)
		{
			print_action(philo->data, 5, philo->id);
			d->dead = 1;
			sem_post(d->death);
			sem_post(philo->eating);
			printf(RESET "===========================\n");
			//printf("all_eat = %d\n", all_eat(d));
			printf("dead = %d\n", d->dead);
			printf("philo = %d\n", philo->id);
			printf("eat count = %d\n", philo->eat_count);
			printf("current time = 		%ld\n", current_time);
			printf("time since last meal = 	%ld\n", (long)philo->time_since_meal);
			printf("elapsed time  = 		  %ld\n", (long)(current_time - philo->time_since_meal));
			printf("philo = %d IS DEAD\n", philo->id);
			printf(RESET"===========================\n"RESET);
			return (NULL);
			//terminate_programs(d);
		}
		sem_post(philo->eating);
		if (d->dead == 1)
			break ;
		custom_sleep(10);
	}
	return (NULL);
}

void	*death_status(void *void_philo)
{
	t_philo	*philo;
	t_data	*d;

	philo = (t_philo *)void_philo;
	d = (t_data *)philo->data;

	printf(GREEN "philo %d waiting\n" RESET, philo->id);
	sem_wait(d->death);
	printf(GREEN "philo %d passed\n" RESET, philo->id);
	terminate_programs(d);
	return (NULL);
}

void	*eat_check(void *void_philo)
{
	t_philo	*philo;
	t_data	*d;

	philo = (t_philo *)void_philo;
	d = (t_data *)philo->data;
	if (philo->eat_count == d->no_of_eat)
		sem_post(d->all_eat);
	sem_post(d->death);
	return (NULL);
}

void	handle_eat(t_philo *philo)
{
	//printf("dead = %d\n", philo->data->dead);
	sem_wait(philo->data->forks);
	print_action(philo->data, 1, philo->id);
	sem_wait(philo->data->forks);
	print_action(philo->data, 1, philo->id);

	sem_wait(philo->eating);
	philo->time_since_meal = get_time();
	print_action(philo->data, 2, philo->id);
	custom_sleep(philo->data->time_to_eat);
	philo->eat_count++;
	sem_post(philo->eating);

	sem_post(philo->data->forks);
	sem_post(philo->data->forks);
}

void	handle_sleep(t_philo *philo)
{
	print_action(philo->data, 3, philo->id);
	custom_sleep(philo->data->time_to_sleep);
}

void	routine(t_philo *philo)
{
	t_data		*d;
	pthread_t	tid;	

	d = (t_data *)philo->data;
	philo->time_since_meal = get_time();
	pthread_create(&philo->death_tid, NULL, check_death, philo);
	pthread_detach(philo->death_tid);
	pthread_create(&tid, NULL, death_status, philo);
	pthread_detach(tid);
	//pthread_create(&tid, NULL, eat_check, philo);
	while (d->dead == 0)
	{
		handle_eat(philo);
		if (philo->eat_count == d->no_of_eat)
			break ;
		handle_sleep(philo);
		print_action(d, 4, philo->id);
	}	
	if (d->dead == 1)
		exit(1);
		//terminate_programs(d);
}

void	philosophers(t_data *data)
{
	int	i;
	int	status;

	i = 0;
	while (i < data->number_of_philos)
	{
		data->philo[i].ph_pid = fork();
		if (data->philo[i].ph_pid == 0)
		{
			//printf("child id = %d parent id = %d\n", getpid(), getppid());
			routine(&(data->philo[i]));
			exit(0);
		}
		if (data->philo[i].ph_pid < 0)
			printf("Error with forking\n");
		i++;
	}
	i = 0;
	while (i < data->number_of_philos)
		waitpid(data->philo[i++].ph_pid, &status, 0);
	//i = 0;
	//printf("waiting %ld\n", get_time());
	//sem_wait(data->death);
	//printf("entered %ld\n", get_time());
	//while (i < data->number_of_philos)
	//	kill(data->philo[i++].ph_pid, SIGKILL);
}

int	main(int argc, char **argv)
{
	t_data	data;
	if (argc > 6 || argc < 5)
	{
		printf(GREEN "\"./philo [no_of_philos] [time_to_die] ");
		printf("[time_to_eat] [time_to_sleep] ");
		printf(CYAN "[no_of_times_philos_must_eat]"GREEN"\"\n" RESET);
		return (0);
	}
	init_data(&data, argc, argv);
	print_rules(&data);
	philosophers(&data);
}
