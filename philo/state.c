/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rookuma <rookuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 17:06:15 by rookuma           #+#    #+#             */
/*   Updated: 2025/10/20 17:07:15 by rookuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_eat(t_philo *philo)
{
	if (philo->philo_id % 2 == 0)
	{
		pthread_mutex_lock(philo->fork_r);
		print_status(philo, Take_Fork);
		pthread_mutex_lock(philo->fork_l);
		print_status(philo, Take_Fork);
	}
	else
	{
		pthread_mutex_lock(philo->fork_l);
		print_status(philo, Take_Fork);
		pthread_mutex_lock(philo->fork_r);
		print_status(philo, Take_Fork);
	}
	print_status(philo, Eat);
	pthread_mutex_lock(&philo->last_eat_ctrl);
	philo->last_eat_time = get_time();
	pthread_mutex_unlock(&philo->last_eat_ctrl);
	ft_usleep(philo->info->time->time_eat);
	pthread_mutex_lock(&philo->eat_times_ctrl);
	philo->num_eat_times++;
	pthread_mutex_unlock(&philo->eat_times_ctrl);
	pthread_mutex_unlock(philo->fork_r);
	pthread_mutex_unlock(philo->fork_l);
}

void	philo_sleep(t_philo *philo)
{
	print_status(philo, Sleep);
	ft_usleep(philo->info->time->time_sleep);
}

void	philo_think(t_philo *philo)
{
	print_status(philo, Think);
}
