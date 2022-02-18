/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfernand <nfernand@student.42kl.edu.m      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 10:45:26 by nfernand          #+#    #+#             */
/*   Updated: 2022/02/18 12:13:39 by nfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

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

void	print_action(t_data *data, int action, int id)
{
	sem_wait(data->print);
	sem_wait(data->print_dead);
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
	if (action < 5)
		sem_post(data->print_dead);
	sem_post(data->print);
}
