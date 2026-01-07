/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rookuma <rookuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 16:02:39 by rookuma           #+#    #+#             */
/*   Updated: 2025/12/07 16:03:54 by rookuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	count_digit(long tmp)
{
	int	len;

	len = 1;
	while (tmp / 10)
	{
		len++;
		tmp /= 10;
	}
	return (len);
}

char	*ft_itoa_long(long num)
{
	int		len;
	char	*les;
	long	tmp;

	tmp = num;
	if (tmp < 0)
		return (NULL);
	len = count_digit(tmp);
	les = (char *)malloc(sizeof(char) * (len + 1));
	if (!les)
		return (NULL);
	les[len] = '\0';
	while (len-- > 0)
	{
		les[len] = tmp % 10 + '0';
		tmp = tmp / 10;
	}
	return (les);
}

void	ft_usleep(long time)
{
	long	start_time;
	long	now_time;

	start_time = get_time();
	while (1)
	{
		now_time = get_time();
		if (now_time - start_time >= time)
			break ;
		usleep(100);
	}
}

long	get_time(void)
{
	struct timeval	tv;
	long			time;

	gettimeofday(&tv, NULL);
	time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (time);
}
