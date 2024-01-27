/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chsiffre <chsiffre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 14:19:07 by charles           #+#    #+#             */
/*   Updated: 2023/08/14 15:05:07 by chsiffre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_return_error_last(char *ret, char *str, int i, int y)
{
	ret = "";
	while (str[i])
	{
		if (str[i] && str[i] == '\"')
			i++;
		while (str[i] && str[i] == '$')
		{
			ret = ft_strjoin((char *) ret, ft_itoa(g_error_last));
			if (!ret)
				return (NULL);
			while (ret[y])
				y++;
			if (str[i + 1])
				i = i + 2;
		}
		if (str[i] && str[i] == '\"' && !str[i + 1])
			i++;
		else if (str[i] && str[i] != '\"')
			ret[y++] = str[i];
		if (str[i])
			i++;
	}
	ret[y] = '\0';
	return (ret);
}

int	ft_count_other_char(char *str)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			count += ft_int_len(g_error_last);
			if (str[i + 1])
				i = i + 2;
		}
		else if (str[i] != '\"')
		{
			count++;
			if (str[i])
				i++;
		}
		else
			i++;
	}
	return (count);
}

char	*ft_convert_error(char *str, char *ret)
{
	int	i;
	int	y;

	y = 0;
	i = 0;
	if (ret)
		free(ret);
	ret = malloc(ft_count_other_char(str) + 1 * sizeof (char));
	if (!ret)
		return (NULL);
	return (ft_return_error_last(ret, str, i, y));
}

void	ft_skipping_var(char *str, int *i)
{
	(*i)++;
	while (str[*i] && ft_isalnum(str[*i]))
		(*i)++;
}

char	*del_quote(char *str, char *ret, t_data *data)
{
	int	i;

	i = 0;
	ret = ft_check_quote_var(str, i, ret, data);
	return (ret);
}
