/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   json_to_light.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 22:37:35 by lomartin          #+#    #+#             */
/*   Updated: 2026/03/08 22:37:40 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
//
#include "json.h"

int	json_light_params(t_pair *pair, t_object *obj, t_parsing_check *check,
		t_global_data *g_data)
{
	char	*error;

	if (!ft_strcmp(pair->key, "position") && !check->pos)
		return (check->pos = 1, parse_json_pos(&pair->value, &obj->pos, false));
	if (!ft_strcmp(pair->key, "rotation") && !check->rot)
		return (check->rot = 1, parse_json_pos(&pair->value, &obj->rot, true));
	if (!ft_strcmp(pair->key, "color") && !check->color)
		return (check->color = 1, parse_json_raw_color(&pair->value,
				&obj->material.color));
	if (!ft_strcmp(pair->key, "diameter") && !check->diamet)
		return (check->diamet = 1, parse_json_float(&pair->value,
				&obj->u_data.light.radius, _positive));
	if (!ft_strcmp(pair->key, "ratio") && !check->ratio)
		return (check->ratio = 1, parse_json_float(&pair->value,
				&obj->u_data.light.ratio, _ratio));
	error = ft_strjoin_mult(3, "invalid light parameter '", pair->key, "'");
	ft_maperror(error, -1, g_data->prog_name);
	return (free(error), 1);
}

int	json_to_light(t_json json, t_global_data *g_data, t_world_data *world)
{
	size_t			i;
	t_parsing_check	check;

	ft_bzero(&check, sizeof(check));
	if (json.e_type != _brace)
		return (1);
	world->lights = ft_realloc(world->lights, world->light_count
			* sizeof(t_object), (world->light_count + 1) * sizeof(t_object));
	world->lights[world->light_count].u_data.light.radius = 0;
	i = -1;
	while (++i < json.u_data.s_brace.size)
	{
		if (json_light_params(json.u_data.s_brace.data + i, world->lights
				+ world->light_count, &check, g_data))
			return (1);
	}
	if (check.diamet)
		world->lights[world->light_count].u_data.light.radius *= 0.5;
	world->lights[world->light_count].e_type = _light;
	world->lights[world->light_count].init_rot = (t_vect3){0, 0, 1};
	++world->light_count;
	if (!check.pos || !check.ratio || !check.color)
		return (ft_maperror("incomplete light parameters", -1,
				g_data->prog_name));
	return (0);
}
