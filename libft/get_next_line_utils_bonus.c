/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luhumber <luhumber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 12:27:50 by chsiffre          #+#    #+#             */
/*   Updated: 2023/08/01 10:45:03 by luhumber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen_2(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

char	*ft_strjoin_2(char *s1, char *s2)
{
	char	*ret;
	size_t	i;
	ssize_t	j;

	ret = malloc((ft_strlen_2(s1) + ft_strlen_2(s2) + 1) * sizeof(char));
	if (!ret)
		return (NULL);
	i = 0;
	while (s1 && s1[i])
	{
		ret[i] = s1[i];
		i++;
	}
	j = -1;
	while (s2 && s2[++j])
		ret[i + j] = s2[j];
	ret[i + j] = '\0';
	if (s1)
		free(s1);
	return (ret);
}

char	*ft_strchr_2(char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i])
	{
		if (s[i] == (unsigned char) c)
			return ((char *) &s[i]);
		i++;
	}
	if (c == '\0')
		return ((char *) &s[i]);
	return (NULL);
}
