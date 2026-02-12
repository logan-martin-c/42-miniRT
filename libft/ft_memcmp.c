/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 14:47:33 by lomartin          #+#    #+#             */
/*   Updated: 2025/11/23 11:48:49 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** @brief Compare n bytes of two memory areas
** @param s1 First memory area
** @param s2 Second memory area
** @param n Number of bytes to compare
** @return Integer less than, equal to,
	or greater than zero if s1 is found to be less than, to match,
	or be greater than s2
*/
int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*s1cpy;
	unsigned char	*s2cpy;

	s1cpy = (unsigned char *)s1;
	s2cpy = (unsigned char *)s2;
	while (n > 0)
	{
		if (*s1cpy != *s2cpy)
			return (*s1cpy - *s2cpy);
		s1cpy++;
		s2cpy++;
		n--;
	}
	return (0);
}
