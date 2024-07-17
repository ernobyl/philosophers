/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emichels <emichels@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 13:34:48 by emichels          #+#    #+#             */
/*   Updated: 2024/07/17 12:18:49 by emichels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

void	print_action(t_philo philo, int action)
{
	pthread_mutex_lock(&philo.data->m_print);
	if (philo.data->stop)
	{
		pthread_mutex_unlock(&philo.data->m_print);
		return ;
	}
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
