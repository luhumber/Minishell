/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chsiffre <chsiffre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 18:55:07 by charles           #+#    #+#             */
/*   Updated: 2022/11/13 15:40:42 by chsiffre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t len)
{
	size_t			i;
	unsigned char	*char_dest;
	unsigned char	*char_src;

	char_dest = (unsigned char *) dest;
	char_src = (unsigned char *) src;
	i = -1;
	if (dest < src)
		while (++i < len)
			char_dest[i] = char_src[i];
	else if (dest > src)
		while (len--)
			char_dest[len] = char_src[len];
	return (char_dest);
}
