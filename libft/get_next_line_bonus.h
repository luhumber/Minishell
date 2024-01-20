/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chsiffre <chsiffre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 13:36:44 by chsiffre          #+#    #+#             */
/*   Updated: 2023/03/15 17:02:30 by chsiffre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <limits.h>
# include "libft.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

char	*get_next_line(int fd);
size_t	ft_strlen_2(const char *s);
char	*ft_strjoin_2(char *s1, char *s2);
char	*ft_strchr_2(char *s, int c);
char	*ft_read(char *buff_s, int fd);
void	ft_setup_next_line(char *line, char *buffer_s, int start);
char	*ft_set_line(char *line, char *buff_s);

#endif