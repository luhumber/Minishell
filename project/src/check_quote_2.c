/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quote_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chsiffre <chsiffre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 15:14:00 by charles           #+#    #+#             */
/*   Updated: 2023/08/14 15:04:07 by chsiffre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_int_len(int n)
{
	int	i;
	int	y;

	i = 1;
	if (n < 0)
	{
		y = -n;
		i++;
	}
	else
		y = n;
	while (y >= 10)
	{
		y = y / 10;
		i++;
	}
	return (i);
}

char	*resize_quote(char *str, t_data *data)
{
	int		i;
	int		new_size;
	char	quote;

	i = -1;
	quote = 0;
	new_size = 0;
	while (str[++i])
	{
		if (str[i] && (str[i] == '\'' || str[i] == '\"'))
		{
			quote = str[i++];
			while (str[i] && str[i] != quote)
			{
				check_size(str, &i, &new_size, data);
				if (str[i])
					i++;
			}
		}
		else
			new_size++;
	}
	return (malloc(sizeof (char) * new_size + 1));
}

void	check_size(char *str, int *i, int *new_size, t_data *data)
{
	if (str[*i] == '$' && str[*i + 1] && str[*i + 1] == '?')
	{
		while (str[*i] && str[*i + 1]
			&& str[*i + 2] && (str[*i] == '$' && str[*i + 1] == '?'))
		{
			(*new_size) += ft_int_len(g_error_last);
			(*i)++;
		}
	}
	else if (str[*i] == '$' && if_expand(str) && is_var(str, *i, data, str))
		(*new_size) += var_exist(str, i, data);
	else if (str[*i] == '$' && if_expand(str) && !is_var(str, *i, data, str))
	{
		while (str[*i] && ft_isalnum(str[*i]))
			(*i)++;
	}
	else
		(*new_size)++;
}

void	*check_token(char *str, int *i, char *ret, t_data *data)
{
	if (str[*i] == '$' && str[(*i) + 1] && str[(*i) + 1] == '?')
		return (ret = ft_convert_error(str, ret), ret);
	else if (str[*i] == '$' && 
		if_expand(str) && is_var(str, *i, data, ret))
		ret = replace_var(str, ret, i, data);
	else if (str[*i] == '$' && 
		if_expand(str) && !is_var(str, *i, data, ret))
		ft_skipping_var(str, i);
	else if (str[*i])
		ret[data->ind++] = str[(*i)++];
	return (0);
}

char	*ft_check_quote_var(char *str, int i, char	*ret, t_data *data)
{
	int	quote;

	quote = 0;
	while (str[i])
	{
		if (str[i] == '\"' || str[i] == '\'')
		{
			quote = str[(i)++];
			while (str[i] && str[i] != quote)
				check_token(str, &i, ret, data);
		}
		else
			ret[data->ind++] = str[i++];
	}
	ret[data->ind] = '\0';
	data->ind = 0;
	return (ret);
}
