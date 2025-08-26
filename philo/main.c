/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rookuma <rookuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 14:50:06 by rookuma           #+#    #+#             */
/*   Updated: 2025/08/26 16:45:49 by rookuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	write_error(char *message)
{
	int	len;

	len = ft_strlen(message);
	write(2, message, len);
	write(2, "\n", 1);
	return (1);
}

int	setting_time(int argc, char **argv, t_setting_time *tm)
{
	if (!(argc == 5 || argc == 6))
		return (FALSE);
	tm->num_philo = ft_atoi_long(argv[1]);
	tm->time_die = ft_atoi_long(argv[2]);
	tm->time_eat = ft_atoi_long(argv[3]);
	tm->time_sleep = ft_atoi_long(argv[4]);
	if (argc == 6)
		tm->num_must_eat = ft_atoi_long(argv[5]);
	else
		tm->num_must_eat = -1;
	if (tm->num_philo <= 0 || tm->time_die <= 0 || tm->time_eat <= 0
		|| tm->time_sleep <= 0 || (argc == 6 && tm->num_must_eat <= 0))
		return (FALSE);
	return (TRUE);
}

int	main(int argc, char **argv)
{
	t_setting_time	tm;

	if (!setting_time(argc, argv, &tm))
		return (write_error("error setting time"));
	// printf("%d\n", tm.num_philo);
	// printf("%d\n", tm.time_die);
	// printf("%d\n", tm.time_eat);
	// printf("%d\n", tm.time_sleep);
	// if (argc == 6)
	// 	printf("%d\n", tm.num_must_eat);
	return (0);
}
