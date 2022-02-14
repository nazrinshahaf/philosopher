/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfernand <nfernand@student.42kl.edu.m      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 11:07:43 by nfernand          #+#    #+#             */
/*   Updated: 2022/02/08 11:08:07 by nfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

static int	ft_countnum(int n)
{
	int			length;
	long int	num;

	length = 0;
	num = n;
	if (!num)
		return (1);
	if (num < 0)
	{
		length++;
		num *= -1;
	}
	while (num)
	{
		num /= 10;
		length++;
	}
	return (length);
}

static void	ft_inttochar(char *str, int n, int length)
{
	int			i;
	long int	num;

	i = 0;
	num = n;
	if (num < 0)
	{
		str[i] = '-';
		num *= -1;
	}
	if (num == 0)
		str[i] = '0';
	while (i < length && num)
	{
		if (str[length] == '-')
			return ;
		str[length - i - 1] = (num % 10) + '0';
		num /= 10;
		i++;
	}
}

char	*ft_itoa(int n)
{
	int		length;
	int		neg;
	char	*res;

	neg = 1;
	length = ft_countnum(n);
	res = malloc(sizeof(char) * length + 1);
	if (!res)
		return (NULL);
	ft_inttochar(res, n, length);
	res[length] = '\0';
	return (res);
}
