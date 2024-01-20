/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chsiffre <chsiffre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 13:59:16 by charles           #+#    #+#             */
/*   Updated: 2022/11/13 15:39:23 by chsiffre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	len_dst;

	i = 0;
	j = 0;
	if (!src || !dst)
		return (0);
	len_dst = ft_strlen(dst);
	if (dstsize == 0 && src && dst)
		return (ft_strlen((char *)src));
	while (dst[i] != '\0' && i < dstsize)
		i++;
	while (src[j] != '\0' && i < dstsize - 1)
		dst[i++] = src[j++];
	if (dstsize != 0 && dstsize >= len_dst)
		dst[i] = '\0';
	if (dstsize < ft_strlen(dst))
		return (ft_strlen((char *)src) + dstsize);
	else
		return (ft_strlen((char *)src) + len_dst);
}
