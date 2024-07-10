/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emichels <emichels@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 10:45:59 by emichels          #+#    #+#             */
/*   Updated: 2024/07/10 11:43:24 by emichels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// int	init_mutexes(t_mutex *mutex)
// {
// 	if (pthread_mutex_init(&mutex->m_print, NULL) != 0)
// 		return (1);
// 	if (pthread_mutex_init(&mutex->m_stop, NULL) != 0)
// 		return (1);
// 	if (pthread_mutex_init(&mutex->m_eat, NULL) != 0)
// 		return (1);
// 	if (pthread_mutex_init(&mutex->m_dead, NULL) != 0)
// 		return (1);
// 	return (0);
// }

int	init_data(char **argv, t_data *data)
{
	if (pthread_mutex_init(&data->m_print, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&data->m_stop, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&data->m_eat, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&data->m_dead, NULL) != 0)
		return (1);
	data->n_philo = philo_atol(argv[1]);
	data->t_todie = philo_atol(argv[2]);
	data->t_toeat = philo_atol(argv[3]);
	data->t_tosleep = philo_atol(argv[4]);
	if (argv[5])
	{
		if ((data->n_eat = philo_atol(argv[5])) == 0)
			return (1);
	}
	data->philo_eat = 0;
	data->philo = malloc(sizeof(t_philo) * data->n_philo);
	if (data->philo == NULL)
		return (1);
	return (0);
}

int	init_philos(t_data *data)
{
	int	i;

	data->start_time = get_time_ms();
	i = -1;
	while (++i < data->n_philo)
	{
		data->philo[i].n = i + 1;
		data->philo[i].last_eat = 0;
		data->philo[i].fork_r = NULL;
		data->philo[i].data = data;
		data->philo[i].m_count = 0;
		pthread_mutex_init(&(data->philo[i].fork_l), NULL);
		if (i == data->n_philo - 1)
			data->philo[i].fork_r = &data->philo[0].fork_l;
		else
			data->philo[i].fork_r = &data->philo[i - 1].fork_l;
		if (pthread_create(&data->philo[i].thread, NULL, &cycle, &(data->philo[i])) != 0)
			return (1);
	}
	i = -1;
	while (++i < data->n_philo)
		if (pthread_join(data->philo[i].thread, NULL) != 0)
			return (1);
	return (0);
}
