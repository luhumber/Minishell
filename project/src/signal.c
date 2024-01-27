/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luhumber <luhumber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 14:51:04 by luhumber          #+#    #+#             */
/*   Updated: 2023/07/31 15:35:50 by luhumber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_ctrl(int signal)
{
	if (signal == SIGINT)
	{
		rl_on_new_line();
		printf("\n");
		rl_replace_line("", 0);
		rl_redisplay();
		g_error_last = 130;
	}
	else if (signal == SIGTERM)
		exit (0);
}

void	ft_ctrl_fork(int signal)
{
	if (signal == SIGINT)
	{
		rl_on_new_line();
		printf("\n");
		rl_replace_line("", 0);
	}
	else if (signal == SIGTERM)
		exit (0);
	else
	{
		write(2, "Quit (core dumped)\n", 20);
		rl_on_new_line();
		rl_replace_line("", 0);
		return ;
	}
}

void	ft_here_sig(int signal)
{
	if (signal == SIGINT)
	{
		rl_on_new_line();
		printf("\n");
		rl_replace_line("", 0);
		exit (1);
	}
}

void	ft_mini_sig(int signal)
{
	if (signal == SIGINT)
	{
		rl_replace_line("", 0);
		rl_redisplay();
		g_error_last = 130;
	}
	else if (signal == SIGTERM)
		exit (0);
}

void	check_signal(t_data *data)
{
	if (!ft_compare_str(data->iterator->content[0], "./minishell"))
	{
		signal(SIGINT, ft_ctrl_fork);
		signal(SIGTERM, ft_ctrl_fork);
		signal(SIGQUIT, ft_ctrl_fork);
	}
	else 
	{
		signal(SIGINT, ft_mini_sig);
		signal(SIGTERM, ft_mini_sig);
		signal(SIGQUIT, ft_mini_sig);
	}
}
