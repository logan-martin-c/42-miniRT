/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 21:29:44 by lomartin          #+#    #+#             */
/*   Updated: 2025/11/23 12:01:16 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** @brief Scan memory for first occurrence of character c (unsigned char)
** @param area Memory area
** @param c Character to find
** @param n Number of bytes to examine
** @return Pointer to matching byte or NULL if not found
*/
void	*ft_memchr(const void *area, int c, size_t n)
{
	unsigned char	*str;

	str = (void *)area;
	while (n--)
	{
		if (*str == (unsigned char)c)
			return (str);
		str++;
	}
	return (0);
}
