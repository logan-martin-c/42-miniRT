/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 13:29:27 by lomartin          #+#    #+#             */
/*   Updated: 2025/12/01 16:27:59 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** @brief Locate first occurrence of needle in haystack,
**	searching at most n bytes
** @param haystack Haystack string
** @param needle Needle string
** @param n Maximum bytes to search
** @return Pointer to first occurrence in haystack or NULL if not found
*/
char	*ft_strnstr(const char *haystack, const char *needle, size_t n)
{
	int	i;
	int	j;

	i = 0;
	j = -1;
	if (!n && !haystack)
		return (NULL);
	if (!(*needle))
		return ((char *)haystack);
	while (haystack[++j] && n)
	{
		i = 0;
		while (needle[i] && n - i && needle[i] == haystack[j + i])
			i++;
		if (!needle[i])
			return ((char *)haystack + j);
		n--;
	}
	return (NULL);
}
