/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emichels <emichels@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 10:45:49 by emichels          #+#    #+#             */
/*   Updated: 2024/07/15 14:53:26 by emichels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data	*data;

	if (philo_atol(argv[1]) > 200)
		return (return_error("max amount of philos = 200"));
	if (check_args(argc, argv) == 1)
		return (return_error("arg count or format invalid"));
	if (philo_atol(argv[1]) == 1)
		return (one_philo(argv), 0);
	data = initialize(argc, argv);
	if (!data)
		return (return_error("failed to initialize data"));
	cycle(data);
	return (0);
}
