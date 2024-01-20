/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chsiffre <chsiffre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 17:36:40 by charles           #+#    #+#             */
/*   Updated: 2022/11/14 09:42:01 by chsiffre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	int		i;
	char	*s1;

	s1 = (char *) s;
	i = 0;
	while (n > 0)
	{
		s1[i] = (unsigned char) c;
		i++;
		n--;
	}
	return (s1);
}
