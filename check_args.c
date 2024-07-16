/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emichels <emichels@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:28:42 by emichels          #+#    #+#             */
/*   Updated: 2024/07/16 13:29:52 by emichels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	else
		return (0);
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
		if (philo_atol(argv[i]) < 0)
			return (1);
		i++;
	}
	return (0);
}
