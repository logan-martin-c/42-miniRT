/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   json_sub_parameters.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 19:48:49 by lomartin          #+#    #+#             */
/*   Updated: 2026/03/08 23:09:55 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
//
#include "json.h"

int	parse_json_pos(t_json *json, t_vect3 *pos, char normalized)
{
	if (json->e_type != _array || json->size != 3)
		return (1);
	pos->x = json->u_data.array[0];
	pos->y = json->u_data.array[1];
	pos->z = json->u_data.array[2];
	if (normalized)
	{
		if (!is_normalized(*pos))
			return (2);
	}
	return (0);
}

int	parse_json_raw_color(t_json *json, t_float_color *color)
{
	int	i;

	if (json->e_type != _array || (json->size != 3 && json->size != 4))
		return (1);
	i = -1;
	if (json->size == 4)
		color->a = json->u_data.array[++i];
	else
		color->a = 255;
	color->r = json->u_data.array[++i];
	color->g = json->u_data.array[++i];
	color->b = json->u_data.array[++i];
	if (color->a > 255 || color->a < 0 || color->r > 255 || color->r < 0
		|| color->g > 255 || color->g < 0 || color->b > 255 || color->b < 0)
		return (2);
	*color = (t_float_color){color->a / 255.0, color->r / 255.0, color->g
		/ 255.0, color->b / 255.0};
	return (0);
}

int	parse_json_float(t_json *json, float *value, t_clamp_mode mode)
{
	if (json->e_type != _float)
		return (1);
	*value = json->u_data.num;
	if (mode == _ratio && (*value > 1 || *value < 0))
		return (2);
	if (mode == _positive && (*value < 0))
		return (2);
	if (mode == _fov && (*value > 180 || *value < 1))
		return (2);
	return (0);
}

int	parse_json_string(t_json *json, char **value)
{
	if (json->e_type != _string)
		return (1);
	*value = ft_strdup(json->u_data.str);
	return (0);
}

int	parse_json_material(t_pair *pair, t_parsing_check *check,
		t_material *material)
{
	if (!ft_strcmp(pair->key, "color") && !check->color)
		return (check->color = 1, parse_json_raw_color(&pair->value,
				&material->color));
	if (!ft_strcmp(pair->key, "refraction") && !check->refr)
		return (check->refr = 1, parse_json_float(&pair->value,
				&material->refraction, _positive));
	if (!ft_strcmp(pair->key, "reflectance") && !check->refl)
		return (check->refl = 1, parse_json_float(&pair->value,
				&material->reflectance, _ratio));
	if (!ft_strcmp(pair->key, "smoothness") && !check->smo)
		return (check->smo = 1, parse_json_float(&pair->value,
				&material->smoothness, _ratio));
	return (2);
}
