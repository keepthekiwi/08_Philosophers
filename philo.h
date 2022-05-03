/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skillian <skillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 16:06:42 by skillian          #+#    #+#             */
/*   Updated: 2022/04/25 21:23:58 by skillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include	<stdio.h>
# include	<stdbool.h>
# include	<pthread.h>
# include	<sys/time.h>
# include	<stdlib.h>
# include	<unistd.h>
# include	<limits.h>
# include	"libft/libft.h"

enum e_status {
	on_table,
	in_hand,
	thinking,
	sleeping,
	eating,
	only_one_philo,
	dead,
	next_in_hand
};

typedef struct s_philo
{
	pthread_t		id;
	pthread_mutex_t	lock_mode_fork;
	int				num;
	int				fork;
	int				status;
	int				ate;
	time_t			last_meal_timestamp;
}	t_philo;

typedef struct s_data
{
	int				nb_of_philos;
	time_t			time_now;
	pthread_mutex_t	print;
	pthread_mutex_t	init_lock;
	bool			arg_checker;
	bool			init_routine;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meals_to_eat;
	int				num_threads;
	bool			all_alive;
	bool			print_possible;
	t_philo			**philos;
}	t_data;

void		args_input(char **argv);
time_t		get_time(void);
time_t		get_time_since_start(void);
t_philo		*create_philo(int i);
void		init_philo(void);
bool		init_routine(void);
void		*routine(void *varg);
void		while_routine(t_philo *philo);
void		take_forks(t_philo **philo, int i);
void		eat(t_philo **philo, int i, int nb);
bool		did_i_die(t_philo *philo);
void		sleep_ms(t_philo *philo, time_t tt);
void		sleepy_philo(t_philo *philo);
t_data		*data(void);
int			ft_atoi_v2(char *str);
void		free_all(void);
void		join_threads(void);
void		printf_m(char *str, int i);
bool		int_min_max_checker(char *ptr);

#endif
