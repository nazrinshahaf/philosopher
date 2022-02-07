/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfernand <nfernand@student.42kl.edu.m      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 10:44:56 by nfernand          #+#    #+#             */
/*   Updated: 2022/02/07 12:50:20 by nfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS
# define PHILO_BONUS

#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <semaphore.h>
#include <stdlib.h>
#include <pthread.h>

#define RESET	"\033[0m"
#define BLACK	"\033[30m"
#define RED		"\033[31m"
#define GREEN	"\033[32m"
#define YELLOW	"\033[33m"
#define BLUE	"\033[34m"
#define MAGENTA	"\033[35m"
#define CYAN	"\033[36m"
#define WHITE	"\033[37m"

// ----- ft_atoi.c -----

int	ft_atoi(const char *str);

#endif
