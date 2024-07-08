/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emichels <emichels@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 10:45:25 by emichels          #+#    #+#             */
/*   Updated: 2024/07/08 14:46:47 by emichels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <stdint.h>
# include <limits.h>
# include <sys/time.h>
# include <stdbool.h>

typedef struct	s_philo
{
	int				n;
	int				m_count;
	bool			is_eating;
	pthread_t		thread;
	long int		last_eat;
	struct s_data	*data;
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
	uint64_t	start_time;
	int 		n_philo;
	int 		t_todie;
	int 		t_toeat;
	int 		t_tosleep;
	int 		n_eat;
	t_mutex		*mutex;
	t_philo		*philo;
	int			stop;
	int			philo_eat;
}				t_data;

long		philo_atol(const char *str);
int			return_error(char *msg);
int			check_args(int argc, char **argv);
uint64_t	get_time_ms(void);
void		ft_usleep(int ms);
int			mutex_philo_death(t_philo *philo, int nb);
void		mutex_print(t_philo *philo, char *str);
int			init_data(char **argv, t_data *data);
int			init_mutexes(t_mutex *mutex);
int			init_philos(t_data *data);
void		*cycle(void *phi);
void		free_data(t_data *data);

#endif