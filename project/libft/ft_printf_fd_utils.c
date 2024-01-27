/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_fd_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luhumber <luhumber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 14:48:17 by luhumber          #+#    #+#             */
/*   Updated: 2023/06/28 10:34:19 by luhumber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr_unsigned_fd(unsigned int n, int fd)
{
	if (n <= 9)
		return (ft_putchar_fd(n + '0', fd));
	return (ft_putnbr_fd(n / 10, fd) + ft_putchar_fd((n % 10) + '0', fd));
}

int	ft_printaddress_fd(void *address, int fd)
{
	unsigned long	address_long;
	int				i;
	char			str[17];
	char			*base;
	int				total;

	if (!address)
		return (ft_putstr_fd("0x0", fd));
	address_long = (long int)address;
	i = 0;
	base = "0123456789abcdef";
	total = 0;
	while (address_long)
	{
		str[i++] = base[address_long % 16];
		address_long /= 16;
	}
	total += ft_putstr_fd("0x", fd);
	while (--i >= 0)
		total += ft_putchar_fd(str[i], fd);
	return (total);
}

int	ft_base_fd(char *base, long int nbr, int fd)
{
	if (nbr < 0)
		return (ft_base_fd(base, 4294967296 + nbr, fd));
	if (nbr < 16)
		return (ft_putchar_fd(base[nbr % 16], fd));
	return (ft_base_fd(base, nbr / 16, fd) + ft_putchar_fd(base[nbr % 16], fd));
}
