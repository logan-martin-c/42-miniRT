/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 09:53:42 by lomartin          #+#    #+#             */
/*   Updated: 2025/11/23 11:47:06 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** @brief Concatenate src to dst of size dstsize, guaranteeing NUL-termination
** @param dst Destination buffer
** @param src Source string
** @param dstsize Full size of destination buffer
** @return Total length of string it tried to create (initial dst + src)
*/
size_t	ft_strlcat(char *dest, char *src, unsigned int size)
{
	size_t	destlen;
	size_t	srclen;
	size_t	i;

	srclen = ft_strlen(src);
	if (!size)
		return (srclen);
	destlen = ft_strlen(dest);
	if (destlen >= size)
		return (srclen + size);
	i = -1;
	while (src[++i] && destlen + i < size - 1)
		dest[destlen + i] = src[i];
	dest[destlen + i] = '\0';
	return (srclen + destlen);
}
