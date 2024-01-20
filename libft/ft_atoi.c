/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luhumber <luhumber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 12:18:10 by charles           #+#    #+#             */
/*   Updated: 2023/08/01 10:45:42 by luhumber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_overflow(int sign)
{
	if (sign == -1)
		return (0);
	else
		return (-1);
}

static long long int	ft_conv(long long int res)
{
	if (res > INT_MAX)
		return (res - LLONG_MAX - 1);
	else if (res < INT_MIN)
		return (res - LLONG_MIN);
	else
		return (res);
}

int	ft_atoi(const char	*str)
{
	int				count;
	long long int	res;
	int				sign;

	count = 0;
	res = 0;
	sign = 1;
	while ((*str >= 9 && *str <= 13) || *str == ' ')
		str++;
	while ((*str == '-' || *str == '+') && ++count)
	{
		if (*str == '-')
			sign *= -1;
		if (count > 1)
			return (0);
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		if (res != (res * 10 + (*str - '0')) / 10)
			return ((int) ft_overflow(sign));
		res = (res * 10) + *str - '0';
		str++;
	}
	return ((int) ft_conv(res * sign));
}
