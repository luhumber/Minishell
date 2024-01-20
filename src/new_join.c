/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_join.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chsiffre <chsiffre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 14:15:57 by chsiffre          #+#    #+#             */
/*   Updated: 2023/08/03 15:53:42 by chsiffre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	if_add_space(char *s1, char *s2, char *str)
{
	size_t	len;
	int		i;

	i = ft_strlen(s1) - 1;
	if (!s1[0])
		len = ft_strlen(s1) + ft_strlen(s2) + 1;
	else if (s1 && s1[i] != '\"' && s1[i] != '\''
		&& str[0] != '\'' && str[0] != '\"' && str[0] != ' ')
		len = ft_strlen(s1) + ft_strlen(s2) + 2;
	else
		len = ft_strlen(s1) + ft_strlen(s2) + 1;
	return (len);
}

char	*new_join(char const *s1, char const *s2, char *str)
{
	size_t	len_tot;
	char	*ret;
	int		i;
	int		j;

	i = 0;
	j = 0;
	len_tot = if_add_space((char *) s1, (char *) s2, str);
	ret = malloc(len_tot * sizeof(char));
	if (!ret)
		return (NULL);
	while (s1[i])
	{
		ret[i] = s1[i];
		i++;
	}
	if ((ft_strlen(s1) + ft_strlen(s2) + 2) == len_tot)
		ret[i++] = ' ';
	while (s2[j])
	{
		ret[i] = s2[j++];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

ssize_t	ft_strs_len(char **strs)
{
	size_t	i;

	i = 0;
	while (strs[i])
		i++;
	return (i);
}
