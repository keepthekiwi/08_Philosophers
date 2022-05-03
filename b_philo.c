/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_philo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skillian <skillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 21:42:00 by skillian          #+#    #+#             */
/*   Updated: 2022/05/03 14:45:39 by skillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

void	init_philo(void)
/* creates arrays of Philos (**) (needs to be freed)*/
{
	int	i;

	data()->philos = malloc(sizeof(t_philo *) * (data()->nb_of_philos + 1));
	i = -1;
	if (pthread_mutex_init(&data()->init_lock, NULL) != 0)
		printf_m("Error at Mutex Init", 0);
	pthread_mutex_lock(&data()->init_lock);
	while (++i < data()->nb_of_philos)
		data()->philos[i] = create_philo(i);
	if (data()->nb_of_philos == 1)
		data()->philos[0]->status = only_one_philo;
	data()->philos[i] = NULL;
	data()->init_routine = true;
	pthread_mutex_unlock(&data()->init_lock);
}

t_philo	*create_philo(int i)
/* create single Philo array (needs to be freed)*/
{
	t_philo		*philo;

	philo = malloc(sizeof(t_philo));
	philo->num = i;
	philo->status = thinking;
	philo->fork = on_table;
	printf_m("PHILO CREATED\n", i);
	if (pthread_mutex_init(&philo->lock_mode_fork, NULL) != 0)
		printf_m("Error at Mutex Init", 0);
	if ((pthread_create(&philo->id, NULL, &routine, philo)) == 0)
		data()->num_threads++;
	else
		printf_m("Error at Create Routine", 0);
	return (philo);
}

void	*routine(void *varg)
/* think, eat, sleep...repeat (every 2nd Philo starts)*/
{
	t_philo	*philo;

	philo = (t_philo *) varg;
	while (!init_routine())
		usleep(10);
	philo->last_meal_timestamp = get_time();
	if (philo->num % 2)
		sleep_ms(philo, data()->time_to_eat);
	while_routine(philo);
	return (NULL);
}

void	while_routine(t_philo *philo)
/* What a Philo does aaaall day long*/
{
	while (init_routine())
	{
		pthread_mutex_lock(&data()->init_lock);
		if (data()->all_alive == false)
		{
			pthread_mutex_unlock(&data()->init_lock);
			break ;
		}
		pthread_mutex_unlock(&data()->init_lock);
		if (philo->status == eating)
			philo->status = sleeping;
		if (philo->status == sleeping)
			sleepy_philo(philo);
		if (philo->status == thinking)
			take_forks(data()->philos, philo->num);
		if (philo->status == only_one_philo)
			sleep_ms(philo, data()->time_to_die);
		if (data()->meals_to_eat && (philo->ate == data()->meals_to_eat))
			break ;
	}
}

void	sleepy_philo(t_philo *philo)
{
	pthread_mutex_lock(&data()->init_lock);
	printf_m("\033[0;35m is sleeping\033[0m\n", philo->num);
	pthread_mutex_unlock(&data()->init_lock);
	philo->status = thinking;
	sleep_ms(philo, data()->time_to_sleep);
}
