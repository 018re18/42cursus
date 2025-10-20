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

void ft_usleep(long time)
{
	long start_time;
	long now_time;

	start_time = get_time();
	while (1)
	{
		now_time = get_time();
		if (now_time - start_time >= time)
			break ;
		usleep(100);
	}
}

long get_time(void)
{
    struct timeval	tv;
    long			time;

    gettimeofday(&tv, NULL);
    time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
    return (time);
}

void print_status(t_philo *philo, int mode)
{
	long	now_time;

	pthread_mutex_lock(&philo->info->finish_ctrl);
	if( philo->info->finish_flag == Finished)
	{
		pthread_mutex_unlock(&philo->info->finish_ctrl);
		return ;
	}
	pthread_mutex_unlock(&philo->info->finish_ctrl);
	now_time = get_time() - philo->info->start_time;
	pthread_mutex_lock(&philo->info->print_ctrl);
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