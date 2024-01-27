/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luhumber <luhumber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 15:04:56 by charles           #+#    #+#             */
/*   Updated: 2023/08/01 10:45:34 by luhumber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_str(char *str, char c)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] == c && str[i])
			i++;
		while (str[i] != c && str[i])
		{
			i++;
			if (str[i] == c || !str[i])
				count++;
		}
	}
	return (count);
}

static char	*give_memory(char *str, int *j, char c)
{
	int		i;
	int		len;
	char	*dest;

	len = 0;
	i = 0;
	while (str[*j] == c)
		(*j)++;
	while (str[*j + len] != c && str[*j + len])
		len++;
	dest = malloc((len + 1) * sizeof(char));
	if (!dest)
		return (NULL);
	while (i < len)
	{
		dest[i] = str[*j];
		i++;
		(*j)++;
	}
	dest[i] = 0;
	return (dest);
}

static void	*free_tab(char **tab, int i)
{
	while (i > -1)
		free(tab[i--]);
	free(tab);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	char	**ret;
	int		nb_str;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	nb_str = ft_count_str((char *) s, c);
	ret = malloc((nb_str + 1) * sizeof(char *));
	if (!ret)
		return (NULL);
	while (i < nb_str)
	{
		ret[i] = give_memory((char *) s, &j, c);
		if (!ret[i])
			return (free_tab(ret, i));
		i++;
	}
	ret[i] = 0;
	return (ret);
}
