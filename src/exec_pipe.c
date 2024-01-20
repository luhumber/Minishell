/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luhumber <luhumber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 09:24:22 by luhumber          #+#    #+#             */
/*   Updated: 2023/08/14 10:53:09 by luhumber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**command_error(t_data *data)
{
	char	**cmd;
	int		i;

	i = 0;
	while (data->iterator->content[i])
		i++;
	cmd = malloc(sizeof(char *) * (i + 1));
	if (!cmd)
	{
		free(data->pipex->tab_pid);
		free(data->pipex->tab_fd);
		ft_error(data, "malloc error\n", 1, 1);
	}
	if (check_built(data))
		return (fill_built(data, cmd), cmd);
	cmd = ft_cmd_options(data, cmd, data->iterator->content[0]);
	if ((cmd[0] != NULL) && (is_executable(cmd[0]) == 0))
		return (cmd);
	if (!data->iterator->next && cmd == NULL)
		data->pipex->last = 127;
	else if (!data->iterator->next)
		data->pipex->last = g_error_last;
	free_cmd(cmd);
	return (NULL);
}

int	ft_exec_pipe(t_data *data, int fd[2], char **cmd)
{
	int	i;

	close(fd[0]);
	if (ft_make_dup(data) == 1)
		exit (1);
	ft_dup_pipe(data);
	i = ft_builtins(data);
	if (i == -1 || i == 1)
	{
		free_cmd(cmd);
		close(data->pipex->prev_fd);
		close(fd[1]);
		close(STDOUT_FILENO);
		free(data->pipex->tab_pid);
		free(data->pipex->tab_fd);
		ft_to_free(data);
		free_data(data);
		ft_free_for_end(data);
		exit (1);
	}
	if (execve(cmd[0], cmd, data->env_path) == -1)
		ft_error(data, "execve error\n", 1, 0);
	g_error_last = 0;
	free_cmd(cmd);
	return (0);
}

void	pipex_algo(t_data *data, char **cmd)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
		ft_error(data, "pipe error\n", 1, 1);
	data->pipex->file_out = fd[1];
	if (!data->iterator->next)
	{
		close(fd[0]);
		data->pipex->file_out = STDOUT_FILENO;
	}
	pid = fork();
	if (pid == -1)
		ft_error(data, "fork error\n", 1, 1);
	else if (pid == 0)
		ft_exec_pipe(data, fd, cmd);
	free_cmd(cmd);
	ft_restore_loop(data, pid, fd, data->pipex->count);
	data->pipex->count++;
}

int	ft_loop_pipe(t_data *data)
{
	char	**cmd;

	while (data->iterator)
	{
		cmd = command_error(data);
		if (cmd != NULL)
			pipex_algo(data, cmd);
		else if (!data->iterator->next)
		{
			if (data->pipex->prev_fd > 0)
				close(data->pipex->prev_fd);
			data->pipex->file_out = STDOUT_FILENO;
		}
		data->iterator = data->iterator->next;
		list_progress(data);
	}
	return (0);
}

int	ft_pipe(t_data *data)
{
	data->pipex->tab_pid = ft_calloc(ft_lstlen(data->iterator), sizeof(int));
	if (data->pipex->tab_pid == NULL)
		ft_error(data, "malloc error\n", 1, 1);
	data->pipex->tab_fd = ft_calloc(ft_lstlen(data->iterator), sizeof(int));
	if (data->pipex->tab_fd == NULL)
		ft_error(data, "malloc error\n", 1, 1);
	data->pipex->prev_fd = 0;
	data->pipex->count = 0;
	data->pipex->last = 0;
	check_signal(data);
	list_progress(data);
	g_error_last = 0;
	ft_loop_pipe(data);
	ft_end(data);
	return (0);
}
