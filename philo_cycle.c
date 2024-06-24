/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_cycle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emichels <emichels@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 12:06:51 by emichels          #+#    #+#             */
/*   Updated: 2024/06/24 16:26:32 by emichels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	mutex_iseating(t_philo *philo)
{
	mutex_print(philo, " is eating\n");
	pthread_mutex_lock(&(philo->data->mutex->m_eat));
	philo->last_eat = get_time_ms();
	philo->m_count++;
	pthread_mutex_unlock(&(philo->data->mutex->m_eat));
	ft_usleep(philo->data->t_toeat);
	pthread_mutex_unlock((philo->fork_r));
	pthread_mutex_unlock(&(philo->fork_l));
	mutex_print(philo, " is sleeping\n");
	ft_usleep(philo->data->t_tosleep);
	mutex_print(philo, " is thinking\n");
}

static void	mutex_hasfork(t_philo *philo)
{
	pthread_mutex_lock(&(philo->fork_l));
	mutex_print(philo, " has taken a fork\n");
	if (philo->data->n_philo == 1)
	{
		ft_usleep(philo->data->t_todie * 2);
		return ;
	}
	pthread_mutex_lock((philo->fork_r));
	mutex_print(philo, " has taken a fork\n");
}

static void	*mutex_isdead(void *phi)
{
	t_philo	*philo;

	philo = (t_philo *)phi;
	ft_usleep(philo->data->t_todie + 1);
	pthread_mutex_lock(&philo->data->mutex->m_eat);
	pthread_mutex_lock(&philo->data->mutex->m_stop);
	if (!mutex_philo_death(philo, 0) && (long)get_time_ms() - \
			philo->last_eat >= ((long)philo->data->t_todie))
	{
		pthread_mutex_unlock(&philo->data->mutex->m_eat);
		pthread_mutex_unlock(&philo->data->mutex->m_stop);
		mutex_print(philo, " died\n");
		mutex_philo_death(philo, 1);
	}
	pthread_mutex_unlock(&philo->data->mutex->m_eat);
	pthread_mutex_unlock(&philo->data->mutex->m_stop);
	return (NULL);
}

void	*cycle(void *phi)
{
	t_philo		*philo;
	pthread_t	t;

	philo = (t_philo *)phi;
	if (philo->n % 2 == 0)
		ft_usleep(philo->data->t_toeat / 10);
	while (!mutex_philo_death(philo, 0))
	{
		pthread_create(&t, NULL, mutex_isdead, phi);
		mutex_hasfork(philo);
		mutex_iseating(philo);
		pthread_detach(t);
		if (philo->m_count == philo->data->n_eat)
		{
			pthread_mutex_lock(&philo->data->mutex->m_stop);
			if (++philo->data->philo_eat == philo->data->n_philo)
			{
				pthread_mutex_unlock(&philo->data->mutex->m_stop);
				mutex_philo_death(philo, 2);
			}
			pthread_mutex_unlock(&philo->data->mutex->m_stop);
			return (NULL);
		}
	}
	return (NULL);
}