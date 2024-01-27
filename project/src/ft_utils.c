/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luhumber <luhumber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 18:37:12 by lucas             #+#    #+#             */
/*   Updated: 2023/08/14 10:52:32 by luhumber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_compare_str(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if ((s1[i] != s2[i]) || (s2[i] != s1[i]))
			return (0);
		i++;
	}
	return (1);
}

int	ft_lsize(t_lst *lst)
{
	int	count;

	count = 0;
	while (lst != NULL)
	{
		lst = lst->next;
		count++;
	}
	return (count);
}

char	*ft_find_name(char *name, char *str)
{
	int	i;

	i = 0;
	while (str[i] && (str[i] != '=' && str[i] != '+'))
		i++;
	name = malloc(sizeof(char) * (i + 3));
	if (!name)
		return (NULL);
	i = 0;
	while (str[i] && (str[i] != '=' && str[i] != '+'))
	{
		name[i] = str[i];
		i++;
	}
	name[i] = '=';
	i++;
	name[i] = '\0';
	return (name);
}

int	ft_lstlen(t_lst *lst)
{
	int	count;

	count = 0;
	while (lst != NULL)
	{
		lst = lst->next;
		count++;
	}
	return (count);
}

int	list_progress(t_data *data)
{
	while (data->iterator && data->iterator->type != CMD)
	{
		if (data->iterator->type == PIPE && data->iterator->next)
		{
			data->iterator = data->iterator->next;
			if (data->iterator->type == PIPE)
				ft_print_error
					("bash: syntax error near unexpected token `||'", 1);
		}
		if (data->iterator->type == REDIR)
		{
			if (ft_which_redir(data) == 1)
			{
				g_error_last = 1;
				data->iterator = data->iterator->next;
				list_progress(data);
				return (1);
			}
			data->iterator = data->iterator->next;
		}
	}
	return (0);
}
