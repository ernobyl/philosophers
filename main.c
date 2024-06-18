/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 11:09:57 by emichels          #+#    #+#             */
/*   Updated: 2024/06/18 15:24:55 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// uint64_t	get_time_ms(void)
// {
// 	struct timeval	tv;

// 	if (gettimeofday(&tv, NULL))
// 		return (0);
// 	return ((tv.tv_sec * (uint64_t)1000) + (tv.tv_usec / 1000));
// }

// void	example(void)
// {
// 	uint64_t	start_time;
// 	uint64_t	now;

// 	start_time = get_time_ms();
// 	usleep(1000000);
// 	now = get_time_ms();
// 	printf("start time: %llu\n", start_time);
// 	printf("milliseconds since start: %llu\n", now - start_time);
// }

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
	data.mutex = &mutex;
	return (0);
}
