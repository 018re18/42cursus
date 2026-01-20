/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   watcher.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rookuma <rookuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 17:06:06 by rookuma           #+#    #+#             */
/*   Updated: 2025/10/20 17:07:12 by rookuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	print_death(t_philo *philo, long timestamp)
{
	pthread_mutex_lock(&philo->info->print_ctrl);
	pthread_mutex_lock(&philo->info->finish_ctrl);
	philo->info->finish_flag = Finished;
	pthread_mutex_unlock(&philo->info->finish_ctrl);
	printf("%ld %d died\n", timestamp, philo->philo_id);
	pthread_mutex_unlock(&philo->info->print_ctrl);
}

int	check_death(t_philo *philos, t_setting_time *time)
{
	int		i;
	long	now_time;
	long	last_eat;

	i = 0;
	while (i < time->num_philo)
	{
		pthread_mutex_lock(&philos[i].last_eat_ctrl);
		last_eat = philos[i].last_eat_time;
		pthread_mutex_unlock(&philos[i].last_eat_ctrl);
		now_time = get_time();
		if (now_time - last_eat >= time->time_die)
		{
			print_death(&philos[i], now_time - philos[i].info->start_time);
			return (1);
		}
		i++;
	}
	return (0);
}

int	check_eat_times(t_philo *philos, t_setting_time *time)
{
	int	i;
	int	count;
	int	eat_times;

	if (time->num_must_eat == -1)
		return (0);
	count = 0;
	i = 0;
	while (i < time->num_philo)
	{
		pthread_mutex_lock(&philos[i].eat_times_ctrl);
		eat_times = philos[i].num_eat_times;
		pthread_mutex_unlock(&philos[i].eat_times_ctrl);
		if (eat_times >= time->num_must_eat)
			count++;
		i++;
	}
	return (count == time->num_philo);
}

void	watcher_philo(t_philo *philos, t_setting_time *time,
		t_information *info)
{
	while (1)
	{
		if (check_death(philos, time))
			break ;
		if (check_eat_times(philos, time))
		{
			pthread_mutex_lock(&info->finish_ctrl);
			info->finish_flag = Finished;
			pthread_mutex_unlock(&info->finish_ctrl);
			break ;
		}
		usleep(1000);
	}
}
