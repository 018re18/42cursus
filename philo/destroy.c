/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rookuma <rookuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 15:43:42 by rookuma           #+#    #+#             */
/*   Updated: 2025/11/24 15:44:45 by rookuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_forks(pthread_mutex_t *forks, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
	free(forks);
}

void	destroy_philos_mutex(t_philo *philos, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		pthread_mutex_destroy(&philos[i].last_eat_ctrl);
		pthread_mutex_destroy(&philos[i].eat_times_ctrl);
		i++;
	}
}

void	destroy_info_mutex(t_setting_time *time, t_information *info)
{
	destroy_forks(info->forks, time->num_philo);
	pthread_mutex_destroy(&info->print_ctrl);
	pthread_mutex_destroy(&info->finish_ctrl);
}

void	destroy_all_mutex(t_philo *philos, t_setting_time *time,
		t_information *info)
{
	destroy_philos_mutex(philos, time->num_philo);
	destroy_info_mutex(time, info);
}
