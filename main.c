/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emichels <emichels@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 11:09:57 by emichels          #+#    #+#             */
/*   Updated: 2024/05/20 12:22:49 by emichels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	return_error(char *msg)
{
	printf("%s\n", msg);
	return (1);
}
int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	else
		return (0);
}

int	ft_atoi(const char *str)
{
	int	counter;
	int	result;
	int	negative;
	int	sign;

	counter = 0;
	result = 0;
	negative = 0;
	sign = 0;
	while ((str[counter] >= 9 && str[counter] <= 13) || str[counter] == ' ')
		counter++;
	while (str[counter] == '-' || str[counter] == '+')
	{
		if (str[counter++] == '-')
			negative++;
		sign++;
	}
	if (sign > 1)
		return (0);
	while (str[counter] >= '0' && str[counter] <= '9')
		result = result * 10 + (str[counter++] - '0');
	if (negative == 1)
		return (result * -1);
	return (result);
}

uint64_t  get_time_ms(void)
{
  struct timeval  tv;

  if (gettimeofday(&tv, NULL))
    return (0);
  return ((tv.tv_sec * (uint64_t)1000) + (tv.tv_usec / 1000));


}

void    example()
{
    uint64_t    start_time;
    uint64_t    now;

    start_time = get_time_ms();
    usleep(1000000);
    now = get_time_ms();
	printf("start time: %ld\n", start_time);
    printf("milliseconds since start: %ld\n", now - start_time);
}

int	check_args(int argc, char **argv)
{
	int	i;
	int	k;

	if (argc != 5 && argc != 6)
		return (1);
	i = 1;
	while (argv[i])
	{
		k = 0;
		while (argv[i][k])
		{
			if (!ft_isdigit(argv[i][k]))
				return (1);
			k++;
		}
		if (ft_atoi(argv[i]) < 0)
			return (1);
		i++;
	}
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
	return (0);
}

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

int	main(int argc, char **argv)
{
	t_data	data;
	t_mutex	mutex;

	if (check_args(argc, argv) == 1)
		return (return_error("arg count or format invalid"));
	if (data_init(argv, &data) == 1)
		return (return_error("failed to initialize data"));
	if (init_mutexes(&mutex) == 1)
		return (return_error("failed to initialize mutexes"));
	return (0);
}
