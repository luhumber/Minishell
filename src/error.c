/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luhumber <luhumber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 21:39:01 by lucas             #+#    #+#             */
/*   Updated: 2023/08/14 12:25:29 by luhumber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_error(t_data *data, char *str, int exit_code, int parse)
{
	char	*join;

	join = ft_strjoin("bash: ", str);
	write(2, join, ft_strlen(join));
	free(join);
	ft_to_free(data);
	if (parse == 1)
		free_data(data);
	ft_free_for_end(data);
	g_error_last = exit_code;
	exit(g_error_last);
}

int	ft_print_error(char *str, int error_code)
{
	char	*join;

	join = ft_strjoin("bash: ", str);
	perror(join);
	free(join);
	if (error_code != 0)
		g_error_last = error_code;
	return (1);
}

int	ft_write_error(char *str)
{
	char	*join;

	join = ft_strjoin("bash: ", str);
	write(2, join, ft_strlen(join));
	write(2, "\n", 2);
	free(join);
	return (1);
}

int	ft_cmd_error(char *str)
{
	char	*join;

	g_error_last = 127;
	join = ft_strjoin(str, ": command not found\n");
	write(2, join, ft_strlen(join));
	free(join);
	return (1);
}

int	ft_free_for_end(t_data *data)
{
	int		i;
	t_env	*next;

	i = -1;
	next = NULL;
	while (data->split_path && data->split_path[++i])
		free(data->split_path[i]);
	free(data->split_path);
	while (data->env)
	{
		next = data->env->next;
		free(data->env->name);
		free(data->env->value);
		free(data->env);
		data->env = next;
	}
	if (data->line)
		free(data->line);
	free_old_path(data, 1);
	ft_close_end(data);
	close(data->savestdin);
	close(data->savestdout);
	rl_clear_history();
	free(data->pipex);
	return (0);
}
