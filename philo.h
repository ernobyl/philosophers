/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emichels <emichels@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 10:45:25 by emichels          #+#    #+#             */
/*   Updated: 2024/07/12 13:59:56 by emichels         ###   ########.fr       */
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

# define FORK 1
# define EAT 2
# define SLEEP 3
# define THINK 4
# define DIE 5

typedef struct	s_philo
{
	int				n;
	int				t_eat;
	pthread_t		thread;
	long int		last_eat;
	struct s_data	*data;
	pthread_mutex_t	*fork_r;
	pthread_mutex_t	*fork_l;
	pthread_mutex_t	eat;
}					t_philo;

typedef struct	s_data
{
	int 	n_philo;
	int 	t_todie;
	int 	t_toeat;
	int 	t_tosleep;
	int 	n_eat;
	int		stop;
	//t_mutex	*mutex;
	t_philo	philo[200];
	int		philo_eat;
	pthread_mutex_t	m_print;
	pthread_mutex_t	monitor;
	pthread_mutex_t	fork[200];
}			t_data;

long	philo_atol(const char *str);
int		return_error(char *msg);
int		check_args(int argc, char **argv);
void	one_philo(char **argv);
long	get_time_ms(void);
void	ft_usleep(int ms);
t_data	*initialize(int argc, char **argv);
t_philo	init_philo(int n, t_data *data);
void	cycle(t_data *data);
void	print_action(t_philo philo, int action);
void	free_data(t_data *data);
int		min(int a, int b);
int		max(int a, int b);
int		check_death(t_philo *philo);
// int		mutex_philo_death(t_philo *philo, int nb);
// void	mutex_print(t_philo *philo, char *str);
// int		init_data(char **argv, t_data *data);
// int		init_mutexes(t_mutex *mutex);
// int		init_philos(t_data *data);
// void	*cycle(void *phi);

#endif