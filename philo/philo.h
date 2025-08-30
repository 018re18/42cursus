/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rookuma <rookuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 14:49:45 by rookuma           #+#    #+#             */
/*   Updated: 2025/08/30 17:52:21 by rookuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

enum
{
	FALSE,
	TRUE
};

enum
{
	Working,
	Finished
};

typedef struct s_setting_time
{
	int				num_philo;
	long			time_die;
	long			time_eat;
	long			time_sleep;
	long			num_must_eat;
}					t_setting_time;

typedef struct s_information
{
	t_setting_time	*time;
	long			start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_ctrl;
	int				finish_flag;
	pthread_mutex_t	finish_ctrl;

}					t_information;

typedef struct s_philo
{
	int				philo_id;
	pthread_t		th_id;
	long			last_eat_time;
	int				num_eat_times;
	pthread_mutex_t	*fork_r;
	pthread_mutex_t	*fork_l;
	t_information	*info;
}					t_philo;

// utils.c
int					write_error(char *message);
int					ft_strlen(char *str);
long				ft_atoi_long(char *str);
int					ft_atoi_philo(char *str);

#endif
