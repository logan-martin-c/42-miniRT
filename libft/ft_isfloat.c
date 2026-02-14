/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isfloat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 19:21:10 by lomartin          #+#    #+#             */
/*   Updated: 2026/02/14 18:32:46 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 16:20:20 by lomartin          #+#    #+#             */
/*   Updated: 2026/02/12 19:20:47 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** @brief Test if a string is only digit composed
** @param str string to test
** @return Non-zero if digit, zero otherwise
*/
int	ft_isfloat_str(char *str)
{
	int	point;

	point = 0;
	if (!str || !*str)
		return (0);
	if (*str == '+' || *str == '-')
		str++;
	while (*str)
	{
		if (*str == '.' || *str == ',')
		{
			if (point)
				return (0);
			point = 1;
			str++;
			continue ;
		}
		if (!ft_isdigit(*(str++)))
			return (0);
	}
	return (1);
}
