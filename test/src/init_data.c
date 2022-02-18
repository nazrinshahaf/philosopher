/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfernand <nfernand@student.42kl.edu.m      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 10:47:12 by nfernand          #+#    #+#             */
/*   Updated: 2022/02/18 11:15:10 by nfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

static void	init_philosophers(t_data *data)
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
		data->philo[i].is_eating = 0;
		i++;
	}
}

static void	init_semaphores_philo(t_data *data)
{
	char	*str;
	int		i;

	i = 0;
	while (i < data->number_of_philos)
	{
		str = ft_strjoin("/eating_sem", ft_itoa(i));
		sem_unlink(str);
		data->philo[i].eating_lock = sem_open(str, O_CREAT, S_IRWXU, 1);
		str = ft_strjoin("/eatcount_sem", ft_itoa(i));
		sem_unlink(str);
		data->philo[i].eat_count_sem = sem_open(str, O_CREAT, S_IRWXU, 0);
		i++;
	}
}

static void	init_semaphores(t_data *data)
{
	sem_unlink("/forks_sem");
	sem_unlink("/dead_sem");
	sem_unlink("/print_sem");
	sem_unlink("/printdead_sem");
	sem_unlink("/sync_sem");
	data->forks = sem_open("/forks_sem", O_CREAT,
			S_IRWXU, data->number_of_philos);
	data->dead = sem_open("/dead_sem", O_CREAT, S_IRWXU, 0);
	data->print = sem_open("/print_sem", O_CREAT, S_IRWXU, 1);
	data->print_dead = sem_open("/printdead_sem", O_CREAT, S_IRWXU, 1);
	data->sync = sem_open("/sync_sem", O_CREAT, S_IRWXU, 0);
	init_semaphores_philo(data);
}

static int	init_arg(t_data *data, int argc, char **argv)
{
	data->number_of_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if ((data->time_to_die < 0 || data->time_to_die > INT_MAX)
		|| (data->number_of_philos <= 0 || data->number_of_philos > 200)
		|| (data->time_to_eat < 0 || data->time_to_eat > INT_MAX)
		|| (data->time_to_sleep <= 0 || data->time_to_sleep > INT_MAX))
		return (1);
	if (argc == 6)
	{
		data->no_of_eat = ft_atoi(argv[5]);
		if (data->no_of_eat <= 0)
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
	init_semaphores(data);
	return (0);
}
