/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luhumber <luhumber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 13:06:56 by charles           #+#    #+#             */
/*   Updated: 2023/08/03 16:08:13 by luhumber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len_tot;
	char	*ret;
	int		i;
	int		j;

	i = 0;
	j = 0;
	len_tot = ft_strlen((char *) s1) + ft_strlen((char *) s2) + 1;
	ret = malloc(len_tot * sizeof(char) + 20);
	if (!ret)
		return (NULL);
	while (s1[i])
	{
		ret[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		ret[i] = s2[j++];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}
