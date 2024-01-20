/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chsiffre <chsiffre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 14:27:12 by chsiffre          #+#    #+#             */
/*   Updated: 2023/03/15 17:00:51 by chsiffre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *s, ...)
{
	int		i;
	int		total;
	va_list	s_args;

	total = 0;
	i = 0;
	va_start(s_args, s);
	if (write(1, 0, 0) != 0)
	{
		va_end(s_args);
		return (-1);
	}
	while (s[i])
	{
		if (s[i] == '%' && s[i + 1])
			total += ft_printf_2(s_args, s[++i]);
		else
			total += ft_putchar_2(s[i]);
		i++;
	}
	va_end(s_args);
	return (total);
}

int	ft_printf_2(va_list args, char c)
{
	if (c == 'c')
		return (ft_putchar_2(va_arg(args, int)));
	else if (c == 's')
		return (ft_putstr_2(va_arg(args, char *)));
	else if (c == 'p')
		return (ft_conv_address(va_arg(args, void *)));
	else if (c == 'd')
		return (ft_putnbr_2(va_arg(args, int)));
	else if (c == 'i')
		return (ft_putnbr_2(va_arg(args, int)));
	else if (c == 'u')
		return (ft_putnbr_u(va_arg(args, unsigned int)));
	else if (c == 'x')
		return (ft_conv_hex(va_arg(args, int), "0123456789abcdef"));
	else if (c == 'X')
		return (ft_conv_hex(va_arg(args, int), "0123456789ABCDEF"));
	else if (c == '%')
		return (ft_putchar_2('%'));
	else
		return (ft_putchar_2(c));
}
