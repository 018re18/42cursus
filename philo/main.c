/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rookuma <rookuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 14:50:06 by rookuma           #+#    #+#             */
/*   Updated: 2025/12/07 16:39:27 by rookuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	thread_error(t_philo *philos, t_information *info,
		t_setting_time *time, int i)
{
	pthread_mutex_lock(&info->finish_ctrl);
	info->finish_flag = Finished;
	pthread_mutex_unlock(&info->finish_ctrl);
	i -= 1;
	while (i >= 0)
	{
		pthread_join(philos[i].th_id, NULL);
		i--;
	}
	destroy_all_mutex(philos, time, info);
	free(philos);
	return (write_error("error_pthread_create"));
}

static int	create_threads(t_philo *philos, t_setting_time *time,
		t_information *info)
{
	int	i;

	i = 0;
	while (i < time->num_philo)
	{
		if (pthread_create(&philos[i].th_id, NULL, philo_loop,
				&philos[i]) != 0)
			return (thread_error(philos, info, time, i));
		i++;
	}
	return (0);
}

static void	join_threads(t_philo *philos, int num_philo)
{
	int	i;

	i = 0;
	while (i < num_philo)
	{
		pthread_join(philos[i].th_id, NULL);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_setting_time	time;
	t_information	info;
	t_philo			*philos;

	if (!setting_time(argc, argv, &time))
		return (write_error("error setting time"));
	if (!init_info(&time, &info))
		return (write_error("error_init_info"));
	info.start_time = get_time();
	philos = init_philos(&time, &info);
	if (!philos)
		return (write_error("error_init_philos"));
	if (create_threads(philos, &time, &info) != 0)
		return (1);
	watcher_philo(philos, &time, &info);
	join_threads(philos, time.num_philo);
	destroy_all_mutex(philos, &time, &info);
	free(philos);
	return (0);
}
