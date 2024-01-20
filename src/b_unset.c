/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_unset.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luhumber <luhumber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 11:23:07 by luhumber          #+#    #+#             */
/*   Updated: 2023/07/19 13:59:24 by luhumber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_envdelone(t_env *env)
{
	if (env)
	{
		free(env->name);
		free(env->value);
		free(env);
	}
}

int	ft_find_var(t_data *data, t_env *tmp, char *n_equal, char *name)
{
	t_env	*prev;

	prev = NULL;
	while (tmp)
	{
		if (ft_compare_str(tmp->name, n_equal)
			|| ft_compare_str(tmp->name, name))
		{
			if (prev == NULL)
				data->env = tmp->next;
			else
				prev->next = tmp->next;
			ft_envdelone(tmp);
			return (free(n_equal), 0);
		}
		prev = tmp;
		tmp = tmp->next;
	}
	return (1);
}

int	ft_unset(t_data *data)
{
	t_env	*tmp;
	char	*n_equal;
	int		len;
	int		i;

	tmp = data->env;
	i = 1;
	while (data->iterator->content[i])
	{
		len = ft_strlen(data->iterator->content[i]);
		if (data->iterator->content[i][len - 1] == '=')
		{
			ft_printf_fd
			("bash: %s: not a valid identifer\n", 2, data->iterator->content[i]);
			g_error_last = 1;
			return (1);
		}
		n_equal = ft_strjoin(data->iterator->content[i], "=");
		ft_find_var(data, tmp, n_equal, data->iterator->content[i]);
		i++;
	}
	g_error_last = 0;
	return (0);
}
