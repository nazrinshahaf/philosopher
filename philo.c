/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfernand <nfernand@student.42kl.edu.m      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 10:51:33 by nfernand          #+#    #+#             */
/*   Updated: 2022/01/24 11:48:45 by nfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philo.h"

void	init_mutex(t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_init(&(data->print), NULL);
	while (i < data->number_of_philos)
	{
		pthread_mutex_init(&(data->forks[i]), NULL);
		pthread_mutex_init(&(data->philo[i].eating), NULL);
		i++;
	}
}

void	init_philosophers(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philos)
	{
		data->philo[i].id = i;
		data->philo[i].time_till_death = data->time_to_die;
		data->philo[i].time_since_meal = 0;
		data->philo[i].left_fork_id = i;
		if (i == 0)
			data->philo[i].right_fork_id = data->number_of_philos - 1;
		else
			data->philo[i].right_fork_id = i - 1;
		data->philo[i].eat_count = 0;
		data->philo[i].data = data;
		i++;
	}
}

void	init_data(t_data *data, int argc, char **argv)
{
	data->number_of_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->no_of_eat = ft_atoi(argv[5]);
	else
		data->no_of_eat = -1;
	data->dead = 0;
	init_philosophers(data);
	init_mutex(data);
}

void	print_rules(t_data *data)
{
	printf(GREEN "number of philosophers = %d\n", data->number_of_philos);
	printf("time to die = %d\n", data->time_to_die);
	printf("time to eat = %d\n", data->time_to_eat);
	printf("time to sleep = %d\n", data->time_to_sleep);
	printf("number of eat = %d\n\n" RESET, data->no_of_eat);
}

void	print_philo(t_data *data, int philo_id)
{
	printf(MAGENTA "philosophers id = %d\n", data->philo[philo_id].id);
	printf("time till death = %ld\n", data->philo[philo_id].time_till_death);
	printf("time since meal = %ld\n", data->philo[philo_id].time_since_meal);
	printf("right fork id = %d\n", data->philo[philo_id].right_fork_id);
	printf("left fork id = %d\n\n", data->philo[philo_id].left_fork_id);
	printf("eat count = %d\n\n", data->philo[philo_id].eat_count);
}

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
		usleep(1);
	}
}

void	print_action(t_data *data, int action, int id)
{
	pthread_mutex_lock(&(data->print));
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
	pthread_mutex_unlock(&(data->print));
}

void	handle_eat(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&(philo->data->forks[philo->left_fork_id]));
		print_action(philo->data, 1, philo->id);
		pthread_mutex_lock(&(philo->data->forks[philo->right_fork_id]));
		print_action(philo->data, 1, philo->id);
	}
	else
	{
		pthread_mutex_lock(&(philo->data->forks[philo->right_fork_id]));
		print_action(philo->data, 1, philo->id);
		pthread_mutex_lock(&(philo->data->forks[philo->left_fork_id]));
		print_action(philo->data, 1, philo->id);
	}
	pthread_mutex_lock(&(philo->eating));
	philo->time_since_meal = get_time();
	print_action(philo->data, 2, philo->id);
	custom_sleep(philo->data->time_to_eat);
	philo->eat_count++;
	pthread_mutex_unlock(&(philo->eating));
	pthread_mutex_unlock(&(philo->data->forks[philo->left_fork_id]));
	pthread_mutex_unlock(&(philo->data->forks[philo->right_fork_id]));
}

void	handle_sleep(t_philo *philo)
{
	print_action(philo->data, 3, philo->id);
	custom_sleep(philo->data->time_to_sleep);
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

void	*routine(void *void_philo)
{
	t_philo	*philo;
	t_data	*d;

	philo = (t_philo *)void_philo;
	d = (t_data *)philo->data;
	// in the case of 3 philos all 3 might pick up a fork at the same time so i delay it || not sure if i need this
	//if (philo->data->number_of_philos % 2 == 1 && philo->id % 2)
	//	custom_sleep(1);
	//check for philo death or finish status
	while (philo->data->dead == 0)
	{
		handle_eat(philo);
		if (all_eat(philo->data) == 1 || philo->eat_count == d->no_of_eat)
			break ;
		handle_sleep(philo);
		print_action(philo->data, 4, philo->id);
	}
	return (NULL);
}

void	check_death(t_data *data)
{
	int		i;
	long	current_time;

	while (all_eat(data) == 0)
	{
		i = 0;
		while (i < data->number_of_philos && data->dead == 0)
		{
			current_time = get_time();
			pthread_mutex_lock(&(data->philo[i].eating));
			if ((current_time - data->philo[i].time_since_meal) >= 
					data->time_to_die && (data->philo[i].eat_count != data->no_of_eat))
			{
				printf("all_eat = %d\n", all_eat(data));
				printf("philo = %d\n", data->philo[i].id);
				printf("eat count = %d\n", data->philo[i].eat_count);
				printf("current time = 		%ld\n", current_time);
				printf("time since last meal = 	%ld\n", (long)data->philo[i].time_since_meal);
				printf("elapsed time  = 		  %ld\n", (long)(current_time - data->philo[i].time_since_meal));
				printf("philo = %d IS DAED\n", data->philo[i].id);
				print_action(data, 5, data->philo[i].id);
				data->dead = 1;
			}
			pthread_mutex_unlock(&(data->philo[i].eating));
			usleep(100);
			i++;
		}
		if (data->dead == 1)
			break ;
	}
}

void	terminate_data(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philos)
	{
		pthread_join(data->philo[i].thread_id, NULL);
		i++;
	}
	i = 0;
	while (i < data->number_of_philos)
	{
		pthread_mutex_destroy(&(data->philo[i].eating));
		pthread_mutex_destroy(&(data->forks[i]));
		i++;
	}
	pthread_mutex_destroy(&(data->print));
	pthread_exit(NULL);
}

void	philosophers(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philos)
	{
		pthread_create(&data->philo[i].thread_id, NULL, routine, &(data->philo[i]));
		data->philo[i].time_since_meal = get_time();
		i++;
	}
	check_death(data);
	terminate_data(data);
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
	return (0);
}
