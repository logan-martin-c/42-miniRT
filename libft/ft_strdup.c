/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 09:17:32 by lomartin          #+#    #+#             */
/*   Updated: 2025/11/23 13:18:42 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	@brief Duplicate a string by allocating memory and copying src
**	@param src Source null-terminated string
**	@return Pointer to newly allocated duplicated string or NULL on allocation
**	failure
*/
char	*ft_strdup(const char *src)
{
	size_t	len;
	char	*dest;

	len = ft_strlen(src);
	dest = malloc(len * sizeof(char) + 1);
	if (!dest)
		return (NULL);
	while (*src)
		*(dest++) = *(src++);
	*dest = 0;
	return (dest - len);
}
