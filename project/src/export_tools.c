/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luhumber <luhumber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 17:01:48 by luhumber          #+#    #+#             */
/*   Updated: 2023/08/01 10:46:16 by luhumber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*new_val(t_env *new, char *str, int i)
{
	char	*join;
	char	*val;

	val = ft_add_value(str, i);
	join = ft_strjoin(new->value, val);
	free(val);
	free(new->value);
	return (join);
}

char	*ft_add_value(char *str, int i)
{
	char	*val;

	val = NULL;
	val = ft_switch_value(val, str, i);
	if (!val)
		return (NULL);
	return (val);
}

int	ft_has_equal(char *str)
{
	int	k;

	k = 0;
	while (str[k])
	{
		if (str[k] == '=')
			return (1);
		k++;
	}
	return (0);
}
