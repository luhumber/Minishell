/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chsiffre <chsiffre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 12:27:48 by chsiffre          #+#    #+#             */
/*   Updated: 2023/02/09 12:57:28 by chsiffre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_read(char *buff_s, int fd)
{
	char	*buff_t;
	int		nb_char;

	nb_char = 1;
	buff_t = NULL;
	if (buff_s)
		buff_t = ft_strjoin_2(buff_t, buff_s);
	while (!ft_strchr_2(buff_s, '\n') && nb_char > 0)
	{
		nb_char = read(fd, buff_s, BUFFER_SIZE);
		if (nb_char == -1)
			return (NULL);
		buff_s[nb_char] = '\0';
		buff_t = ft_strjoin_2(buff_t, buff_s);
	}
	return (buff_t);
}

void	ft_setup_next_line(char *line, char *buffer_s, int start)
{
	int		i;

	i = 0;
	while (line[start + i])
	{
		buffer_s[i] = line[start + i];
		i++;
	}
	buffer_s[i] = '\0';
}

char	*ft_set_line(char *line, char *buff_s)
{
	int		i;
	char	*result_line;

	i = 0;
	if (line[0] == '\0')
		return (free(line), NULL);
	while (line[i] && line[i] != '\n')
		i++;
	result_line = malloc(sizeof(char) * (i + 2));
	if (!result_line)
		return (free(line), NULL);
	i = -1;
	while (line[++i] && line[i] != '\n')
		result_line[i] = line[i];
	if (line[i] == '\n')
	{
		result_line[i] = line[i];
		i++;
	}
	result_line[i] = '\0';
	ft_setup_next_line(line, buff_s, i);
	free(line);
	return (result_line);
}

char	*get_next_line(int fd)
{
	static char	buff_s[10200][BUFFER_SIZE + 1];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, NULL, 0) == -1)
		return (NULL);
	line = ft_read(buff_s[fd], fd);
	if (!line)
		return (NULL);
	return (ft_set_line(line, buff_s[fd]));
}
