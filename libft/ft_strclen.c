/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strclen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 19:11:01 by lomartin          #+#    #+#             */
/*   Updated: 2026/02/11 19:15:49 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** @brief Returns the lengths of a string up to c,
**	or to the end if c is not found
** @param str A string
** @param c ASCII character
** @return The length of the string up to c
*/
int	ft_strclen(const char *str, char c)
{
	int	len;

	len = 0;
	while (str[len] && str[len] != c)
		len++;
	return (len);
}

int	ft_strcharsetlen(const char *str, char *charset)
{
	int	len;

	len = 0;
	while (str[len] && !ft_isinset(str[len], charset))
		len++;
	return (len);
}
