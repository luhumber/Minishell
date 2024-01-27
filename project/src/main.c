/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chsiffre <chsiffre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 13:20:17 by chsiffre          #+#    #+#             */
/*   Updated: 2023/08/14 15:09:01 by chsiffre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	g_error_last;

void	ft_get_env(t_data *data)
{
	int	i;

	i = 0;
	while (data->env_path[i])
	{
		if (ft_strnstr(data->env_path[i], "PATH", 5))
		{
			data->path = data->env_path[i] + 5;
			data->split_path = ft_split(data->path, ':');
			if (!data->split_path)
				exit (1);
			return ;
		}
		i++;
	}
	data->path = NULL;
	data->split_path = NULL;
}

char	**ft_no_env(char **envp)
{
	char	buff[REP_MAX];

	if (getcwd(buff, REP_MAX) == NULL)
		exit(1);
	envp = malloc(sizeof(char **) * 5);
	if (!envp)
	{
		write(2, "malloc error\n", 14);
		exit (1);
	}
	envp[0] = ft_strdup("OLDPWD");
	envp[1] = ft_strdup("SHLVL=1");
	envp[2] = ft_strdup("_=/usr/bin/env");
	envp[3] = ft_strjoin("PWD=", buff);
	envp[4] = NULL;
	return (envp);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	char	**fake_envp;

	(void)argc;
	(void)**argv;
	fake_envp = NULL;
	if (!envp || !envp[0])
	{
		data.fake = 1;
		fake_envp = ft_no_env(fake_envp);
		data.fake_path = ft_split
			("/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin",
				':');
		ft_init_data(&data, fake_envp);
	}
	else
	{
		ft_init_data(&data, envp);
		data.fake = 0;
	}
	data = ft_init_struct(data);
	ft_get_env(&data);
	ft_prompt(&data);
	return (0);
}
