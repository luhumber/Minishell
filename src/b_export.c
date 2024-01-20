/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_export.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luhumber <luhumber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 13:22:51 by luhumber          #+#    #+#             */
/*   Updated: 2023/08/14 12:25:15 by luhumber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	allocate_path(t_data *data)
{
	int		i;
	t_env	*tmp;

	i = 0;
	tmp = data->env;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

void	update_env(t_data *data)
{
	int		i;
	t_env	*tmp;
	int		size;

	tmp = data->env;
	free_old_path(data, 0);
	size = allocate_path(data);
	data->env_path = malloc(sizeof(char *) * (size + 1));
	if (!data->env_path)
		ft_error(data, "malloc error\n", 1, 1);
	i = 0;
	while (tmp)
	{
		if (tmp->name && tmp->value)
			data->env_path[i] = ft_strjoin(tmp->name, tmp->value);
		else if (tmp->name)
			data->env_path[i] = ft_strdup(tmp->name);
		tmp = tmp->next;
		i++;
	}
	data->env_path[i] = NULL;
	ft_get_env(data);
}

void	ft_print_export(t_data *data)
{
	t_env	*tmp;

	tmp = data->env;
	while (tmp)
	{
		printf("declare -x %s", tmp->name);
		if (tmp->value)
			printf("\"%s\"", tmp->value);
		printf("\n");
		tmp = tmp->next;
	}
	g_error_last = 0;
}

int	ft_while_export(t_data *data, int i)
{
	int	ret;

	ret = ft_check_exist(data, data->env, data->iterator->content[i]);
	if (data->iterator->content[i])
	{
		if (ret == -1)
			return (ft_export_error(data->iterator->content[i]), -1);
		else if (ret == 0)
			return (ft_add_var(data, data->iterator->content[i], 0), 0);
		else if (ret == 1)
			return (ft_add_var(data, data->iterator->content[i], 1), 0);
		else if (ret == 2)
			return (ft_add_var(data, data->iterator->content[i], 2), 2);
		else
			return (-1);
	}
	return (-1);
}

int	ft_export(t_data *data)
{
	int	i;
	int	error;

	i = 1;
	error = 0;
	if (!data->iterator->content[i])
		return (ft_print_export(data), 0);
	while (data->iterator->content[i])
	{
		if (ft_while_export(data, i) == -1)
			error = 1;
		i++;
	}
	if (error == 1)
		g_error_last = 1;
	return (1);
}
