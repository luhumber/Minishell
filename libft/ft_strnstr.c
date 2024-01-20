/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chsiffre <chsiffre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 23:02:31 by charles           #+#    #+#             */
/*   Updated: 2022/11/12 12:02:46 by chsiffre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t n)
{
	size_t	i;

	if (!*needle)
		return ((char *) haystack);
	while (haystack && n > 0 && *haystack)
	{
		if ((unsigned char) *haystack == (unsigned char) *needle)
		{
			i = 0;
			while (needle[i] == haystack[i] && needle[i] && i < n)
				i++;
			if (!((unsigned char) needle[i]))
				return ((char *) haystack);
		}
		haystack++;
		n--;
	}
	return (0);
}
