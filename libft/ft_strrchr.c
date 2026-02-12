/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 14:03:45 by lomartin          #+#    #+#             */
/*   Updated: 2025/11/23 13:19:35 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** @brief Locate last occurrence of character c in string s
** @param s Null-terminated string to search
** @param c Character to find
** @return Pointer to last occurrence or NULL if not found
*/
char	*ft_strrchr(const char *str, int c)
{
	size_t	len;

	len = ft_strlen(str);
	if (c == '\0')
		return ((char *)(str + len));
	while (len)
	{
		if (str[len - 1] == (unsigned char)c)
			return ((char *)(str + len - 1));
		len--;
	}
	return (NULL);
}
