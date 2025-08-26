/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rookuma <rookuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 14:49:45 by rookuma           #+#    #+#             */
/*   Updated: 2025/08/26 17:17:38 by rookuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

enum
{
	FALSE,
	TRUE
};

typedef struct s_setting_time
{
	long		num_philo;
	long		time_die;
	long		time_eat;
	long		time_sleep;
	long		num_must_eat;
}				t_setting_time;

typedef struct s_philo
{
	int			philo_id;
	pthread_t	th_id;
	int			last_eat_time;
	int			eat_times;

}				t_philo;

// utils.c
int				ft_strlen(char *str);
long			ft_atoi_long(char *str);

#endif
