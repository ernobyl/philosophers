/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emichels <emichels@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 10:45:25 by emichels          #+#    #+#             */
/*   Updated: 2024/07/18 10:02:00 by emichels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <limits.h>
# include <sys/time.h>

# define FORK 1
# define EAT 2
# define SLEEP 3
# define THINK 4
# define DIE 5

typedef struct s_philo
{
	int				n;
	int				n_eaten;
	pthread_t		thread;
	long int		last_eat;
	struct s_data	*data;
	pthread_mutex_t	*fork_r;
	pthread_mutex_t	*fork_l;
}					t_philo;

typedef struct s_data
{
	int				n_philo;
	int				t_todie;
	int				t_toeat;
	int				t_tosleep;
	int				n_eat;
	int				stop;
	t_philo			*philo;
	pthread_mutex_t	m_print;
	pthread_mutex_t	monitor;
	pthread_mutex_t	*fork;
}					t_data;

void	*ft_calloc(size_t count, size_t size);
long	philo_atol(const char *str);
int		return_error(char *msg);
int		check_args(int argc, char **argv);
void	*routine(void *arg);
long	get_time_ms(void);
void	ft_usleep(int ms);
int		initialize(t_data *data, int argc, char **argv);
t_philo	init_philo(int n, t_data *data);
int		cycle(t_data *data);
void	print_action(t_philo philo, int action);
void	free_data(t_data *data);
int		check_death(t_philo *philo);

#endif