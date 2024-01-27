/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luhumber <luhumber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 14:25:53 by luhumber          #+#    #+#             */
/*   Updated: 2023/08/01 10:43:08 by luhumber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_special_char(char *cmd)
{
	int		i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

int	ft_export_error(char *str)
{
	ft_printf_fd("bash: export: '%s\n' not a valid indentifier\n", 2, str);
	g_error_last = 2;
	return (1);
}

void	ft_rl_error(t_data *data)
{
	ft_to_free(data);
	write(2, "exit\n", 6);
	ft_free_for_end(data);
	exit(0);
}

void	ft_syntax_error(char *str)
{
	g_error_last = 2;
	ft_printf_fd("bash: syntax error near unexpected token %s\n", 2, str);
	return ;
}

void	env_error(t_data *data)
{
	ft_printf_fd("env: '%s': No such file or directory\n",
		2, data->iterator->content[1]);
	g_error_last = 127;
}
