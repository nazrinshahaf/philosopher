/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfernand <nfernand@student.42kl.edu.m      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 11:25:05 by nfernand          #+#    #+#             */
/*   Updated: 2022/02/18 12:21:34 by nfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

int	philosophers(t_data *data)
{
	int			i;
	int			status;

	i = 0;
	while (i < data->number_of_philos)
	{
		data->philo[i].ph_pid = fork();
		if (data->philo[i].ph_pid < 0)
			printf("Error with forking\n");
		else if (data->philo[i].ph_pid == 0)
		{
			routine(&(data->philo[i]));
			exit(0);
		}
		usleep(100);
		i++;
	}
	i = 0;
	while (i++ < data->number_of_philos)
		sem_post(data->sync);
	i = 0;
	return (0);
}
