/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 16:27:24 by lomartin          #+#    #+#             */
/*   Updated: 2026/02/10 22:29:18 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** @brief Compute length of null-terminated string
** @param str Null-terminated string
** @return Number of characters before the terminating null byte
*/
size_t	ft_strlen(char const *str)
{
	size_t	len;

	if (!str)
		return (0);
	len = 0;
	while (str[len])
		len++;
	return (len);
}
