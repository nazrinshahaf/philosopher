/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfernand <nfernand@student.42kl.edu.m      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 10:00:41 by nfernand          #+#    #+#             */
/*   Updated: 2022/02/18 10:00:57 by nfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	handle_error(t_data *data, int err_num)
{
	if (err_num == 1)
	{
		printf(RED "Error with input values\n");
		printf("[1 <= n < 200]\n[0 <= ttd <= INT_MAX]\n");
		printf("[0 <= tte <= INT_MAX]\n[0 <= tts <= INT_MAX]\n");
		printf("[0 <= eat_count <= INT_MAX]\n" RESET);
	}
	else if (err_num == 2)
		printf(RED "Error with initialising mutex\n" RESET);
	else if (err_num == 3)
		printf(RED "Errror with creating threads\n" RESET);
	return (0);
}
