/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rookuma <rookuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 17:05:52 by rookuma           #+#    #+#             */
/*   Updated: 2025/11/24 15:30:08 by rookuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	philo_loop_helper(t_philo *philo)
{
	philo_eat(philo);
	philo_sleep(philo);
	philo_think(philo);
}

void	*philo_loop(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->info->time->num_philo == 1)
	{
		pthread_mutex_lock(philo->fork_r);
		print_status(philo, Take_Fork);
		ft_usleep(philo->info->time->time_die);
		pthread_mutex_unlock(philo->fork_r);
		return (NULL);
	}
	if (philo->philo_id % 2 == 0)
		ft_usleep(philo->info->time->time_eat / 2);
	while (1)
	{
		pthread_mutex_lock(&philo->info->finish_ctrl);
		if (philo->info->finish_flag == Finished)
		{
			pthread_mutex_unlock(&philo->info->finish_ctrl);
			break ;
		}
		pthread_mutex_unlock(&philo->info->finish_ctrl);
		philo_loop_helper(philo);
	}
	return (NULL);
}
