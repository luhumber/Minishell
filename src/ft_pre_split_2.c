/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pre_split_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chsiffre <chsiffre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 15:59:24 by chsiffre          #+#    #+#             */
/*   Updated: 2023/07/19 16:09:02 by chsiffre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*check_pipes(char *str, char *copy, int *i, int *y)
{
	if (copy[*i] && copy[*i + 1] && (copy[*i] == '|' && copy[*i + 1] == '|'))
		return (NULL);
	if ((copy[*i] && copy[*i] != ' ' && copy[*i + 1]
			&& copy[*i + 1] == '|') || (copy[*i] == '|' && copy[*i + 1] != ' '))
	{
		if (copy[*i])
			str[(*y)++] = copy[(*i)++];
		str[(*y)++] = ' ';
	}
	else
		str[(*y)++] = copy[(*i)++];
	return (str);
}

int	quote_open(char *str)
{
	int		i;
	char	quote;

	quote = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			quote = str[i++];
			while (str[i] != quote && str[i])
				i++;
			if (!str[i])
				return (1);
		}
		i++;
	}
	return (0);
}

int	resize_pre_split(char *str, int *new_size)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '<' || str[i] == '>')
		{
			if (!str[i + 1])
				return (0);
			if (str[i + 1] && str[i + 1] != '<'
				&& str[i + 1] != '>' && str[i + 1] != ' ')
				(*new_size)++;
			if (i != 0 && str[i - 1] && str[i - 1] != ' ')
				(*new_size)++;
		}
		if (i != 0 && str[i] && str[i] == '|' && str[i - 1] != ' ')
			(*new_size)++;
		if (str[i] && str[i] == '|' && str[i + 1] && str[i + 1] != ' ')
			(*new_size)++;
	}
	return (*new_size);
}
