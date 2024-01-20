/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luhumber <luhumber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 13:12:25 by lucas             #+#    #+#             */
/*   Updated: 2023/08/14 15:02:49 by luhumber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_exec(t_data *prompt, char **cmd)
{
	pid_t	pid;
	int		ret;

	pid = fork();
	if (pid == -1)
		ft_error(prompt, "fork error\n", 1, 1);
	else if (pid == 0)
	{
		if (execve(cmd[0], cmd, prompt->env_path) == -1)
			ft_error(prompt, "execve error\n", 1, 0);
	}
	g_error_last = 0;
	ret = 0;
	if (waitpid(pid, &ret, 0) == -1)
		ft_error(prompt, "waitpid error\n", 1, 1);
	if (WIFEXITED(ret))
		g_error_last = WEXITSTATUS(ret);
	else if (WIFSIGNALED(ret))
		g_error_last = 130;
	return (0);
}

char	*ft_try_path(t_data *data, char *cmd)
{
	int		i;
	char	*tmp;
	char	*tab;

	i = 0;
	if (cmd && ft_special_char(cmd) == 1)
		return (ft_strdup(cmd));
	tmp = ft_strjoin("/", cmd);
	tab = NULL;
	while (data->split_path && data->split_path[i])
	{
		tab = ft_strjoin(data->split_path[i], tmp);
		if (access(tab, F_OK) != -1)
			break ;
		free(tab);
		tab = NULL;
		i++;
	}
	free(tmp);
	if (!tab)
		return (ft_cmd_error(data->iterator->content[0]), NULL);
	return (tab);
}

char	**ft_cmd_options(t_data *data, char **cmd, char *content)
{
	int	i;

	if (data->fake == 0)
		cmd[0] = ft_try_path(data, content);
	else if (data->fake == 1)
		cmd[0] = fake_try_path(data, content);
	if (cmd[0] == NULL)
		return (cmd);
	i = 1;
	while (data->iterator->content[i])
	{
		cmd[i] = ft_strdup(data->iterator->content[i]);
		i++;
	}
	cmd[i] = 0;
	return (cmd);
}

int	is_executable(char *content)
{
	struct stat	info;

	if (stat(content, &info) == 0)
	{
		if (!(info.st_mode & S_IXUSR))
		{
			g_error_last = 126;
			ft_printf_fd("bash: %s: Permission denied\n", 2, content);
			return (-1);
		}
		if (S_ISDIR(info.st_mode))
		{
			g_error_last = 126;
			ft_printf_fd("%s: is a directory\n", 2, content);
			return (-1);
		}
		return (0);
	}
	g_error_last = 127;
	ft_printf_fd("No such file or directory\n", 2);
	return (-1);
}

int	ft_execute_cmd(t_data *data, char *content)
{
	char	**cmd;
	int		i;

	check_signal(data);
	i = ft_builtins(data);
	if (i == -1 || i == 1)
		return (1);
	i = 0;
	while (data->iterator->content[i])
		i++;
	cmd = malloc(sizeof(char *) * (i + 1));
	if (!cmd)
		ft_error(data, "malloc error\n", 1, 1);
	cmd = ft_cmd_options(data, cmd, content);
	if (cmd[0] != NULL && (is_executable(cmd[0]) == 0))
		ft_exec(data, cmd);
	else
		return (free_cmd(cmd), 1);
	free_cmd(cmd);
	return (0);
}
