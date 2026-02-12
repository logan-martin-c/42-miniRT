/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_min_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 19:44:23 by lomartin          #+#    #+#             */
/*   Updated: 2025/12/03 21:53:22 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** @brief Returns the lowest value between count longs
** @param count Count of long to expect
** @return Lowest between all given values
*/
long	ft_min_var(unsigned int count, ...)
{
	va_list	ap_min;
	long	min;
	long	arg;

	if (!count)
		return (0);
	va_start(ap_min, count);
	min = va_arg(ap_min, long);
	while (--count)
	{
		arg = va_arg(ap_min, long);
		if (arg < min)
			min = arg;
	}
	va_end(ap_min);
	return (min);
}
