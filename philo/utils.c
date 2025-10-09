/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rookuma <rookuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 15:39:28 by rookuma           #+#    #+#             */
/*   Updated: 2025/09/06 14:22:02 by rookuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	write_error(char *message)
{
	int	len;

	len = ft_strlen(message);
	write(2, message, len);
	write(2, "\n", 1);
	return (1);
}

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

int	ft_atoi_philo(char *str)
{
	int		i;
	long	num;

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
		num = num * 10 + (str[i] - '0');
		if (num > 2147483647)
			return (-1);
		i++;
	}
	return ((int)(num));
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
