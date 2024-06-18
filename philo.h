/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 11:12:46 by emichels          #+#    #+#             */
/*   Updated: 2024/06/18 15:26:17 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <stdint.h>
# include <sys/time.h>
# include <stdbool.h>

typedef struct	s_philo
{
	int				n;
	int				m_count;
	bool			is_eating;
	pthread_t		thread;
	long int		last_eat;
	struct l_info	*info;
	pthread_mutex_t	*fork_r;
	pthread_mutex_t	fork_l;
}					t_philo;

typedef struct	s_mutex
{
	pthread_mutex_t	m_print;
	pthread_mutex_t	m_stop;
	pthread_mutex_t	m_eat;
	pthread_mutex_t	m_dead;
}					t_mutex;

typedef struct	s_data
{
	int 	n_philo;
	int 	t_todie;
	int 	t_toeat;
	int 	t_tosleep;
	int 	n_eat;
	t_mutex	*mutex;
	t_philo	*philo;
}			t_data;

int	ft_atoi(const char *str);
int	return_error(char *msg);
int	check_args(int argc, char **argv);
int	data_init(char **argv, t_data *data);
int	init_mutexes(t_mutex *mutex);

#endif