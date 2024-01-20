/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chsiffre <chsiffre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 14:25:48 by chsiffre          #+#    #+#             */
/*   Updated: 2023/03/15 17:03:01 by chsiffre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H 

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>
# include "libft.h"

int			ft_putstr_2(char *s);
int			ft_putchar_2(int c);
int			ft_conv_hex(long int c, char *base);
int			ft_putnbr_2(int c);
int			ft_conv_address(void *mem);
unsigned	int	ft_putnbr_u(unsigned int n);
int			ft_printf(const char *s, ...);
int			ft_printf_2(va_list args, char c);

#endif
