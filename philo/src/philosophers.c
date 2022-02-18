/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfernand <nfernand@student.42kl.edu.m      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 10:32:15 by nfernand          #+#    #+#             */
/*   Updated: 2022/02/18 10:33:18 by nfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	philosophers(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philos)
	{
		if (pthread_create(&data->philo[i].thread_id, NULL,
				routine, &(data->philo[i])))
			return (1);
		data->philo[i].time_since_meal = get_time();
		i++;
	}
	data->started = 1;
	check_death(data);
	terminate_data(data);
	return (0);
}
