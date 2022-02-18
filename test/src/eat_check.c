/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfernand <nfernand@student.42kl.edu.m      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 11:10:58 by nfernand          #+#    #+#             */
/*   Updated: 2022/02/18 11:11:16 by nfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

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
