/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfernand <nfernand@student.42kl.edu.m      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 10:52:44 by nfernand          #+#    #+#             */
/*   Updated: 2022/01/24 20:07:52 by nfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <sys/time.h>
# include <pthread.h>

#define RESET	"\033[0m"
#define BLACK	"\033[30m"
#define RED		"\033[31m"
#define GREEN	"\033[32m"
#define YELLOW	"\033[33m"
#define BLUE	"\033[34m"
#define MAGENTA	"\033[35m"
#define CYAN	"\033[36m"
#define WHITE	"\033[37m"

typedef struct s_data t_data;

typedef struct	s_philo
{
	int				id;
	long			time_since_meal;
	int				right_fork_id;
	int				left_fork_id;
	int				eat_count;
	pthread_mutex_t	eating;
	pthread_t		thread_id;
	t_data			*data;
}				t_philo;

typedef struct	s_data
{
	int				number_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				no_of_eat;
	int				dead;
	long			start_time;
	pthread_mutex_t	print;
	pthread_mutex_t	forks[250];
	t_philo			philo[250];
}				t_data;

// ----- ft_atoi.c -----

int	ft_atoi(const char *str);



#endif
