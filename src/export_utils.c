/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luhumber <luhumber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 11:00:23 by luhumber          #+#    #+#             */
/*   Updated: 2023/08/03 11:40:54 by luhumber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_check_isok(char *str)
{
	int	i;

	i = 0;
	if (ft_isalpha(str[0]) == 0 && str[i] != '_')
		return (1);
	while (str[i] && str[i] != '=')
	{
		if (str[i] == '+' && str[i + 1] == '=')
			return (2);
		if (ft_isalnum(str[i]) == 0 && str[i] != '_')
			return (1);
		i++;
	}
	if (str[i] == '+')
		return (2);
	return (0);
}

int	ft_loop_check(t_env *tmp, char *name, char *n_equal)
{
	while (tmp)
	{
		if (ft_compare_str(tmp->name, name))
			return (1);
		if (ft_compare_str(tmp->name, n_equal))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

char	*ft_plusequal_cpy(char *str, char *name)
{
	int	i;

	i = 0;
	while (str[i] && ((str[i] != '=') && (str[i] != '+')))
	{
		name[i] = str[i];
		i++;
	}
	name[i] = '\0';
	return (name);
}

int	ft_check_exist(t_data *data, t_env *env, char *str)
{
	t_env	*tmp;
	int		i;
	int		ret;
	char	*name;
	char	*n_equal;

	tmp = env;
	i = 0;
	ret = ft_check_isok(str);
	if (ret == 1)
		return (-1);
	while (str[i] && (str[i + 1] != '=' && str[i + 1] != '+'))
		i++;
	name = malloc(sizeof(char *) * i + 1);
	if (!name)
		ft_error(data, "malloc error\n", 1, 1);
	name = ft_plusequal_cpy(str, name);
	n_equal = ft_strjoin(name, "=");
	if (ft_loop_check(tmp, name, n_equal) == 1)
	{
		if (ret == 2)
			return (free(name), free(n_equal), 2);
		return (free(name), free(n_equal), 1);
	}
	return (free(name), free(n_equal), 0);
}

char	*ft_switch_value(char *val, char *str, int i)
{
	int	k;

	val = malloc(sizeof(char) * (ft_strlen(str) - i));
	if (!val)
		return (NULL);
	i++;
	k = 0;
	while (str[i])
	{
		val[k] = str[i];
		k++;
		i++;
	}
	val[k] = '\0';
	return (val);
}
