/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rookuma <rookuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 16:18:17 by rookuma           #+#    #+#             */
/*   Updated: 2025/12/07 16:18:40 by rookuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	setting_time(int argc, char **argv, t_setting_time *time)
{
	if (!(argc == 5 || argc == 6))
		return (FALSE);
	time->num_philo = ft_atoi_philo(argv[1]);
	time->time_die = ft_atoi_long(argv[2]);
	time->time_eat = ft_atoi_long(argv[3]);
	time->time_sleep = ft_atoi_long(argv[4]);
	if (argc == 6)
		time->num_must_eat = ft_atoi_long(argv[5]);
	else
		time->num_must_eat = -1;
	if (time->num_philo <= 0 || time->time_die <= 0 || time->time_eat <= 0
		|| time->time_sleep <= 0 || (argc == 6 && time->num_must_eat <= 0))
		return (FALSE);
	return (TRUE);
}

int	make_forks(t_information *info, int count)
{
	int	i;

	info->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * count);
	if (!info->forks)
		return (FALSE);
	i = 0;
	while (i < count)
	{
		if (pthread_mutex_init(&info->forks[i], NULL) != 0)
		{
			destroy_forks(info->forks, i);
			return (FALSE);
		}
		i++;
	}
	return (TRUE);
}

int	init_info(t_setting_time *time, t_information *info)
{
	info->time = time;
	if (!make_forks(info, time->num_philo))
		return (FALSE);
	if (pthread_mutex_init(&info->print_ctrl, NULL) != 0)
	{
		destroy_forks(info->forks, time->num_philo);
		return (FALSE);
	}
	if (pthread_mutex_init(&info->finish_ctrl, NULL) != 0)
	{
		destroy_forks(info->forks, time->num_philo);
		pthread_mutex_destroy(&info->print_ctrl);
		return (FALSE);
	}
	info->finish_flag = Working;
	return (TRUE);
}

static int	init_philo_mutexes(t_philo *philos, int i, t_setting_time *tm,
		t_information *info)
{
	if (pthread_mutex_init(&philos[i].last_eat_ctrl, NULL) != 0)
	{
		destroy_philos_mutex(philos, i);
		destroy_info_mutex(tm, info);
		free(philos);
		return (FALSE);
	}
	if (pthread_mutex_init(&philos[i].eat_times_ctrl, NULL) != 0)
	{
		pthread_mutex_destroy(&philos[i].last_eat_ctrl);
		destroy_philos_mutex(philos, i);
		destroy_info_mutex(tm, info);
		free(philos);
		return (FALSE);
	}
	return (TRUE);
}

t_philo	*init_philos(t_setting_time *tm, t_information *info)
{
	t_philo	*philos;
	int		i;

	philos = (t_philo *)malloc(sizeof(t_philo) * tm->num_philo);
	if (!philos)
		return (destroy_info_mutex(tm, info), NULL);
	i = 0;
	while (i < tm->num_philo)
	{
		philos[i].info = info;
		philos[i].philo_id = i + 1;
		philos[i].num_eat_times = 0;
		philos[i].last_eat_time = info->start_time;
		if (!init_philo_mutexes(philos, i, tm, info))
			return (NULL);
		philos[i].fork_r = &info->forks[i];
		if (i == tm->num_philo - 1)
			philos[i].fork_l = &info->forks[0];
		else
			philos[i].fork_l = &info->forks[i + 1];
		i++;
	}
	return (philos);
}
