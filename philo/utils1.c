/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rookuma <rookuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 15:39:28 by rookuma           #+#    #+#             */
/*   Updated: 2025/12/07 16:04:03 by rookuma          ###   ########.fr       */
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

void	print_status(t_philo *philo, int mode)
{
	long	now_time;

	now_time = get_time() - philo->info->start_time;
	pthread_mutex_lock(&philo->info->print_ctrl);
	pthread_mutex_lock(&philo->info->finish_ctrl);
	if (philo->info->finish_flag == Finished)
	{
		pthread_mutex_unlock(&philo->info->finish_ctrl);
		pthread_mutex_unlock(&philo->info->print_ctrl);
		return ;
	}
	pthread_mutex_unlock(&philo->info->finish_ctrl);
	if (mode == Take_Fork)
		printf("%ld %d has taken a fork\n", now_time, philo->philo_id);
	else if (mode == Eat)
		printf("%ld %d is eating\n", now_time, philo->philo_id);
	else if (mode == Sleep)
		printf("%ld %d is sleeping\n", now_time, philo->philo_id);
	else if (mode == Think)
		printf("%ld %d is thinking\n", now_time, philo->philo_id);
	pthread_mutex_unlock(&philo->info->print_ctrl);
}
