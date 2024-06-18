/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 14:58:58 by root              #+#    #+#             */
/*   Updated: 2024/06/18 15:23:17 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_mutexes(t_mutex *mutex)
{
	if (pthread_mutex_init(&mutex->m_print, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&mutex->m_stop, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&mutex->m_eat, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&mutex->m_dead, NULL) != 0)
		return (1);
	return (0);
}

int	data_init(char **argv, t_data *data)
{
	data->n_philo = ft_atoi(argv[1]);
	data->t_todie = ft_atoi(argv[2]);
	data->t_toeat = ft_atoi(argv[3]);
	data->t_tosleep = ft_atoi(argv[4]);
	if (argv[5])
	{
		if ((data->n_eat = ft_atoi(argv[5])) == 0)
			return (1);
	}
	data->philo = malloc(sizeof(t_philo) * data->n_philo);
	
	return (0);
}
