/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rookuma <rookuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 14:50:06 by rookuma           #+#    #+#             */
/*   Updated: 2025/10/20 17:07:19 by rookuma          ###   ########.fr       */
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

void	destroy_info_mutex(t_setting_time *time, t_information *info)
{
	destroy_forks(info->forks, time->num_philo);
	pthread_mutex_destroy(&info->print_ctrl);
	pthread_mutex_destroy(&info->finish_ctrl);
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

void	destroy_all_mutex(t_philo *philos, t_setting_time *time,
		t_information *info)
{
	destroy_philos_mutex(philos, time->num_philo);
	destroy_info_mutex(time, info);
}

t_philo	*init_philos(t_setting_time *tm, t_information *info)
{
	t_philo	*philos;
	int		i;

	philos = (t_philo *)malloc(sizeof(t_philo) * tm->num_philo);
	if (!philos)
	{
		destroy_info_mutex(tm, info);
		return (NULL);
	}
	i = 0;
	while (i < tm->num_philo)
	{
		philos[i].info = info;
		philos[i].philo_id = i + 1;
		philos[i].num_eat_times = 0;
		philos[i].last_eat_time = info->start_time;
		pthread_mutex_init(&philos[i].last_eat_ctrl, NULL);
		pthread_mutex_init(&philos[i].eat_times_ctrl, NULL);
		philos[i].fork_r = &info->forks[i];
		if (i == tm->num_philo - 1)
			philos[i].fork_l = &info->forks[0];
		else
			philos[i].fork_l = &info->forks[i + 1];
		i++;
	}
	return (philos);
}

int	process_for_one(t_setting_time *tm)
{
	char	*finish_time;

	write(1, "0 1 has taken a fork\n", 21);
	ft_usleep(tm->time_die);
	finish_time = ft_itoa_long(tm->time_die);
	if (!finish_time)
		return (1);
	write(1, finish_time, ft_strlen(finish_time));
	free(finish_time);
	write(1, " 1 died\n", 8);
	return (0);
}

int	main(int argc, char **argv)
{
	t_setting_time	time;
	t_information	info;
	t_philo			*philos;
	int				i;

	if (!setting_time(argc, argv, &time))
		return (write_error("error setting time"));
	if (time.num_philo == 1)
		return (process_for_one(&time));
	if (!init_info(&time, &info))
		return (write_error("error_init_info"));
	info.start_time = get_time();
	philos = init_philos(&time, &info);
	if (!philos)
		return (write_error("error_init_philos"));
	i = 0;
	while (i < time.num_philo)
	{
		pthread_create(&philos[i].th_id, NULL, philo_loop, &philos[i]);
		i++;
	}
	watcher_philo(philos, &time, &info);
	i = 0;
	while (i < time.num_philo)
	{
		pthread_join(philos[i].th_id, NULL);
		i++;
	}
	destroy_all_mutex(philos, &time, &info);
	free(philos);
	return (0);
}
