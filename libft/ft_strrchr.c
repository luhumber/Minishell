/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chsiffre <chsiffre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 16:48:58 by charles           #+#    #+#             */
/*   Updated: 2022/11/13 15:15:36 by chsiffre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	ssize_t	j;

	j = ft_strlen(s);
	if (!s)
		return (NULL);
	while (j >= 0)
	{
		if (s[j] == (unsigned char)c)
			return ((char *) s + j);
		j--;
	}
	return (NULL);
}
