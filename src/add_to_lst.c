/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_to_lst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luhumber <luhumber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 10:11:52 by charles           #+#    #+#             */
/*   Updated: 2023/08/03 11:57:44 by luhumber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_lst	*ft_lstnew_t(char **strs, int type, int i)
{
	t_lst	*ptr;
	int		y;

	y = 0;
	ptr = malloc(sizeof(t_lst) + 1);
	if (!ptr)
		return (NULL);
	ptr->content = malloc(sizeof(char *) * (ft_strs_len(strs) + 1));
	if (!ptr->content)
		return (NULL);
	ptr->type = type;
	ft_check_fil_content(strs, &y, &i, ptr->content);
	ptr->content[y] = 0;
	ptr->next = NULL;
	return (ptr);
}

char	**ft_check_fil_content(char **strs, int *y, int *i, char **content)
{
	if (strs[*i] && ft_is_redir(strs[*i]))
	{
		content[(*y)++] = ft_strdup(strs[(*i)++]);
		if (!strs[*i] || strs[*i][0] == '|')
			return (NULL);
		content[(*y)++] = ft_strdup(strs[(*i)++]);
	}
	else if (strs[*i] && !ft_is_redir(strs[*i]) && strs[*i][0] != '|')
	{
		while (strs[*i] && strs[*i][0] != '|')
			content[(*y)++] = ft_strdup(strs[(*i)++]);
	}
	else
		content[(*y)++] = ft_strdup(strs[(*i)++]);
	return (content);
}

t_lst	*ft_add_lst(t_lst *lst, t_data *data, int type)
{
	t_lst	*new;

	new = ft_lstnew_t(data->res_parse, type, data->y);
	if (!new)
		return (NULL);
	ft_add_back(&lst, new);
	return (lst);
}

t_lst	*ft_last(t_lst *lst)
{
	while (lst)
	{
		if (!lst->next)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

void	ft_add_back(t_lst **lst, t_lst *new)
{
	t_lst	*last;

	if (lst)
	{
		if (*lst)
		{
			last = ft_last(*lst);
			last->next = new;
		}
		else
			*lst = new;
	}
}
