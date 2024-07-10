/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emichels <emichels@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 09:49:39 by emichels          #+#    #+#             */
/*   Updated: 2024/07/10 13:55:27 by emichels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	ft_usleep(int ms)
{
	long	time;
	
	time = get_time_ms();
	while (get_time_ms() - time < ms)
		usleep(500);
}

void	free_data(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->n_philo)
	{
		if (pthread_mutex_destroy(&data->philo[i].fork_l) != 0)
			printf("Error destroying fork_l mutex\n");
		if (data->philo[i].fork_r && pthread_mutex_destroy(data->philo[i].fork_r) != 0)
            printf("Error destroying fork_r mutex\n");
	}
	pthread_mutex_destroy(&data->m_print);
	pthread_mutex_destroy(&data->m_stop);
	pthread_mutex_destroy(&data->m_eat);
	pthread_mutex_destroy(&data->m_dead);
	free(data->philo);
}

int	mutex_philo_death(t_philo *philo, int nb)
{
	pthread_mutex_lock(&philo->data->m_dead);
	if (nb)
		philo->data->stop = 1;
	if (philo->data->stop)
	{
		pthread_mutex_unlock(&philo->data->m_dead);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->m_dead);
	return (0);
}

void	mutex_print(t_philo *philo, char *str)
{
	long	time;

	pthread_mutex_lock(&(philo->data->m_print));
	time = get_time_ms() - philo->data->start_time;
	if (!philo->data->stop && time >= 0 \
			&& time <= INT_MAX && !mutex_philo_death(philo, 0))
		printf("%ld %d %s", get_time_ms() - philo->data->start_time, philo->n, str);
	pthread_mutex_unlock(&(philo->data->m_print));
}