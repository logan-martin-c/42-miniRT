/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nblen_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 19:01:04 by lomartin          #+#    #+#             */
/*   Updated: 2025/11/23 19:23:10 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** @brief Counts the numbers in nb
** @param nb Long int to process
** @return Length of nb
*/
size_t	ft_nblen(long nb)
{
	size_t	len;

	if (nb == 0)
		return (1);
	len = 0;
	if (nb < 0)
	{
		len++;
		nb = -nb;
	}
	while (nb)
	{
		len++;
		nb /= 10;
	}
	return (len);
}
