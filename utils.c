/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 15:02:39 by root              #+#    #+#             */
/*   Updated: 2024/06/18 15:25:43 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	return_error(char *msg)
{
	printf("%s\n", msg);
	return (1);
}

static int	ft_isdigit(int c)
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
