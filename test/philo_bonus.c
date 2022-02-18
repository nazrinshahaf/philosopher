/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfernand <nfernand@student.42kl.edu.m      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 10:43:28 by nfernand          #+#    #+#             */
/*   Updated: 2022/02/18 11:53:10 by nfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philo_bonus.h"


int	main(int argc, char **argv)
{
	t_data		data;
	pthread_t	eat_tid;
	int			i;

	if (argc > 6 || argc < 5)
	{
		printf(GREEN "\"./philo [no_of_philos] [time_to_die] ");
		printf("[time_to_eat] [time_to_sleep] ");
		printf(CYAN "[no_of_times_philos_must_eat]"GREEN"\"\n" RESET);
		return (0);
	}
	init_data(&data, argc, argv);
	print_rules(&data);
	if (data.no_of_eat > 0)
	{
		pthread_create(&eat_tid, NULL, &eat_check, (void *)&data);
		pthread_detach(eat_tid);
	}
	philosophers(&data);
	sem_wait(data.dead);
	i = 0;
	while (i < data.number_of_philos)
		kill(data.philo[i++].ph_pid, SIGTERM);
	terminate_data(&data);
	return (0);
}
