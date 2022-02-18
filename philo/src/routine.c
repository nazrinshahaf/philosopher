/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfernand <nfernand@student.42kl.edu.m      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 10:18:56 by nfernand          #+#    #+#             */
/*   Updated: 2022/02/18 10:21:39 by nfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	handle_eat(t_philo *philo)
{
	if (philo->data->number_of_philos > 1)
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
		print_action(philo->data, 2, philo->id);
		philo->time_since_meal = get_time();
		pthread_mutex_unlock(&(philo->eating));
		custom_sleep(philo->data->time_to_eat);
		philo->eat_count++;
		pthread_mutex_unlock(&(philo->data->forks[philo->left_fork_id]));
		pthread_mutex_unlock(&(philo->data->forks[philo->right_fork_id]));
	}
}

static void	handle_sleep(t_philo *philo)
{
	print_action(philo->data, 3, philo->id);
	custom_sleep(philo->data->time_to_sleep);
}

void	*routine(void *void_philo)
{
	t_philo	*philo;
	t_data	*d;

	philo = (t_philo *)void_philo;
	d = (t_data *)philo->data;
	while (d->started == 0)
		;
	if (philo->id % 2)
		custom_sleep(d->time_to_eat / 2);
	d->start_time = get_time();
	philo->time_since_meal = get_time();
	while (d->dead == 0 && d->number_of_philos > 1)
	{
		handle_eat(philo);
		handle_sleep(philo);
		print_action(philo->data, 4, philo->id);
		if (all_eat(philo->data) == 1 || philo->eat_count == d->no_of_eat)
			break ;
	}
	return (NULL);
}
