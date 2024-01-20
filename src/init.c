/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luhumber <luhumber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 15:39:59 by chsiffre          #+#    #+#             */
/*   Updated: 2023/08/14 14:24:59 by luhumber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_struct_env(t_data *data)
{
	int		i;
	t_env	*new;

	i = 0;
	while (data->env_path[i])
	{
		new = ft_new_env(data->env_path[i]);
		if (!new)
		{
			write(2, "malloc error\n", 14);
			exit (1);
		}
		ft_envadd_back(&data->env, new);
		i++;
	}
}

void	ft_init_data(t_data *data, char **envp)
{
	data->env_path = envp;
	data->env = NULL;
	data->iterator = NULL;
	data->in_redir = 0;
	data->out_redir = 0;
	data->savestdin = dup(0);
	data->savestdout = dup(1);
	ft_struct_env(data);
}

t_data	ft_init_struct(t_data data)
{
	data.line = NULL;
	data.lst = NULL;
	data.iterator = NULL;
	data.path = NULL;
	data.split_path = NULL;
	data.cmd = NULL;
	data.res_split = NULL;
	data.res_parse = NULL;
	data.i = 0;
	data.y = 0;
	data.f_quote = 0;
	data.quote = 0;
	data.ind = 0;
	data.x = 0;
	data.pipex = malloc(sizeof(t_pipe));
	if (!data.pipex)
		ft_error(&data, "malloc error\n", 1, 0);
	return (data);
}
