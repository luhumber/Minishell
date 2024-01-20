/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pre_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chsiffre <chsiffre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 16:18:45 by chsiffre          #+#    #+#             */
/*   Updated: 2023/08/03 14:48:09 by chsiffre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_pre_split(char *str)
{
	int		new_size;
	char	*copy;

	copy = ft_strdup(str);
	if (!copy)
		return (NULL);
	new_size = ft_strlen(str);
	new_size = resize_pre_split(copy, &new_size);
	if (quote_open(str))
		return (free(copy), free(str), NULL);
	free(str);
	str = ft_calloc((new_size + 1), sizeof(char));
	if (!str)
		return (NULL);
	str = ft_str_replace(str, copy, new_size);
	if (!str)
		return (free(copy), NULL);
	return (free(copy), str);
}

char	*ft_str_replace(char *str, char *copy, int new_size)
{
	int	i;
	int	y;

	y = 0;
	i = 0;
	while (y < new_size)
	{
		str = check_chevron(str, copy, &i, &y);
		str = check_pipes(str, copy, &i, &y);
	}
	str[y] = '\0';
	return (str);
}

char	*check_chevron(char *str, char *copy, int *i, int *y)
{
	if (copy[*i] && (copy[*i] == '<' || copy[*i] == '>'))
	{
		if (*i != 0 && copy[*i - 1] && copy[*i - 1] != ' '
			&& copy[*i - 1] != '<' && copy[*i - 1] != '>')
		{
			str[(*y)++] = ' ';
			while (copy[*i] && (copy[*i] == '<' || copy[*i] == '>'))
				str[(*y)++] = copy[(*i)++];
			if (copy[*i] != ' ')
				str[(*y)++] = ' ';
			if (copy[*i])
				str[(*y)++] = copy[(*i)++];
			return (str);
		}
		else if (copy[*i] && copy[*i + 1] && copy[*i + 1] != '<'
			&& copy[*i + 1] != '>' && copy[*i + 1] != ' ')
		{
			str[(*y)++] = copy[(*i)++];
			str[(*y)++] = ' ';
			str[(*y)++] = copy[(*i)++];
		}
	}
	return (str);
}

int	empty(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_is_not_space(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	ft_is_not_space(char c)
{
	if (c != ' ' && c != '\t' && c != '\n'
		&& c != '\v' && c != '\f' && c != '\r')
		return (1);
	return (0);
}
