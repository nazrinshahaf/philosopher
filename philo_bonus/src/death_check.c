/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfernand <nfernand@student.42kl.edu.m      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 11:12:34 by nfernand          #+#    #+#             */
/*   Updated: 2022/02/18 11:14:43 by nfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

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
		sem_wait(philo->eating_lock);
		if (current_time - philo->time_since_meal
			>= d->time_to_die && !philo->is_eating)
		{
			print_action(philo->data, 5, philo->id);
			sem_post(philo->eating_lock);
			sem_post(d->dead);
			return (NULL);
		}
		sem_post(philo->eating_lock);
		custom_sleep(d->time_to_die / 100);
	}
	return (NULL);
}

/**
 *	printf(RESET "===========================\n");
 *	printf("philo = %d\n", philo->id);
 *	printf("eat count = %d\n", philo->eat_count);
 *	printf("current time = 		%ld\n", current_time);
 *
 *	printf("time since last meal = 	%ld\n",
 *	(long)philo->time_since_meal);
 *
 *	printf("elapsed time  = 		  %ld\n",
 *	(long)(current_time - philo->time_since_meal));
 *
 *	printf("philo = %d IS DEAD\n", philo->id);
 *	printf(RESET"===========================\n"RESET);
**/
