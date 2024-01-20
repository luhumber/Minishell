/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_echo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chsiffre <chsiffre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 13:00:03 by lucas             #+#    #+#             */
/*   Updated: 2023/08/14 15:06:56 by chsiffre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	empty_echo(t_data *data)
{
	if (!data->iterator->content[1])
	{
		printf("\n");
		return (1);
	}
	else if (ft_compare_str(data->iterator->content[1], "-n")
		&& !data->iterator->content[2])
		return (1);
	return (0);
}

int	ft_is_option_n(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (1);
	while (str[i])
	{
		if (str[0] && str[0] == '-')
			i++;
		if (str[i] && str[i] != 'n')
			return (0);
		if (str[i])
			i++;
	}
	return (1);
}

void	ft_echo(t_data *data)
{
	char	*ret;
	int		i;
	int		option;

	option = 0;
	i = 1;
	ret = "";
	if (empty_echo(data) == 1)
		return ;
	while (data->iterator->content[i++][0] != '\0' &&
		ft_is_option_n(data->iterator->content[i]))
		option = 1;
	while (data->iterator->content[i])
	{
		ret = new_join(ret, data->iterator->content[i], data->res_split[i]);
		i++;
	}
	if (option == 1)
		printf("%s", ret);
	else
		printf("%s\n", ret);
	free(ret);
	g_error_last = 0;
}
