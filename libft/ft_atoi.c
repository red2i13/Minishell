/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenmakh <rbenmakh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 21:22:32 by rbenmakh          #+#    #+#             */
/*   Updated: 2024/09/12 19:40:43 by rbenmakh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

long	ft_atoi(const char *nptr)
{
	int		i;
	long	result;
	int		sign;

	sign = 1;
	i = 0;
	result = 0;
	while (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign = -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		result = result * 10 + nptr[i] - '0';
		if ((result > 2147483647 && sign == 1) || (result < -2147483648
				&& sign == -1))
			return (__LONG_MAX__);
		i++;
	}
	return (result * sign);
}
