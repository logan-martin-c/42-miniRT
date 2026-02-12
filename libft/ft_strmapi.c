/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 16:36:09 by lomartin          #+#    #+#             */
/*   Updated: 2025/11/23 11:53:16 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** @brief Create a new string by applying function f to each character of s
** @param s Source string
** @param f Function taking index and char returning new char
** @return Newly allocated transformed string or NULL on failure
*/
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*dest;
	size_t	i;

	if (!s || !f)
		return (NULL);
	dest = malloc((ft_strlen(s) + 1) * sizeof(char));
	i = -1;
	if (!dest)
		return (NULL);
	while (s[++i])
		dest[i] = f(i, s[i]);
	dest[i] = '\0';
	return (dest);
}
