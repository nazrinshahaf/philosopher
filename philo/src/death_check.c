/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfernand <nfernand@student.42kl.edu.m      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 10:04:00 by nfernand          #+#    #+#             */
/*   Updated: 2022/02/18 10:17:37 by nfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	handle_death(t_data *data, int i)
{
	pthread_mutex_lock(&(data->philo[i].eating));
	print_action(data, 5, data->philo[i].id);
	data->dead = 1;
	pthread_mutex_unlock(&(data->philo[i].eating));
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
			if ((current_time - data->philo[i].time_since_meal)
				>= data->time_to_die
				&& (data->philo[i].eat_count != data->no_of_eat))
				handle_death(data, i);
			if (data->dead == 1 || all_eat(data) == 1)
				break ;
			usleep(10);
			i++;
		}
		if (data->dead == 1 || all_eat(data) == 1)
			break ;
	}
}

/**
 *	printf("all_eat = %d\n", all_eat(data));
 *	printf("philo = %d\n", data->philo[i].id);
 *	printf("eat count = %d\n", data->philo[i].eat_count);
 *	printf("current time = 		%ld\n", current_time);
 *
 *	printf("time since last meal = 	%ld\n", 
 *	(long)data->philo[i].time_since_meal);
 *
 *	printf("elapsed time  = 		  %ld\n",
 *	(long)(current_time - data->philo[i].time_since_meal));
 *
 *	printf("philo = %d IS DEAD\n", data->philo[i].id);
**/
