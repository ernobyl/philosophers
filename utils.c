/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emichels <emichels@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 10:45:06 by emichels          #+#    #+#             */
/*   Updated: 2024/07/16 14:20:04 by emichels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	return_error(char *msg)
{
	printf("%s\n", msg);
	return (1);
}

long	philo_atol(const char *str)
{
	long	i;
	long	result;
	int		negative;
	int		sign;

	i = 0;
	result = 0;
	negative = 0;
	sign = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	while (str[i] == '-' || str[i] == '+')
	{
		if (str[i++] == '-')
			negative++;
		sign++;
	}
	if (sign > 1)
		return (0);
	while (str[i] >= '0' && str[i] <= '9')
		result = result * 10 + (str[i++] - '0');
	if (negative == 1 || result > INT_MAX)
		return (result * -1);
	return (result);
}

static void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*a;

	a = b;
	while (len--)
		*a++ = c;
	return (b);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	ptr = malloc(count * size);
	if (ptr == NULL)
		return (NULL);
	ft_memset(ptr, '\0', size);
	return (ptr);
}
