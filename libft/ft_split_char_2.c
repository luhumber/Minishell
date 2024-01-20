/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_char_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chsiffre <chsiffre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 14:48:27 by chsiffre          #+#    #+#             */
/*   Updated: 2023/07/19 15:58:45 by chsiffre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "libft.h"
#include "../include/minishell.h"

int	check_quote(char *str, int *index, char *charset)
{
	int	size;
	int	i;

	i = (*index);
	size = 0;
	while (str[(*index)])
	{
		while (str[*index] && ft_charset(str[*index], charset))
			(*index)++;
		if (str[(*index)] && (str[(*index)] == '\"' || str[(*index)] == '\''))
		{
			size = skipping_quote(str[*index], str, index);
			(*index) = i;
			return (size + 2);
		}
		else
		{
			(*index) = i;
			return (0);
		}
	}
	(*index) = i;
	return (0);
}

int	check_space(char *str, int *index, char *charset, int i_str)
{
	int		i;
	int		len;
	char	c;

	c = 0;
	i = *index;
	len = 0;
	while (str[i])
	{
		while (str[i] && ft_charset(str[i], charset))
			i++;
		if (str[i] && (str[i] == '\"' || str[i] == '\''))
		{
			if (i != 0 && str[i] && str[i - 1]
				&& str[i - 1] == ' ' && i_str != 1)
				len++;
			c = str[i++];
			while (str[i++] != c && str[i])
				len++;
			return (len + 2);
		}
		else
			return (0);
	}
	return (0);
}

char	*copy_str(int *index, char *str, int len, char *ret)
{
	int	i;

	i = 0;
	ret = malloc((len + 1) * sizeof(char));
	if (!ret)
		return (NULL);
	while (i < len)
	{
		ret[i] = str[*index];
		i++;
		(*index)++;
	}
	ret[i] = '\0';
	return (ret);
}

int	skipping_quote(char c, char *str, int *i)
{
	int	size;

	size = 0;
	(*i)++;
	while (str[*i] != c && str[*i])
	{
		(*i)++;
		size++;
	}
	return (size);
}

int	ft_charset(char c, char *charset)
{
	int	i;

	i = 0;
	while (charset[i])
	{
		if (c == charset[i])
			return (1);
		i++;
	}
	return (0);
}
