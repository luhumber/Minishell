/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luhumber <luhumber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 12:27:03 by luhumber          #+#    #+#             */
/*   Updated: 2023/08/03 13:47:17 by luhumber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_write_entry(t_data *data, char *res, char *line)
{
	int	i;

	res = malloc(sizeof(char) * ft_strlen(line) + 2);
	if (!res)
		ft_error(data, "malloc error\n", 1, 1);
	i = -1;
	while (line[++i])
		res[i] = line[i];
	res[i++] = '\n';
	res[i] = '\0';
	return (res);
}

void	ft_heredoc_loop(t_data *data, int *fd)
{
	char	*line;
	char	*res;

	res = NULL;
	while (1)
	{
		line = readline("heredoc> ");
		if (line == NULL)
		{
			ft_write_error
				("warning: here-document delimited by end-of-file");
			break ;
		}
		if (ft_compare_str(line, data->limiter))
			break ;
		res = ft_write_entry(data, res, line);
		write(fd[1], res, ft_strlen(res));
		free(line);
		free(res);
	}
	free(line);
}

void	ft_pid_heredoc(t_data *data, pid_t pid, int *fd)
{
	if (pid == -1)
		ft_error(data, "fork error\n", 1, 1);
	else if (pid == 0)
	{
		close(fd[0]);
		data->limiter = data->iterator->content[1];
		signal(SIGINT, ft_here_sig);
		ft_heredoc_loop(data, fd);
		close(fd[1]);
		ft_to_free(data);
		free_data(data);
		ft_free_for_end(data);
		close(STDIN_FILENO);
		exit(0);
	}
}

int	ft_here_doc(t_data *data)
{
	int		fd[2];
	int		exit_status;
	pid_t	pid;

	if (pipe(fd) == -1)
		ft_error(data, "pipe error\n", 1, 1);
	signal(SIGINT, SIG_IGN);
	pid = fork();
	ft_pid_heredoc(data, pid, fd);
	waitpid(pid, &exit_status, 2);
	if (WEXITSTATUS(exit_status) == 1)
		return (1);
	close(fd[1]);
	data->in_redir = fd[0];
	g_error_last = 0;
	return (0);
}
