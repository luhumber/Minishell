/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chsiffre <chsiffre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 14:02:37 by charles           #+#    #+#             */
/*   Updated: 2022/11/10 10:28:16 by chsiffre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	char	*char_src;

	char_src = (char *) src;
	i = -1;
	j = ft_strlen(char_src);
	if (j + 1 < dstsize)
		while (++i < j + 1)
			dst[i] = char_src[i];
	else if (dstsize)
	{
		while (++i < dstsize - 1)
			dst[i] = char_src[i];
		dst[i] = 0;
	}
	return (j);
}
