/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charles <charles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 13:50:45 by chsiffre          #+#    #+#             */
/*   Updated: 2023/08/02 12:25:12 by charles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*resize_var(char *str, t_data *data)
{
	int	i;
	int	new_size;

	i = -1;
	new_size = 0;
	while (str[++i] && str[i] != '$')
		new_size++;
	while (str[i])
	{
		if (str[i] == '$')
			new_size = check_size_var(str, &i, &new_size, data);
		if (str[i] == '$')
			continue ;
		else if (str[i])
			i++;
	}
	return (malloc(sizeof(char ) * new_size + 1));
}

int	check_size_var(char *str, int *i, int *new_size, t_data *data)
{
	t_env	*tmp;
	int		z;

	z = -1;
	tmp = data->env;
	(*i)++;
	while (tmp)
	{
		if (ft_compare_var(str, tmp->name, *i))
		{
			z = -1;
			while (tmp->value[++z])
				(*new_size)++;
			while (ft_isalnum(str[*i]))
				(*i)++;
			return (*new_size);
		}
		tmp = tmp->next;
	}
	return (*new_size);
}

int	if_expand(char *str)
{
	int		ind;
	char	quote;
	char	f_quote;

	f_quote = 0;
	quote = 0;
	ind = -1;
	while (str[++ind])
	{
		if (str[ind] == '\"' || str[ind] == '\'')
		{
			if (f_quote == 0)
				f_quote = str[ind];
			quote = str[ind];
			while (str[++ind] != quote)
			{
				if (str[ind] == '$' && f_quote == '\"')
					return (1);
			}
		}
		else if (str[ind] == '$')
			return (1);
	}
	return (0);
}
