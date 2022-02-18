/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfernand <nfernand@student.42kl.edu.m      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 10:02:38 by nfernand          #+#    #+#             */
/*   Updated: 2022/02/18 10:15:51 by nfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	all_eat(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philos)
	{
		if (data->philo[i].eat_count != data->no_of_eat)
			return (0);
		i++;
	}
	return (1);
}
