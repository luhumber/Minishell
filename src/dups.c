/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dups.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luhumber <luhumber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 10:55:54 by luhumber          #+#    #+#             */
/*   Updated: 2023/08/02 10:39:43 by luhumber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_dup_pipe(t_data *data)
{
	if (data->in_redir > 0 && data->out_redir == 0)
	{
		if (dup2(data->pipex->file_out, STDOUT_FILENO) == -1)
			ft_error(data, "dup error\n", 1, 1);
	}
	else if (data->out_redir > 0 && data->in_redir == 0)
	{
		if (dup2(data->pipex->prev_fd, STDIN_FILENO) == -1)
			ft_error(data, "dup error\n", 1, 1);
	}
	else if (data->in_redir == 0 && data->out_redir == 0)
	{
		if (dup2(data->pipex->prev_fd, STDIN_FILENO) == -1)
			ft_error(data, "dup error\n", 1, 1);
		if (dup2(data->pipex->file_out, STDOUT_FILENO) == -1)
			ft_error(data, "dup error\n", 1, 1);
	}
}

int	ft_make_dup(t_data *data)
{
	if (data->in_redir > 0 && dup2(data->in_redir, STDIN_FILENO) == -1)
		ft_error(data, "dup error\n", 1, 1);
	if (data->out_redir > 0 && dup2(data->out_redir, STDOUT_FILENO) == -1)
		ft_error(data, "dup error\n", 1, 1);
	if (data->in_redir == -1 || data->out_redir == -1)
	{
		data->in_redir = 0;
		data->out_redir = 0;
		return (1);
	}
	return (0);
}

int	ft_close_end(t_data *data)
{
	if (data->in_redir > 0)
	{
		close(data->in_redir);
		if (dup2(data->savestdin, STDIN_FILENO) == -1)
			ft_error(data, "dup error\n", 1, 1);
	}
	if (data->out_redir > 0)
	{
		close(data->out_redir);
		if (dup2(data->savestdout, STDOUT_FILENO) == -1)
			ft_error(data, "dup error\n", 1, 1);
	}
	return (0);
}
