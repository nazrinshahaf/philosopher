/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfernand <nfernand@student.42kl.edu.m      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 09:47:19 by nfernand          #+#    #+#             */
/*   Updated: 2022/02/18 09:48:10 by nfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

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

void	print_philo(t_data *data, int philo_id)
{
	printf(MAGENTA "philosophers id = %d\n", data->philo[philo_id].id);
	printf("time since meal = %ld\n", data->philo[philo_id].time_since_meal);
	printf("right fork id = %d\n", data->philo[philo_id].right_fork_id);
	printf("left fork id = %d\n", data->philo[philo_id].left_fork_id);
	printf("eat count = %d\n\n", data->philo[philo_id].eat_count);
}

void	print_action(t_data *data, int action, int id)
{
	pthread_mutex_lock(&(data->print));
	if (data->dead == 0)
	{
		if (action == 1)
			printf(BLUE "%ld %d has taken a fork\n" RESET, get_time(), id);
		else if (action == 2)
			printf(MAGENTA "%ld %d is eating\n" RESET, get_time(), id);
		else if (action == 3)
			printf(CYAN "%ld %d is sleeping\n" RESET, get_time(), id);
		else if (action == 4)
			printf(YELLOW "%ld %d is thinking\n" RESET, get_time(), id);
		else if (action == 5)
			printf(RED "%ld %d died\n" RESET, get_time(), id);
	}
	pthread_mutex_unlock(&(data->print));
}
