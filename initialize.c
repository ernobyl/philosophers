/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emichels <emichels@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 10:45:59 by emichels          #+#    #+#             */
/*   Updated: 2024/07/12 13:59:46 by emichels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	init_philo(int n, t_data *data)
{
	t_philo		philo;

	philo.n = n + 1;
	philo.fork_l = &data->fork[n];
	philo.fork_r = &data->fork[(n + 1) % data->n_philo];
	philo.t_eat = 0;
	philo.thread = 0;
	philo.last_eat = get_time_ms();
	return (philo);
}

t_data	*initialize(int argc, char **argv)
{
	int				i;
	t_data			*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->n_philo = philo_atol(argv[1]);
	data->t_todie = philo_atol(argv[2]);
	data->t_toeat = philo_atol(argv[3]);
	data->t_tosleep = philo_atol(argv[4]);
	data->stop = 0;
	pthread_mutex_init(&data->monitor, NULL);
	pthread_mutex_init(&data->m_print, NULL);
	if (argc == 6)
		data->n_eat = philo_atol(argv[5]);
	else
		data->n_eat = -1;
	//data->philo = malloc(sizeof(t_philo) * data->n_philo);
	i = -1;
	while (++i < data->n_philo)
	{
		pthread_mutex_init(&data->fork[i], NULL);
		data->philo[i] = init_philo(i, data);
		data->philo[i].data = data;
	}
	return (data);
}