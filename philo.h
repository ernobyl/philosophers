/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emichels <emichels@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 11:12:46 by emichels          #+#    #+#             */
/*   Updated: 2024/05/20 12:08:23 by emichels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdint.h>
#include <sys/time.h>

typedef struct	s_data
{
	int n_philo;
	int t_todie;
	int t_toeat;
	int t_tosleep;
	int n_eat;
}		t_data;

typedef struct	s_mutex
{
	pthread_mutex_t	m_print;
	pthread_mutex_t	m_stop;
	pthread_mutex_t	m_eat;
	pthread_mutex_t	m_dead;
}					t_mutex;



#endif