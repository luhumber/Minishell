/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luhumber <luhumber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 16:22:56 by luhumber          #+#    #+#             */
/*   Updated: 2023/08/01 10:44:21 by luhumber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_in_redir(t_data *data)
{
	if (ft_compare_str(data->iterator->content[0], "<"))
	{
		data->in_redir = open
			(data->iterator->content[1], O_RDONLY, 0644);
		if (data->in_redir == -1)
			return (ft_print_error(data->iterator->content[1], 1), 1);
		return (0);
	}
	else if (ft_compare_str(data->iterator->content[0], "<<"))
	{
		if (ft_here_doc(data) == 1)
		{
			g_error_last = 130;
			return (1);
		}
		return (0);
	}
	return (2);
}

int	ft_out_redir(t_data *data)
{
	if (ft_compare_str(data->iterator->content[0], ">"))
	{
		data->out_redir = open
			(data->iterator->content[1], O_RDWR | O_TRUNC | O_CREAT, 0644);
		if (data->out_redir == -1)
			return (ft_print_error(data->iterator->content[1], 1), 1);
		return (0);
	}
	else if (ft_compare_str(data->iterator->content[0], ">>"))
	{
		data->out_redir = open
			(data->iterator->content[1], O_RDWR | O_APPEND | O_CREAT, 0644);
		if (data->out_redir == -1)
			return (ft_print_error(data->iterator->content[1], 1), 1);
		return (0);
	}
	return (2);
}

int	ft_which_redir(t_data *data)
{
	int	redir;

	if (data->iterator->content[1] == NULL)
	{
		g_error_last = 2;
		return (ft_print_error
			("syntax error near unexpected token `newline'\n", 1), 1);
	}
	redir = ft_in_redir(data);
	if (redir == 1)
		return (1);
	if (redir == 2)
	{
		redir = ft_out_redir(data);
		if (redir == 1)
			return (1);
		if (redir == 2)
			return (ft_print_error
				("syntax error near unexpected token `newline'\n", 1), 1);
	}
	return (0);
}
