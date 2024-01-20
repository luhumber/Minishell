/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chsiffre <chsiffre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 14:46:30 by charles           #+#    #+#             */
/*   Updated: 2022/11/10 19:27:20 by chsiffre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*dest;
	unsigned int	new_len;
	size_t			i;

	if (!s)
		return (NULL);
	i = 0;
	new_len = ft_strlen(s);
	if (new_len < start)
		return (ft_strdup(""));
	if (new_len < len)
		len = new_len;
	dest = malloc((len + 1) * sizeof(char));
	if (!dest)
		return (NULL);
	while (s[i] && len > i)
	{
		dest[i] = s[start + i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
