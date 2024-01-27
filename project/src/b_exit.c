/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_exit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luhumber <luhumber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 22:44:17 by lucas             #+#    #+#             */
/*   Updated: 2023/08/03 11:02:46 by luhumber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_exit_error(char *str)
{
	char	*join;
	char	*join2;

	join = ft_strjoin("bash: exit: ", str);
	join2 = ft_strjoin(join, " numeric argument required\n");
	write(2, join2, ft_strlen(join2));
	free(join);
	free(join2);
	return (0);
}

static int	ft_is_valid_num(char *command)
{
	int						i;
	unsigned long long int	res;

	i = -1;
	res = 0;
	if (ft_compare_str(command, "-9223372036854775808"))
		return (1);
	if (command[0] == '+' || command[0] == '-')
		i++;
	while (command[++i])
	{
		if (!ft_isdigit(command[i]))
			return (0);
		res = (res * 10) + command[i] - '0';
		if (res > LLMAX)
			return (0);
	}
	return (1);
}

void	ft_exit_pack(t_data *data, int code_error, int ex, int error)
{
	g_error_last = code_error;
	printf("exit\n");
	if (error == 1)
		ft_exit_error(data->iterator->content[1]);
	ft_to_free(data);
	if (ex == 1)
		free_data(data);
	ft_free_for_end(data);
	exit(g_error_last);
}

int	ft_exit(t_data *data)
{
	if (data->iterator->content[1])
	{
		if (ft_is_valid_num(data->iterator->content[1])
			&& data->iterator->content[2])
		{
			g_error_last = 1;
			printf("exit\n");
			write(2, "bash: exit: too many arguments\n", 32);
			return (1);
		}
		if (ft_is_valid_num(data->iterator->content[1]))
			ft_exit_pack(data, ft_atoi(data->iterator->content[1]) % 256, 1, 0);
		else
		{
			g_error_last = 2;
			ft_exit_pack(data, g_error_last, 1, 1);
		}
	}
	else
		ft_exit_pack(data, g_error_last, 1, 0);
	return (1);
}
