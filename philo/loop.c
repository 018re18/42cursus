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
	if (philo->philo_id % 2 == 0)
		ft_usleep(1);
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
