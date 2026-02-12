/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 17:34:56 by lomartin          #+#    #+#             */
/*   Updated: 2025/11/23 12:58:18 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** @brief Trim characters in set from start and end of string s
** @param s1 Source string
** @param set Characters to trim
** @return Newly allocated trimmed string or NULL on failure
*/
char	*ft_strtrim(const char *s1, const char *set)
{
	size_t	len;
	char	*dest;

	if (!s1)
		return (NULL);
	if (!set)
		return ((char *)s1);
	while (ft_isinset(*s1, set))
		s1++;
	len = ft_strlen(s1);
	if (len)
	{
		while (ft_isinset(s1[len - 1], set))
			len--;
	}
	dest = malloc((len + 1) * sizeof(char));
	if (!dest)
		return (NULL);
	dest[len] = '\0';
	while (len--)
		dest[len] = s1[len];
	return (dest);
}
