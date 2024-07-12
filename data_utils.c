/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emichels <emichels@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 09:49:39 by emichels          #+#    #+#             */
/*   Updated: 2024/07/12 14:40:26 by emichels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time_ms(void)
{
	static unsigned long	time = 0;
	struct timeval			tv;

	gettimeofday(&tv, NULL);
	if (!time)
	{
		time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
		return (time);
	}
	return ((tv.tv_sec * 1000 + tv.tv_usec / 1000) - time);
}

void	ft_usleep(int ms)
{
	long	time;
	
	time = get_time_ms();
	while (get_time_ms() - time < ms)
		usleep(ms / 10);
}

void	free_data(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->n_philo)
		pthread_mutex_destroy(&data->fork[i]);
	pthread_mutex_destroy(&data->m_print);
	free(data);
}
