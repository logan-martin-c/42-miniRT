/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 11:06:07 by lomartin          #+#    #+#             */
/*   Updated: 2026/02/14 16:29:54 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	check_args_count(char **args, unsigned int min, unsigned int max)
{
	unsigned int	i;

	if (min > max || (!args && min))
		return (-1);
	if (!args && !min)
		return (0);
	i = 0;
	while (i < min)
	{
		if (!args[i])
			return (-1);
		i++;
	}
	while (i < max)
	{
		if (!args[i])
			return (i - 1);
		i++;
	}
	if (args[i])
		return (-1);
	return (i);
}

int	is_normalized(t_pos_xyz pos)
{
	double	magnitude;

	pos.x = ft_abs(pos.x);
	pos.y = ft_abs(pos.y);
	pos.z = ft_abs(pos.z);
	if (pos.x < 0 || pos.x > NORM_PREC || pos.y < 0 || pos.y > NORM_PREC || pos.z < 0
		|| pos.z > NORM_PREC)
		return (0);
	magnitude = sqrt(pos.x * pos.x + pos.y * pos.y + pos.z * pos.z);
	return ((magnitude < NORM_PREC + NORM_TOLERANCE) && (magnitude > NORM_PREC - NORM_TOLERANCE));
}
