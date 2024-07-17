/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emichels <emichels@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 10:45:49 by emichels          #+#    #+#             */
/*   Updated: 2024/07/17 10:45:13 by emichels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (check_args(argc, argv) == 1)
		return (return_error("input error"));
	if (initialize(&data, argc, argv) == 1)
		return (return_error("failed to initialize data"));
	cycle(&data);
	return (0);
}
