/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_env.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lucas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 11:15:29 by luhumber          #+#    #+#             */
/*   Updated: 2023/08/07 11:39:05 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_env	*ft_envlast(t_env *lst)
{
	while (lst && lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_envadd_back(t_env **env, t_env *new)
{
	t_env	*last;

	if (env)
	{
		if (*env)
		{
			last = ft_envlast(*env);
			last->next = new;
		}
		else
			*env = new;
	}
}

char	*ft_alloc_val(t_env *new, char *str, int k, int temp)
{
	while (str[k])
		k++;
	new->value = malloc(sizeof(char *) * ((k - temp) + 1));
	if (!new->value)
		return (NULL);
	k = temp;
	temp = 0;
	while (str[k])
		new->value[temp++] = str[k++];
	new->value[temp] = '\0';
	return (new->value);
}

t_env	*give_value(t_env *new, char *str, int k)
{
	int		i;
	int		temp;

	i = 0;
	temp = 0;
	while (temp <= k)
	{
		if (str[temp] != '+')
		{
			new->name[i] = str[temp];
			i++;
		}
		temp++;
	}
	new->name[i] = '\0';
	if (new->equal == 1)
		ft_alloc_val(new, str, k, temp);
	else
		new->value = NULL;
	new->next = NULL;
	return (new);
}

t_env	*ft_new_env(char *str)
{
	t_env	*new;
	int		k;

	k = 0;
	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->equal = ft_has_equal(str);
	while (str[k] && str[k] != '=')
		k++;
	new->name = malloc(sizeof(char *) * (k + 1));
	if (!new->name)
		return (NULL);
	new = give_value(new, str, k);
	return (new);
}
