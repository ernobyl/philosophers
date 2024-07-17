/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_cycle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emichels <emichels@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 12:06:51 by emichels          #+#    #+#             */
/*   Updated: 2024/07/17 12:30:28 by emichels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	update_end(t_data *data)
{
	int	i;
	int	min;

	pthread_mutex_lock(&data->monitor);
	min = data->philo[0].n_eaten;
	i = -1;
	while (++i < data->n_philo)
	{
		if (get_time_ms() - data->philo[i].last_eat > data->t_todie)
		{
			if (!data->stop)
			{
				print_action(data->philo[i], DIE);
				data->stop = 1;
			}
			break ;
		}
		if (data->philo[i].n_eaten < min)
			min = data->philo[i].n_eaten;
	}
	if (min == data->n_eat)
		data->stop = 1;
	pthread_mutex_unlock(&data->monitor);
}

int	take_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->fork_l);
	if (check_death(philo))
		return (pthread_mutex_unlock(philo->fork_l), 0);
	print_action(*philo, FORK);
	pthread_mutex_lock(philo->fork_r);
	if (check_death(philo))
	{
		pthread_mutex_unlock(philo->fork_l);
		pthread_mutex_unlock(philo->fork_r);
		return (0);
	}
	print_action(*philo, FORK);
	pthread_mutex_lock(&philo->data->monitor);
	philo->last_eat = get_time_ms();
	print_action(*philo, EAT);
	pthread_mutex_unlock(&philo->data->monitor);
	ft_usleep(philo->data->t_toeat);
	philo->n_eaten++;
	return (1);
}

int	put_fork(t_philo *philo)
{
	pthread_mutex_unlock(philo->fork_l);
	pthread_mutex_unlock(philo->fork_r);
	if (check_death(philo))
		return (0);
	print_action(*philo, SLEEP);
	ft_usleep(philo->data->t_tosleep);
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
	if (philo->data->n_philo == 1)
	{
		print_action(*philo, FORK);
		ft_usleep(philo->data->t_todie);
		print_action(*philo, DIE);
	}
	else
	{
		if (philo->n % 2 == 0)
			ft_usleep(philo->data->t_toeat - 10);
		while (1)
		{
			if (!take_fork(philo))
				break ;
			if (!put_fork(philo))
				break ;
		}
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
	}
	while (1 && data->n_philo != 1)
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
