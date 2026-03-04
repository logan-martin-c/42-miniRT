/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub_parameters.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adastugu <adastugu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 19:48:49 by lomartin          #+#    #+#             */
/*   Updated: 2026/03/04 14:18:50 by adastugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	parse_pos(char *str, t_vect3 *pos, char normalized)
{
	char	**spl_str;

	spl_str = ft_split(str, ',');
	if (!spl_str || check_args_count(spl_str, 3, 3) == -1)
		return (ft_free_strs(spl_str), 1);
	if (!ft_isfloat_str(spl_str[0]) || !ft_isfloat_str(spl_str[1])
		|| !ft_isfloat_str(spl_str[2]))
		return (ft_free_strs(spl_str), 2);
	pos->x = ft_atof(spl_str[0]);
	pos->y = ft_atof(spl_str[1]);
	pos->z = ft_atof(spl_str[2]);
	if (normalized)
	{
		if (!is_normalized(*pos))
			return (ft_free_strs(spl_str), 3);
	}
	ft_free_strs(spl_str);
	return (0);
}

int	parse_raw_color(char *str, t_float_color *color)
{
	int			args_count;
	char		**spl_str;
	int			i;

	spl_str = ft_split(str, ',');
	args_count = check_args_count(spl_str, 3, 4);
	if (!spl_str || args_count == -1)
		return (ft_free_strs(spl_str), 1);
	if (!ft_isdigit_str(spl_str[0]) || !ft_isdigit_str(spl_str[1])
		|| !ft_isdigit_str(spl_str[2]))
		return (ft_free_strs(spl_str), 1);
	i = -1;
	if (args_count == 4)
		color->a = ft_atoi(spl_str[++i]);
	else
		color->a = 255;
	color->r = ft_atoi(spl_str[++i]);
	color->g = ft_atoi(spl_str[++i]);
	color->b = ft_atoi(spl_str[++i]);
	if (color->a > 255 || color->a < 0 || color->r > 255 || color->r < 0 || color->g > 255 || color->g < 0
		|| color->b > 255 || color->b < 0)
		return (ft_free_strs(spl_str), 2);
	*color = (t_float_color){color->a / 255.0, color->r / 255.0, color->g / 255.0, color->b / 255.0};
	return (ft_free_strs(spl_str), 0);
}

int	parse_float(char *str, float *value)
{
	*value = atof(str);
	return (0);
}
