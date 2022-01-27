/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfernand <nfernand@student.42kl.edu.m      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 10:43:28 by nfernand          #+#    #+#             */
/*   Updated: 2022/01/27 11:20:55 by nfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philo_bonus.h"

long	get_time()
{
	struct timeval	t;
	long int	time;

	gettimeofday(&t, NULL);
	time = t.tv_sec;
	time = (time * 1000) + (t.tv_usec / 1000);
	return (time);
}

void	custom_sleep(int time)
{
	long int	start;
	long int	end;

	start = get_time();
	while (1)
	{
		end = get_time();
		if ((end - start) >= time)
			break;
		usleep(500);
	}
}

int	main(int argc, char **argv)
{
	if (argc > 6 || argc < 5)
	{
		printf(GREEN "\"./philo [no_of_philos] [time_to_die] ");
		printf("[time_to_eat] [time_to_sleep] ");
		printf(CYAN "[no_of_times_philos_must_eat]"GREEN"\"\n" RESET);
		return (0);
	}
}
