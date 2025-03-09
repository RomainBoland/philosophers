/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboland <rboland@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 17:52:09 by rboland           #+#    #+#             */
/*   Updated: 2025/03/09 17:52:09 by rboland          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	handle_overflow(int sign)
{
	if (sign == 1)
		return (INT_MAX);
	return (INT_MIN);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	result;
	int	sign;

	result = 0;
	sign = 1;
	i = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = (result * 10) + (str[i] - '0');
		if (result * sign > INT_MAX || result * sign < INT_MIN)
			return (handle_overflow(sign));
		i++;
	}
	return (result * sign);
}
