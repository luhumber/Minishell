/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chsiffre <chsiffre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 15:03:10 by chsiffre          #+#    #+#             */
/*   Updated: 2023/03/15 17:01:31 by chsiffre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

int	ft_putstr_2(char *s)
{
	if (!s)
	{
		if (write(1, "(null)", 6) == -1)
			return (-1);
		return (6);
	}
	if (write(1, s, ft_strlen(s)) == -1)
		return (-1);
	return (ft_strlen(s));
}

int	ft_putchar_2(int c)
{
	if (write(1, &c, 1) == -1)
		return (-1);
	return (1);
}

int	ft_conv_hex(long int c, char *base)
{
	if (c < 0)
		return (ft_conv_hex(4294967296 + c, base));
	if (c < 16)
		return (ft_putchar_2(base[c % 16]));
	return (ft_conv_hex((c / 16), base) + ft_putchar_2(base[c % 16]));
}

int	ft_putnbr_2(int c)
{
	if (c == -2147483648)
		return (ft_putstr_2("-2147483648"));
	if (c < 0)
		return (ft_putchar_2('-') + ft_putnbr_2(-c));
	if (c <= 9)
		return (ft_putchar_2(c + '0'));
	return (ft_putnbr_2(c / 10) + ft_putchar_2((c % 10) + '0'));
}
