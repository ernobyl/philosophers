/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_cycle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emichels <emichels@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 12:06:51 by emichels          #+#    #+#             */
/*   Updated: 2024/07/15 15:48:50 by emichels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	update_end(t_data *data)
{
	int	i;
	int	min;

	pthread_mutex_lock(&data->monitor);
	min = data->philo[0].t_eat;
	i = -1;
	while (++i < data->n_philo)
	{
		if (get_time_ms() - data->philo[i].last_eat > data->t_todie)
		{
			print_action(data->philo[i], DIE);
			data->stop = 1;
			break ;
		}
		if (data->philo[i].t_eat < min)
			min = data->philo[i].t_eat;
	}
	if (min == data->n_eat)
		data->stop = 1;
	pthread_mutex_unlock(&data->monitor);
}

int	take_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->fork[min(philo->n - 1, philo->n
			% philo->data->n_philo)]);
	if (check_death(philo))
		return (pthread_mutex_unlock(&philo->data->fork[min(philo->n - 1,
						philo->n % philo->data->n_philo)]), 0);
	print_action(*philo, FORK);
	pthread_mutex_lock(&philo->data->fork[max(philo->n - 1, philo->n
			% philo->data->n_philo)]);
	if (check_death(philo))
	{
		pthread_mutex_unlock(&philo->data->fork[min(philo->n - 1, philo->n
				% philo->data->n_philo)]);
		pthread_mutex_unlock(&philo->data->fork[max(philo->n - 1, philo->n
				% philo->data->n_philo)]);
		return (0);
	}
	print_action(*philo, FORK);
	print_action(*philo, EAT);
	pthread_mutex_lock(&philo->data->monitor);
	philo->last_eat = get_time_ms();
	pthread_mutex_unlock(&philo->data->monitor);
	ft_usleep(philo->data, philo->data->t_toeat);
	philo->t_eat++;
	return (1);
}

int	put_fork(t_philo *philo)
{
	pthread_mutex_unlock(philo->fork_l);
	pthread_mutex_unlock(philo->fork_r);
	if (check_death(philo))
		return (0);
	print_action(*philo, SLEEP);
	ft_usleep(philo->data, philo->data->t_tosleep);
	if (check_death(philo))
		return (0);
	print_action(*philo, THINK);
	usleep(5);
	return (1);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	// if (philo->data->n_philo % 2 == 0)
	// 	ft_usleep(100);
	while (1)
	{
		if (!take_fork(philo))
			break ;
		if (!put_fork(philo))
			break ;
	}
	return (NULL);
}

void	cycle(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->n_philo)
	{
		pthread_create(&data->philo[i].thread, NULL, routine,
			&data->philo[i]);
		ft_usleep(data, data->t_toeat - 10);
	}
	while (1)
	{
		update_end(data);
		if (data->stop)
			break ;
	}
	i = -1;
	while (++i < data->n_philo)
		pthread_join(data->philo[i].thread, NULL);
	free_data(data);
}
