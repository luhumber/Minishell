/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luhumber <luhumber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 15:02:28 by luhumber          #+#    #+#             */
/*   Updated: 2023/08/14 15:02:52 by luhumber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*fake_try_path(t_data *data, char *cmd)
{
	int		i;
	char	*tmp;
	char	*tab;

	i = 0;
	if (cmd && ft_special_char(cmd) == 1)
		return (ft_strdup(cmd));
	tmp = ft_strjoin("/", cmd);
	tab = NULL;
	while (data->fake_path && data->fake_path[i])
	{
		tab = ft_strjoin(data->fake_path[i], tmp);
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
