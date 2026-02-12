/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_max.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 19:41:34 by lomartin          #+#    #+#             */
/*   Updated: 2025/12/03 21:54:12 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** @brief Returns the highest value between count longs
** @param count Count of long to expect
** @return Highest between all given values
*/
long	ft_max(long a, long b)
{
	if (a > b)
		return (a);
	return (b);
}
