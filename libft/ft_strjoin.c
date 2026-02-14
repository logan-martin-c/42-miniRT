/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 10:30:37 by lomartin          #+#    #+#             */
/*   Updated: 2026/02/14 18:30:13 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** @brief Allocate and return a new string which is the result of the\
** concatenation of s1 and s2
** @param s1 First string
** @param s2 Second string
** @return Newly allocated concatenated string or NULL on failure
*/
char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len;
	char	*dest;

	len = ft_strlen(s1) + ft_strlen(s2);
	dest = malloc((len + 1) * sizeof(char));
	if (!dest)
		return (0);
	while (s1 && *s1)
		*(dest++) = *(s1++);
	while (s2 && *s2)
		*(dest++) = *(s2++);
	*dest = 0;
	return (dest - len);
}

char	*ft_strjoin_mult(unsigned int count, ...)
{
	va_list			ap;
	char			*dest;
	char			*temp;
	char			*temp2;
	unsigned int	i;

	i = -1;
	dest = NULL;
	va_start(ap, count);
	while (++i < count)
	{
		temp = va_arg(ap, char *);
		if (!temp || !*temp)
			continue ;
		temp2 = dest;
		dest = ft_strjoin(dest, temp);
		free(temp2);
	}
	va_end(ap);
	return (dest);
}
