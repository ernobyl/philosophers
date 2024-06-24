/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emichels <emichels@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 11:44:31 by emichels          #+#    #+#             */
/*   Updated: 2024/06/24 12:03:56 by emichels         ###   ########.fr       */
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
	while (get_time_ms() - time < ms)
		usleep(ms / 10);
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
	time = timestamp() - philo->data->start_time;
	if (!philo->data->stop && time >= 0 \
			&& time <= INT_MAX && !is_dead(philo, 0))
		printf("%llu %d %s", timestamp() - philo->data->start_time, philo->n, str);
	pthread_mutex_unlock(&(philo->data->mutex->m_print));
}