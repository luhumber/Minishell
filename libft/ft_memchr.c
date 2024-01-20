/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chsiffre <chsiffre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 21:10:47 by charles           #+#    #+#             */
/*   Updated: 2022/11/11 11:40:21 by chsiffre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*cast;

	cast = (unsigned char *) s;
	if (!cast || n == 0)
		return (NULL);
	while (n--)
	{
		if (*cast == (unsigned char) c)
			return (cast);
		cast++;
	}
	return (NULL);
}
