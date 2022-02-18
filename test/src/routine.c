/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfernand <nfernand@student.42kl.edu.m      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 11:16:11 by nfernand          #+#    #+#             */
/*   Updated: 2022/02/18 12:21:15 by nfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

static void	handle_eat(t_philo *philo)
{
	sem_wait(philo->data->forks);
	print_action(philo->data, 1, philo->id);
	sem_wait(philo->data->forks);
	print_action(philo->data, 1, philo->id);
	sem_wait(philo->eating_lock);
	philo->is_eating = 1;
	print_action(philo->data, 2, philo->id);
	philo->eat_count++;
	philo->time_since_meal = get_time();
	custom_sleep(philo->data->time_to_eat);
	philo->is_eating = 0;
	sem_post(philo->eating_lock);
	sem_post(philo->eat_count_sem);
	sem_post(philo->data->forks);
	sem_post(philo->data->forks);
}

static void	handle_sleep(t_philo *philo)
{
	print_action(philo->data, 3, philo->id);
	custom_sleep(philo->data->time_to_sleep);
}

void	routine(t_philo *philo)
{
	pthread_t	death_tid;
	t_data		*d;

	d = (t_data *)philo->data;
	sem_wait(d->sync);
	philo->time_since_meal = get_time();
	if (pthread_create(&death_tid, NULL, &death_check, (void *)philo))
		return ;
	pthread_detach(death_tid);
	if (philo->id % 2)
		custom_sleep(d->time_to_eat / 2);
	while (1)
	{
		if (d->no_of_eat > 0 && philo->eat_count >= d->no_of_eat)
			break ;
		handle_eat(philo);
		handle_sleep(philo);
		print_action(philo->data, 4, philo->id);
	}
}
