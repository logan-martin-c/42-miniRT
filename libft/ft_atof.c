/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 15:26:34 by lomartin          #+#    #+#             */
/*   Updated: 2026/02/14 18:33:14 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** @brief Converts string to float
** @param str Null-terminated string to convert, with ',' or '.' as fractional
** delimiter
** @return Converted float value
*/
float	ft_atof(const char *str)
{
	float	nbr;
	float	dec;
	int		sin;

	nbr = 0;
	sin = 1;
	while (ft_isspace(*str))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sin = -sin;
		str++;
	}
	while (*str >= '0' && *str <= '9')
		nbr = nbr * 10 + (*(str++) - '0');
	if (*str != ',' && *(str++) != '.')
		return (nbr * sin);
	dec = 0.1;
	while (*str >= '0' && *str <= '9')
	{
		nbr += (*(str++) - '0') * dec;
		dec /= 10;
	}
	return (nbr * sin);
}
