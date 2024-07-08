/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emichels <emichels@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 11:44:31 by emichels          #+#    #+#             */
/*   Updated: 2024/07/03 10:56:45 by emichels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

uint64_t	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * (uint64_t)1000) + (tv.tv_usec / 1000));
}

void	ft_usleep(int ms)
{
	uint64_t	time;
	
	time = get_time_ms();
	while (get_time_ms() - time < (unsigned int)ms)
		usleep(ms / 10);
}

void	free_data(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_philo)
	{
		pthread_mutex_destroy(&data->philo[i].fork_l);
		pthread_mutex_destroy(data->philo[i].fork_r);
		i++;
	}
	free(data->philo);
	pthread_mutex_destroy(&data->mutex->m_print);
	pthread_mutex_destroy(&data->mutex->m_stop);
	pthread_mutex_destroy(&data->mutex->m_eat);
	pthread_mutex_destroy(&data->mutex->m_dead);
}

int	mutex_philo_death(t_philo *philo, int nb)
{
	pthread_mutex_lock(&philo->data->mutex->m_dead);
	if (nb)
		philo->data->stop = 1;
	if (philo->data->stop)
	{
		pthread_mutex_unlock(&philo->data->mutex->m_dead);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->mutex->m_dead);
	return (0);
}

void	mutex_print(t_philo *philo, char *str)
{
	uint64_t	time;

	pthread_mutex_lock(&(philo->data->mutex->m_print));
	time = get_time_ms() - philo->data->start_time;
	if (!philo->data->stop && (long)time >= 0 \
			&& (long)time <= INT_MAX && !mutex_philo_death(philo, 0))
		printf("%lu %d %s", get_time_ms() - philo->data->start_time, philo->n, str);
	pthread_mutex_unlock(&(philo->data->mutex->m_print));
}