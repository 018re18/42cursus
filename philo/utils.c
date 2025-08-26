/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rookuma <rookuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 15:39:28 by rookuma           #+#    #+#             */
/*   Updated: 2025/08/26 16:50:52 by rookuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}

long	ft_atoi_long(char *str)
{
	int		i;
	long	num;
	long	tmp;

	if (!str)
		return (-1);
	i = 0;
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
		return (-1);
	num = 0;
	while (str[i])
	{
		if (!('0' <= str[i] && str[i] <= '9'))
			return (-1);
		tmp = num;
		num = num * 10 + (str[i] - '0');
		if (num / 10 != tmp)
			return (-1);
		i++;
	}
	return (num);
}
