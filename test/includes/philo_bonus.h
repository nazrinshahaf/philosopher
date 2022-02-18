/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfernand <nfernand@student.42kl.edu.m      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 10:44:56 by nfernand          #+#    #+#             */
/*   Updated: 2022/02/18 12:12:00 by nfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <semaphore.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/wait.h>
# include <signal.h>
# include <limits.h>

# define RESET	"\033[0m"
# define BLACK	"\033[30m"
# define RED		"\033[31m"
# define GREEN	"\033[32m"
# define YELLOW	"\033[33m"
# define BLUE	"\033[34m"
# define MAGENTA	"\033[35m"
# define CYAN	"\033[36m"
# define WHITE	"\033[37m"

typedef struct s_data	t_data;

typedef struct s_philo
{
	int			id;
	long		time_since_meal;
	int			eat_count;
	int			is_eating;
	pid_t		ph_pid;
	sem_t		*eat_count_sem;
	sem_t		*eating_lock;
	t_data		*data;
}				t_philo;

typedef struct s_data
{
	int			number_of_philos;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			no_of_eat;
	long		start_time;
	t_philo		philo[250];
	sem_t		*forks;
	sem_t		*dead;
	sem_t		*print;
	sem_t		*print_dead;
	sem_t		*sync;
}				t_data;

// ----- ft_atoi.c -----

int		ft_atoi(const char *str);

// ----- ft_itoa.c -----

char	*ft_itoa(int n);

// ----- ft_strlen.c -----

int		ft_strlen(const char *s);

// ----- ft_strjoin.c -----

char	*ft_strjoin(char const *s1, char const *s2);

// ----- time_utils.c -----

long	get_time(void);
void	custom_sleep(int time);

// ----- print_utils.c -----

void	print_rules(t_data *data);
void	print_action(t_data *data, int action, int id);

// ----- init_data.c -----
 
int	init_data(t_data *data, int argc, char **argv);

// ----- terminate_data.c -----

void	terminate_data(t_data *data);

// ----- eat_check.c -----

void	*eat_check(void *void_data);

// ----- death_check.c -----

void	*death_check(void *void_philo);

// ----- death_check.c -----

void	routine(t_philo *philo);

// ----- philosophers.c -----

int		philosophers(t_data *data);


// test

void	ft_putnbr_fd(long n, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putchar_fd(char c, int fd);




#endif
