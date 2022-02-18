/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminate_data.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfernand <nfernand@student.42kl.edu.m      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 11:36:10 by nfernand          #+#    #+#             */
/*   Updated: 2022/02/18 11:42:16 by nfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

static void terminate_semaphore_data(t_data *data)
{
	char	*str;
	int		i;

	i = 0;
	while (i < data->number_of_philos)
	{
		str = ft_strjoin("/eating_sem", ft_itoa(i));
		sem_unlink(str);
		str = ft_strjoin("/eatcount_sem", ft_itoa(i));
		sem_unlink(str);
		i++;
	}
}

void	terminate_data(t_data *data)
{
	sem_unlink("/forks_sem");
	sem_unlink("/dead_sem");
	sem_unlink("/print_sem");
	sem_unlink("/printdead_sem");
	sem_unlink("/sync_sem");

}
