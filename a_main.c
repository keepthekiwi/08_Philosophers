/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   A_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skillian <skillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 17:52:23 by skillian          #+#    #+#             */
/*   Updated: 2022/04/25 23:06:22 by skillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

int	main(int argc, char **argv)
{
	data()->arg_checker = true;
	if (argc == 5 || argc == 6)
		args_input(argv);
	else
		return (printf("Args do not match.\n"));
	if (data()->arg_checker == false)
		return (printf("Args do not match.\n"));
	data()->time_now = get_time();
	if (pthread_mutex_init(&data()->print, NULL) != 0)
		printf_m("Error at Mutex Init", 0);
	init_philo();
	join_threads();
	free_all();
	return (0);
}

void	args_input(char **argv)
{
	data()->nb_of_philos = ft_atoi_v2(argv[1]);
	data()->time_to_die = ft_atoi_v2(argv[2]);
	data()->time_to_eat = ft_atoi_v2(argv[3]);
	data()->time_to_sleep = ft_atoi_v2(argv[4]);
	if (argv[5])
		data()->meals_to_eat = ft_atoi_v2(argv[5]);
	else
		data()->meals_to_eat = -1;
	data()->init_routine = false;
	data()->all_alive = true;
	data()->print_possible = true;
	data()->num_threads = 0;
}

void	take_forks(t_philo **philo, int i)
/* it would be enough id you just have the mutex lock as a fork*/
{
	int	nb;

	pthread_mutex_lock(&data()->init_lock);
	printf_m("\e[0;33m is thinking\033[0m\n", philo[i]->num);
	pthread_mutex_unlock(&data()->init_lock);
	nb = data()->nb_of_philos;
	pthread_mutex_lock(&philo[i]->lock_mode_fork);
	printf_m("\033[0;36m has taken a fork\033[0m\n", philo[i]->num);
	if (did_i_die(philo[i]) == true)
	{
		pthread_mutex_unlock(&philo[i]->lock_mode_fork);
		return ;
	}	
	pthread_mutex_lock(&philo[(i + 1) % nb]->lock_mode_fork);
	printf_m("\033[0;34m has taken a fork\033[0m\n", philo[i]->num);
	if (did_i_die(philo[i]) == true)
	{
		pthread_mutex_unlock(&philo[i]->lock_mode_fork);
		pthread_mutex_unlock(&philo[(i + 1) % nb]->lock_mode_fork);
		return ;
	}
	eat(philo, i, nb);
}

void	eat(t_philo **philo, int i, int nb)
{
	philo[i]->last_meal_timestamp = get_time();
	pthread_mutex_lock(&data()->init_lock);
	printf_m("\033[0;32m is eating \033[0m\n", philo[i]->num);
	pthread_mutex_unlock(&data()->init_lock);
	philo[i]->status = eating;
	sleep_ms(philo[i], data()->time_to_eat);
	philo[i]->ate++;
	pthread_mutex_unlock(&philo[(i + 1) % nb]->lock_mode_fork);
	pthread_mutex_unlock(&philo[i]->lock_mode_fork);
}

void	join_threads(void)
{
	int	i;

	i = 0;
	while (i < data()->nb_of_philos)
	{
		pthread_join(data()->philos[i]->id, NULL);
		i++;
	}
}
