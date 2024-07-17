/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emichels <emichels@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 10:45:59 by emichels          #+#    #+#             */
/*   Updated: 2024/07/17 12:03:21 by emichels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	init_philo(int n, t_data *data)
{
	t_philo		philo;

	philo.n = n + 1;
	philo.fork_l = &data->fork[n];
	philo.fork_r = &data->fork[(n + 1) % data->n_philo];
	philo.n_eaten = 0;
	philo.thread = 0;
	philo.last_eat = get_time_ms();
	return (philo);
}

static int	safe_init_mutexes(t_data *data)
{
	if (pthread_mutex_init(&data->monitor, NULL) != 0)
	{
		free(data);
		return (1);
	}
	if (pthread_mutex_init(&data->m_print, NULL) != 0)
	{
		pthread_mutex_destroy(&data->monitor);
		free(data);
		return (1);
	}
	return (0);
}

static int	safe_init_forks(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->n_philo)
	{
		if (pthread_mutex_init(&data->fork[i], NULL) != 0)
		{
			while (--i > -1)
				pthread_mutex_destroy(&data->fork[i]);
			free(data);
			return (1);
		}
		data->philo[i] = init_philo(i, data);
		data->philo[i].data = data;
	}
	return (0);
}

int	initialize(t_data *data, int argc, char **argv)
{
	data->n_philo = philo_atol(argv[1]);
	data->t_todie = philo_atol(argv[2]);
	data->t_toeat = philo_atol(argv[3]);
	data->t_tosleep = philo_atol(argv[4]);
	data->stop = 0;
	data->philo = ft_calloc(data->n_philo, (sizeof(t_philo)));
	if (data->philo == NULL)
		return (1);
	data->fork = ft_calloc(data->n_philo, (sizeof(pthread_mutex_t)));
	if (data->fork == NULL)
	{
		free(data->philo);
		return (1);
	}
	if (safe_init_mutexes(data) == 1)
		return (1);
	if (argc == 6)
		data->n_eat = philo_atol(argv[5]);
	else
		data->n_eat = -1;
	if (safe_init_forks(data) == 1)
		return (1);
	return (0);
}
