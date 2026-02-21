/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 11:06:07 by lomartin          #+#    #+#             */
/*   Updated: 2026/02/21 17:12:10 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_obj_type	get_obj_type(char *obj_line)
{
	if ((!ft_strncmp(obj_line, "C", 1) || !ft_strncmp(obj_line, "L", 1)
			|| !ft_strncmp(obj_line, "A", 1)) && ft_isspace(obj_line[1]))
		return (_obj_param);
	else if ((!ft_strncmp(obj_line, "sp", 2) || !ft_strncmp(obj_line, "pl", 2)
			|| !ft_strncmp(obj_line, "cy", 2)) && ft_isspace(obj_line[2]))
		return (_obj_object);
	return (_obj_none);
}

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

int	is_normalized(t_vect3 pos)
{
	double	magnitude;

	pos.x = ft_abs(pos.x);
	pos.y = ft_abs(pos.y);
	pos.z = ft_abs(pos.z);
	if (pos.x < 0 || pos.x > 1 || pos.y < 0 || pos.y > 1 || pos.z < 0
		|| pos.z > 1)
		return (0);
	magnitude = sqrt(pos.x * pos.x + pos.y * pos.y + pos.z * pos.z);
	return ((magnitude <= (1 + NORM_TOLERANCE)) || (magnitude >= (1
				- NORM_TOLERANCE)));
}
