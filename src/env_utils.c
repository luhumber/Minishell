/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luhumber <luhumber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 15:23:01 by luhumber          #+#    #+#             */
/*   Updated: 2023/07/31 17:03:16 by luhumber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_exist_var(t_data *data, char *str, t_env *new)
{
	char	*name;
	int		i;

	i = 0;
	name = NULL;
	name = ft_find_name(name, str);
	if (name == NULL)
		ft_error(data, "malloc error\n", 1, 1);
	while (ft_strncmp(new->name, name, ft_strlen(name) - 1))
		new = new->next;
	free(new->name);
	new->name = name;
	while (str[i] && str[i] != '=')
		i++;
	if (str[i] == '=')
	{
		free(new->value);
		new->value = ft_add_value(str, i);
		if (!new->value)
			ft_error(data, "malloc error\n", 1, 1);
		if (ft_has_equal(new->name))
			new->equal = 1;
	}
}

void	ft_join_var(t_data *data, char *str, t_env *new)
{
	char	*name;
	int		i;

	i = 0;
	name = NULL;
	name = ft_find_name(name, str);
	if (name == NULL)
		ft_error(data, "malloc error\n", 1, 1);
	while (ft_strncmp(new->name, name, ft_strlen(name) - 1))
		new = new->next;
	free(new->name);
	new->name = name;
	while (str[i] && str[i] != '=')
		i++;
	if (str[i] == '=')
	{
		new->value = new_val(new, str, i);
		if (!new->value)
			ft_error(data, "malloc error\n", 1, 1);
		if (ft_has_equal(new->name))
			new->equal = 1;
	}
}

void	ft_add_var(t_data *data, char *str, int exist)
{
	t_env	*new;

	new = data->env;
	if (exist == 0)
	{
		new = ft_new_env(str);
		ft_envadd_back(&data->env, new);
	}
	else if (exist == 1)
		ft_exist_var(data, str, new);
	else if (exist == 2)
		ft_join_var(data, str, new);
	g_error_last = 0;
}
