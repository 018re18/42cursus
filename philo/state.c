/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rookuma <rookuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 17:06:15 by rookuma           #+#    #+#             */
/*   Updated: 2025/11/24 12:40:45 by rookuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	take_forks(t_philo *philo, pthread_mutex_t *first,
		pthread_mutex_t *second)
{
	pthread_mutex_lock(first);
	print_status(philo, Take_Fork);
	pthread_mutex_lock(second);
	print_status(philo, Take_Fork);
}

static void	update_eat_status(t_philo *philo)
{
	print_status(philo, Eat);
	pthread_mutex_lock(&philo->last_eat_ctrl);
	philo->last_eat_time = get_time();
	pthread_mutex_unlock(&philo->last_eat_ctrl);
	ft_usleep(philo->info->time->time_eat);
	pthread_mutex_lock(&philo->eat_times_ctrl);
	philo->num_eat_times++;
	pthread_mutex_unlock(&philo->eat_times_ctrl);
}

void	philo_eat(t_philo *philo)
{
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;

	if (philo->fork_r < philo->fork_l)
	{
		first_fork = philo->fork_r;
		second_fork = philo->fork_l;
	}
	else
	{
		first_fork = philo->fork_l;
		second_fork = philo->fork_r;
	}
	take_forks(philo, first_fork, second_fork);
	update_eat_status(philo);
	pthread_mutex_unlock(second_fork);
	pthread_mutex_unlock(first_fork);
}

void	philo_sleep(t_philo *philo)
{
	print_status(philo, Sleep);
	ft_usleep(philo->info->time->time_sleep);
}

void	philo_think(t_philo *philo)
{
	long	think_time;

	print_status(philo, Think);
	if (philo->info->time->num_philo % 2 != 0)
	{
		think_time = philo->info->time->time_eat * 2
			- philo->info->time->time_sleep;
		if (think_time > 0 && think_time < 600)
			ft_usleep(think_time * 500);
	}
}
