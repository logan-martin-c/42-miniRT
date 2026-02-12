/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 13:11:18 by lomartin          #+#    #+#             */
/*   Updated: 2025/11/23 11:59:25 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** @brief Compare up to n characters of two strings
** @param s1 First string
** @param s2 Second string
** @param n Maximum characters to compare
** @return Integer less than, equal to, or greater than zero,
** ASCII difference between the first non-matching encountered character.
*/
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	while (n > 0 && (*s1 || *s2))
	{
		if ((unsigned char)*s1 != (unsigned char)*s2)
			return (((unsigned char)*s1 - (unsigned char)*s2));
		s1++;
		s2++;
		n--;
	}
	return (0);
}
