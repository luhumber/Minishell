/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chsiffre <chsiffre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 16:18:45 by chsiffre          #+#    #+#             */
/*   Updated: 2023/08/14 14:40:33 by chsiffre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_lst	*ft_parse(t_data *d)
{
	t_lst	*lst;

	lst = NULL;
	d->res_split = ft_split_charset(d->line, " \t\n\r\v\f");
	if (!d->res_split)
		return (NULL);
	d->res_parse = malloc((ft_strs_len(d->res_split) + 1) * sizeof(char *));
	if (!d->res_parse)
		return (NULL);
	d->res_parse = check_res_split(d);
	d->res_parse = check_quotes(d->res_parse, d);
	lst = ft_convert_in_lst(lst, d);
	if (!lst)
		return (NULL);
	return (lst);
}

char	**check_res_split(t_data *d)
{
	int	i;

	i = 0;
	while (d->res_split[i])
	{
		d->res_parse = ft_check_redir(d->res_parse, d, d->res_split, i);
		if (!d->res_parse)
			return (NULL);
		d->res_parse = ft_check_cmd(d->res_parse, d, d->res_split, i);
		while (d->res_split[i] && d->res_split[i][0] != '|')
			i++;
		if (d->res_split[i])
			d->res_parse[d->i++] = ft_strdup(d->res_split[i++]);
	}
	d->res_parse[i] = NULL;
	return (d->res_parse);
}

t_lst	*ft_convert_in_lst(t_lst *lst, t_data *data)
{
	while (data->res_parse[data->y])
	{
		if (ft_is_redir(data->res_parse[data->y]))
		{
			lst = ft_add_lst(lst, data, REDIR);
			if (!lst)
				return (NULL);
			data->y = data->y + 2;
		}
		else if (data->res_parse[data->y]
			&& !ft_is_redir(data->res_parse[data->y])
			&& data->res_parse[data->y][0] != '|')
			lst = add_command(lst, data);
		else
			data->y++;
	}
	return (lst);
}

t_lst	*add_command(t_lst *lst, t_data *data)
{
	lst = ft_add_lst(lst, data, CMD);
	while (data->res_parse[data->y] && data->res_parse[data->y][0] != '|')
		data->y++;
	if (data->res_parse[data->y])
	{
		lst = ft_add_lst(lst, data, PIPE);
		if (!lst)
			return (NULL);
		data->y++;
	}
	return (lst);
}

int	ft_len_parse(char **strs, int i)
{
	int	size;

	size = 0;
	while (strs[i] && strs[i][0] != '|')
	{
		size++;
		i++;
	}
	return (size);
}
