/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_charset.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luhumber <luhumber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 21:01:54 by chsiffre          #+#    #+#             */
/*   Updated: 2023/08/03 14:58:57 by luhumber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	get_ac(char *str, char *charset, char c)
{
	int		i;
	int		count;

	count = 0;
	i = 0;
	while (str[i])
	{
		while (ft_charset(str[i], charset) && str[i])
			i++;
		if (str[i] && (str[i] == '\"' || str[i] == '\''))
		{
			c = str[i++];
			while (str[i] && str[i] != c)
				i++;
			if (str[i])
				i++;
			count++;
		}
		else if (str[i])
			skiping_one(str, charset, &i, &count);
		if (str[i] && !ft_charset(str[i], charset)
			&& str[i] != '\'' && str[i] != '\"')
			skiping_two(str, charset, &i, &count);
	}
	return (count + 1);
}

void	skiping_one(char *str, char *charset, int *i, int *count)
{
	(*count)++;
	while (!ft_charset(str[*i], charset)
		&& str[*i] && str[*i] != '\"' && str[*i] != '\'')
		(*i)++;
}

void	skiping_two(char *str, char *charset, int *i, int *count)
{
	while (str[*i] &&!ft_charset(str[*i], charset)
		&& str[*i] != '\'' && str[*i] != '\"')
		(*i)++;
	(*count)++;
}

char	*give_memory(char *str, char *charset, int *i, int i_str)
{
	int		len;
	char	*ret;

	ret = NULL;
	len = check_space(str, i, charset, i_str);
	if (len != 0)
	{
		if (i_str == 1)
			while (ft_charset(str[*i], charset))
				(*i)++;
		else
			while (ft_charset(str[*i], charset)
				&& str[(*i) + 1] != '\"' && str[(*i) + 1] != '\'')
				(*i)++;
		return (copy_str(i, str, len, ret));
	}
	len = check_quote(str, i, charset);
	if (len != 0)
		return (copy_str(i, str, len, ret));
	while (ft_charset(str[*i], charset))
		(*i)++;
	while (!ft_charset(str[*i + len], charset) && str[*i + len]
		&& str[*i + len] != '\'' && str[*i + len] != '\"')
		len++;
	return (copy_str(i, str, len, ret));
}

char	**ft_split_charset(char *str, char *charset)
{
	int		i;
	int		nb_str;
	char	**strs;
	int		j;
	char	c;

	c = 0;
	i = 0;
	j = 0;
	if (!str)
		return (NULL);
	nb_str = get_ac(str, charset, c);
	strs = malloc(nb_str * sizeof(char *));
	if (!strs)
		return (NULL);
	while (i < (nb_str - 1))
	{
		strs[i] = give_memory(str, charset, &j, i);
		i++;
	}
	strs[i] = 0;
	return (strs);
}
