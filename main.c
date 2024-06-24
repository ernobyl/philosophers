/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emichels <emichels@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 10:45:49 by emichels          #+#    #+#             */
/*   Updated: 2024/06/24 15:57:31 by emichels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data	data;
	t_mutex	mutex;

	if (check_args(argc, argv) == 1)
		return (return_error("arg count or format invalid"));
	if (init_data(argv, &data) == 1)
		return (return_error("failed to initialize data"));
	if (init_mutexes(&mutex) == 1)
	{
		free(data.philo);
		return (return_error("failed to initialize mutexes"));
	}
	data.mutex = &mutex;
	init_philos(&data);
	free_data(&data);
	return (0);
}
