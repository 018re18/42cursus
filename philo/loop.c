/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rookuma <rookuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 17:05:52 by rookuma           #+#    #+#             */
/*   Updated: 2025/10/20 17:07:21 by rookuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	while (1)
	{
		pthread_mutex_lock(&philo->info->finish_ctrl);
		if (philo->info->finish_flag == Finished)
		{
			pthread_mutex_unlock(&philo->info->finish_ctrl);
			break ;
		}
		pthread_mutex_unlock(&philo->info->finish_ctrl);
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
	return (NULL);
}
