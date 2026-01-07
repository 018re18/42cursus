/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rookuma <rookuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 14:49:45 by rookuma           #+#    #+#             */
/*   Updated: 2025/12/07 16:40:39 by rookuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

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

enum
{
	Take_Fork,
	Eat,
	Sleep,
	Think
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
	pthread_mutex_t	last_eat_ctrl;
	long			last_eat_time;
	pthread_mutex_t	eat_times_ctrl;
	int				num_eat_times;
	pthread_mutex_t	*fork_r;
	pthread_mutex_t	*fork_l;
	t_information	*info;
}					t_philo;

// destroy.c
void				destroy_forks(pthread_mutex_t *forks, int count);
void				destroy_philos_mutex(t_philo *philos, int count);
void				destroy_info_mutex(t_setting_time *time,
						t_information *info);
void				destroy_all_mutex(t_philo *philos, t_setting_time *time,
						t_information *info);

// init.c
int					setting_time(int argc, char **argv, t_setting_time *time);
int					make_forks(t_information *info, int count);
int					init_info(t_setting_time *time, t_information *info);
t_philo				*init_philos(t_setting_time *tm, t_information *info);

// utils1.c
int					write_error(char *message);
int					ft_strlen(char *str);
long				ft_atoi_long(char *str);
int					ft_atoi_philo(char *str);
void				print_status(t_philo *philo, int mode);

// utils2.c
char				*ft_itoa_long(long num);
long				get_time(void);
void				ft_usleep(long time);

// state.c
void				philo_eat(t_philo *philo);
void				philo_sleep(t_philo *philo);
void				philo_think(t_philo *philo);

// loop.c
void				*philo_loop(void *arg);

// watcher.c
int					check_death(t_philo *philos, t_setting_time *time);
int					check_eat_times(t_philo *philos, t_setting_time *time);
void				watcher_philo(t_philo *philos, t_setting_time *time,
						t_information *info);

#endif
