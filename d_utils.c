/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   D_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skillian <skillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 16:44:56 by skillian          #+#    #+#             */
/*   Updated: 2022/04/25 23:06:42 by skillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

t_data	*data(void)
{
	static t_data	data;

	return (&data);
}

int	ft_atoi_v2(char *str)
/* adjusted function with no minus sign and 0 */
{
	long long int	res;

	while (*str == ' ' || *str == '\n' || *str == '\t'
		|| *str == '\v' || *str == '\f' || *str == '\r')
		str++;
	if (*str == '-')
		return (data()->arg_checker = false);
	if (int_min_max_checker(str) == false)
		return (data()->arg_checker = false);
	if (*str == '+')
		str++;
	res = 0;
	while (*str)
	{
		if (*str >= 48 && *str <= 57)
			res = res * 10 + *str - 48;
		else
			return (data()->arg_checker = false);
		str++;
	}
	if (res == 0)
		return (data()->arg_checker = false);
	return (res);
}

bool	int_min_max_checker(char *ptr)
{
	int					i;
	long long int		num;

	i = ft_strlen(ptr);
	if (i > 11)
		return (false);
	if (i < 10)
		return (true);
	num = ft_atoi(ptr);
	if (num > INT_MAX || num < INT_MIN)
		return (false);
	return (true);
}

void	printf_m(char *str, int i)
/* milli(gets printed), that's why time print is 0 ("ignores" nano seconds) */
{
	time_t	time;

	pthread_mutex_lock(&data()->print);
	if (data()->print_possible == true)
	{
		time = get_time_since_start();
		printf("%li ms	%i	%s", time, (i + 1), str);
	}
	pthread_mutex_unlock(&data()->print);
}

bool	init_routine(void)
{
	pthread_mutex_lock(&data()->init_lock);
	if (data()->init_routine == true)
	{
		pthread_mutex_unlock(&data()->init_lock);
		return (true);
	}
	pthread_mutex_unlock(&data()->init_lock);
	return (false);
}	
