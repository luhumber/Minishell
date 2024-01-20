/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luhumber <luhumber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 14:47:18 by luhumber          #+#    #+#             */
/*   Updated: 2023/06/28 10:51:47 by luhumber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_printf_calls(va_list args, char type, int fd)
{
	int	total;

	total = 0;
	if (type == 'c')
		total += ft_putchar_fd(va_arg(args, int), fd);
	else if (type == 's')
		total += ft_putstr_fd(va_arg(args, char *), fd);
	else if (type == 'p')
		total += ft_printaddress_fd(va_arg(args, void *), fd);
	else if (type == 'd')
		total += ft_putnbr_fd(va_arg(args, int), fd);
	else if (type == 'i')
		total += ft_putnbr_fd(va_arg(args, int), fd);
	else if (type == 'u')
		total += ft_putnbr_unsigned_fd(va_arg(args, int), fd);
	else if (type == 'x')
		total += ft_base_fd("0123456789abcdef", va_arg(args, int), fd);
	else if (type == 'X')
		total += ft_base_fd("0123456789ABCDEF", va_arg(args, int), fd);
	else if (type == '%')
		total += ft_putchar_fd('%', fd);
	else
		total += ft_putchar_fd(type, fd);
	return (total);
}

int	ft_printf_fd(const char *s, int fd, ...)
{
	va_list	args;
	int		i;
	int		total;

	va_start(args, fd);
	i = 0;
	total = 0;
	if (write(1, 0, 0) == -1)
		return (va_end(args), -1);
	while (s[i])
	{
		if (s[i] == '%' && s[i + 1])
			total += ft_printf_calls(args, s[++i], fd);
		else
			total += ft_putchar_fd(s[i], fd);
		i++;
	}
	return (va_end(args), total);
}
