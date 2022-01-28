/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfernand <nfernand@student.42kl.edu.m      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 10:43:28 by nfernand          #+#    #+#             */
/*   Updated: 2022/01/28 16:30:33 by nfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philo_bonus.h"

typedef struct s_data t_data;

typedef struct	s_philo
{
	int			id;
	long		time_since_meal;
	int			right_fork_id;
	int			left_fork_id;
	int			eat_count;
	pid_t		pid_id;
	t_data		*data;
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
	t_philo		philo[250];
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
		data->philo[i].left_fork_id = i;
		if (i == 0)
			data->philo[i].right_fork_id = data->number_of_philos - 1;
		else
			data->philo[i].right_fork_id = i - 1;
		if (i % 2 != 0)
		{
			temp = data->philo[i].left_fork_id;
			data->philo[i].left_fork_id = data->philo[i].right_fork_id;
			data->philo[i].right_fork_id = temp;
		}
		data->philo[i].eat_count = 0;
		data->philo[i].data = data;
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
//	if (init_mutex(data))
//		return (2);
	return (0);
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
}
