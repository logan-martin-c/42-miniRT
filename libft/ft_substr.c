/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 09:30:22 by lomartin          #+#    #+#             */
/*   Updated: 2025/11/23 11:47:16 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** @brief Return a newly allocated substring from string s starting at start
** @param s Source string
** @param start Start index
** @param len Maximum length of substring
** @return Newly allocated substring or NULL on allocation failure
*/
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substring;
	size_t	size;

	if (!s)
		return (NULL);
	size = ft_strlen(s);
	if (start > size)
		len = 0;
	s += start;
	size -= start;
	if (size < len)
		len = size;
	size = len;
	substring = malloc((len + 1) * sizeof(char));
	if (!substring)
		return (NULL);
	while (*s && len--)
		*(substring++) = *(s++);
	*substring = 0;
	return (substring - size);
}
