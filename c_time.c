/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   C_time.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skillian <skillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 15:01:15 by skillian          #+#    #+#             */
/*   Updated: 2022/04/25 21:30:16 by skillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

time_t	get_time(void)
/* time since 00:00:00 UTC, January 1, 1970 (Unix timestamp) */
{
	struct timeval	time;
	time_t			ms;

	gettimeofday(&time, NULL);
	ms = ((time.tv_sec * 1000) + (time.tv_usec / 1000));
	return (ms);
}

time_t	get_time_since_start(void)
{
	time_t	start;
	time_t	now;

	start = data()->time_now;
	now = get_time();
	now = (now - start);
	return (now);
}

void	sleep_ms(t_philo *philo, time_t tt)
{	
	time_t	time;

	time = get_time();
	while (1)
	{
		if (time + tt <= get_time())
			break ;
		did_i_die(philo);
		usleep(100);
	}
}

bool	did_i_die(t_philo *philo)
{
	bool	i;

	i = false;
	pthread_mutex_lock(&data()->init_lock);
	if (get_time() - philo->last_meal_timestamp > data()->time_to_die)
	{
		printf_m("\033[0;31m died\033\n", philo->num);
		data()->all_alive = false;
		data()->init_routine = false;
		pthread_mutex_lock(&data()->print);
		data()->print_possible = false;
		pthread_mutex_unlock(&data()->print);
		i = true;
	}
	pthread_mutex_unlock(&data()->init_lock);
	return (i);
}

void	free_all(void)
{
	int	i;

	i = -1;
	while (++i < data()->num_threads)
	{
		if (pthread_mutex_destroy(&data()->philos[i]->lock_mode_fork) != 0)
			printf_m("Error at Mutex Destroy", i);
	}	
	if (pthread_mutex_destroy(&data()->print) != 0)
		printf_m("Error at Mutex Destroy", i);
	if (pthread_mutex_destroy(&data()->init_lock) != 0)
		printf_m("Error at Mutex Destroy", i);
	i = -1;
	while (++i < data()->nb_of_philos)
	{
		free(data()->philos[i]);
		data()->philos[i] = NULL;
	}	
	free(data()->philos);
	data()->philos = NULL;
}
