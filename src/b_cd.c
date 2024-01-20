/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_cd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luhumber <luhumber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 14:07:27 by luhumber          #+#    #+#             */
/*   Updated: 2023/08/14 14:10:12 by luhumber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_cd_error(char *str)
{
	g_error_last = 1;
	ft_printf_fd("%s\n", 2, str);
	return (-1);
}

int	ft_pwd(t_data *data)
{
	char	buff[REP_MAX];
	char	*str;

	if (ft_check_exist(data, data->env, "PWD=") == 0)
		return (1);
	if (getcwd(buff, REP_MAX) == NULL)
		ft_error(data, "PWD error\n", 1, 1);
	str = ft_strjoin("PWD=", buff);
	ft_add_var(data, str, 1);
	free(str);
	return (0);
}

int	ft_old_pwd(t_data *data)
{
	char	buff[REP_MAX];
	char	*str;

	if (ft_check_exist(data, data->env, "OLDPWD=") == 0)
		return (1);
	if (getcwd(buff, REP_MAX) == NULL)
		return (1);
	str = ft_strjoin("OLDPWD=", buff);
	ft_add_var(data, str, 1);
	free(str);
	return (0);
}

int	ft_algo_cd(t_data *data, char *rep)
{
	ft_old_pwd(data);
	if (chdir(rep) == -1)
		return (ft_print_error(rep, 1), 1);
	ft_pwd(data);
	g_error_last = 0;
	return (0);
}

void	ft_cd(t_data *data)
{
	t_env	*tmp;
	int		args;

	args = 0;
	tmp = data->env;
	while (data->iterator->content[args])
		args++;
	if (args == 1)
	{
		while (tmp)
		{
			if (ft_compare_str(tmp->name, "HOME="))
			{
				ft_algo_cd(data, tmp->value);
				return ;
			}
			tmp = tmp->next;
		}
		ft_cd_error("bash: cd: HOME not set");
	}
	else if (args == 2)
		ft_algo_cd(data, data->iterator->content[1]);
	else
		ft_cd_error("bash: cd: too many arguments");
}
