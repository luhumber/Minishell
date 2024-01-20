/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luhumber <luhumber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 10:41:56 by luhumber          #+#    #+#             */
/*   Updated: 2023/08/03 11:19:23 by luhumber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_end(t_data *data)
{
	int	ret;

	while (data->pipex->count--)
	{
		ret = 0;
		if (waitpid(data->pipex->tab_pid[data->pipex->count], &ret, 0) == -1)
			ft_error(data, "waitpid error\n", 1, 1);
		if (WIFEXITED(ret))
			g_error_last = WEXITSTATUS(ret);
		if (data->pipex->count > 0)
			close(data->pipex->tab_fd[data->pipex->count]);
	}
	if (data->pipex->last != 0)
		g_error_last = data->pipex->last;
	free(data->pipex->tab_pid);
	free(data->pipex->tab_fd);
	return (0);
}

void	ft_restore_loop(t_data *data, pid_t pid, int *fd, int count)
{
	if (data->in_redir != 0)
	{
		if (data->in_redir > 0)
		{
			close(data->in_redir);
			if (dup2(data->savestdin, STDIN_FILENO) == -1)
				ft_error(data, "dup error\n", 1, 1);
		}
		data->in_redir = 0;
	}
	if (data->out_redir != 0)
	{
		if (data->out_redir > 0)
		{
			close(data->out_redir);
			if (dup2(data->savestdout, STDOUT_FILENO) == -1)
				ft_error(data, "dup error\n", 1, 1);
		}
		data->out_redir = 0;
	}
	data->pipex->tab_pid[count] = pid;
	data->pipex->tab_fd[count] = data->pipex->prev_fd;
	data->pipex->prev_fd = fd[0];
	close(fd[1]);
}
