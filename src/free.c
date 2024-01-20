/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luhumber <luhumber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 11:12:27 by luhumber          #+#    #+#             */
/*   Updated: 2023/08/14 12:25:21 by luhumber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_cmd(char **cmd)
{
	int	i;

	i = -1;
	while (cmd && cmd[++i])
	{
		if (cmd[i])
			free(cmd[i]);
	}
	if (cmd)
		free(cmd);
}

void	*free_data(t_data *data)
{
	int	i;

	i = 0;
	i = 0;
	while (data->res_parse && data->res_parse[i])
	{
		if (data->res_parse[i])
			free(data->res_parse[i++]);
		else
			i++;
	}
	if (data->res_parse)
		free(data->res_parse);
	i = 0;
	while (data->res_split && data->res_split[i])
	{
		if (data->res_split[i])
			free(data->res_split[i++]);
		else
			i++;
	}
	if (data->res_split)
		free(data->res_split);
	return (NULL);
}

void	ft_to_free(t_data *data)
{
	int		i;
	t_lst	*next;

	next = NULL;
	while (data->lst != NULL)
	{
		next = data->lst->next;
		i = 0;
		while (data->lst->content[i])
		{
			if (data->lst->content[i])
				free(data->lst->content[i++]);
		}
		free(data->lst->content);
		free(data->lst);
		data->lst = next;
	}
	ft_close_end(data);
	data->in_redir = 0;
	data->out_redir = 0;
	data->i = 0;
	data->y = 0;
	data->ind = 0;
}

void	free_old_path(t_data *data, int end)
{
	int	i;

	if (end == 0)
	{
		i = 0;
		if (data->split_path)
			while (data->split_path[i])
				free(data->split_path[i++]);
		free(data->split_path);
	}
	i = 0;
	if (data->loop == 0)
	{
		data->env_path = NULL;
		return ;
	}
	while (data->env_path && data->env_path[i])
	{
		free(data->env_path[i]);
		i++;
	}
	if (data->env_path)
		free(data->env_path);
}
