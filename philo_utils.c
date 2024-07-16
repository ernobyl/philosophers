/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emichels <emichels@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 13:34:48 by emichels          #+#    #+#             */
/*   Updated: 2024/07/16 10:50:58 by emichels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	one_philo(char **argv)
{
	printf("0 1 has taken a fork\n");
	usleep(1000 * philo_atol(argv[2]));
	printf("%ld 1 died\n", philo_atol(argv[2]));
}

int	check_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->monitor);
	if (philo->data->stop)
	{
		pthread_mutex_unlock(&philo->data->monitor);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->monitor);
	return (0);
}

int	max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

int	min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

void	print_action(t_philo philo, int action)
{
	pthread_mutex_lock(&philo.data->m_print);
	if (philo.data->stop)
	{
		pthread_mutex_unlock(&philo.data->m_print);
		return ;
	}
	//pthread_mutex_lock(&philo.data->m_print);
	if (action == FORK)
		printf("%ld %d has taken a fork\n", get_time_ms(), philo.n);
	else if (action == EAT)
		printf("%ld %d is eating\n", get_time_ms(), philo.n);
	else if (action == SLEEP)
		printf("%ld %d is sleeping\n", get_time_ms(), philo.n);
	else if (action == THINK)
		printf("%ld %d is thinking\n", get_time_ms(), philo.n);
	else if (action == DIE)
		printf("%ld %d died\n", get_time_ms(), philo.n);
	pthread_mutex_unlock(&philo.data->m_print);
}
