/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 14:12:59 by lomartin          #+#    #+#             */
/*   Updated: 2025/11/23 11:47:09 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** @brief Copy up to n - 1 chars from src to dest and NUL-terminate
** @param dest Destination buffer
** @param src Source string
** @param n Size of destination buffer
** @return Length of src
*/
size_t	ft_strlcpy(char *dest, const char *src, size_t n)
{
	int		i;
	size_t	len;

	len = ft_strlen(src);
	if (!n || !dest)
		return (len);
	i = -1;
	while (src[++i] && n - 1)
	{
		dest[i] = src[i];
		n--;
	}
	dest[i] = 0;
	return (len);
}
