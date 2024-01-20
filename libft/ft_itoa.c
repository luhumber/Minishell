/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luhumber <luhumber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 09:54:11 by charles           #+#    #+#             */
/*   Updated: 2023/08/01 10:45:19 by luhumber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	int_len(int n)
{
	int	i;
	int	y;

	i = 1;
	if (n < 0)
	{
		y = -n;
		i++;
	}
	else
		y = n;
	while (y >= 10)
	{
		y = y / 10;
		i++;
	}
	return (i);
}

static char	*ft_itoa_2(long y, long n, int i)
{
	char	*dest;

	dest = malloc((i + 1) * sizeof(char));
	if (!dest)
		return (NULL);
	if (n == 0)
	{
		dest[1] = '\0';
		dest[0] = 48;
		return (dest);
	}
	dest[i] = '\0';
	i--;
	while (i >= 0)
	{
		dest[i--] = (y % 10) + '0';
		y = y / 10;
	}
	if (n < 0)
		dest[0] = '-';
	return (dest);
}

char	*ft_itoa(int n)
{
	long	i;
	int		y;

	if (n == -2147483648)
	{
		return (ft_strdup("-2147483648"));
	}
	else
		i = int_len(n);
	if (n < 0 && n != -2147483648)
		y = -n;
	else
		y = n;
	return (ft_itoa_2(y, n, i));
}
