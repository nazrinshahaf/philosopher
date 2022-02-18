/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfernand <nfernand@student.42kl.edu.m      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 09:57:00 by nfernand          #+#    #+#             */
/*   Updated: 2022/02/18 10:01:57 by nfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	init_mutex(t_data *data)
{
	int	i;

	i = 0;
	if (pthread_mutex_init(&(data->print), NULL))
		return (1);
	while (i < data->number_of_philos)
	{
		if (pthread_mutex_init(&(data->forks[i]), NULL))
			return (1);
		if (pthread_mutex_init(&(data->philo[i].eating), NULL))
			return (1);
		i++;
	}
	return (0);
}

static void	init_philosophers(t_data *data)
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

static int	init_arg(t_data *data, int argc, char **argv)
{
	data->number_of_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->started = 0;
	data->dead = 0;
	if ((data->time_to_die < 0 || data->time_to_die > INT_MAX)
		|| (data->number_of_philos <= 0 || data->number_of_philos > 200)
		|| (data->time_to_eat < 0 || data->time_to_eat > INT_MAX)
		|| (data->time_to_sleep <= 0 || data->time_to_sleep > INT_MAX))
		return (1);
	if (argc == 6)
	{
		data->no_of_eat = ft_atoi(argv[5]);
		if (data->no_of_eat <= 0 || data->no_of_eat > INT_MAX)
			return (1);
	}
	else
		data->no_of_eat = -1;
	return (0);
}

int	init_data(t_data *data, int argc, char **argv)
{
	if (init_arg(data, argc, argv))
		return (1);
	init_philosophers(data);
	if (init_mutex(data))
		return (2);
	return (0);
}
