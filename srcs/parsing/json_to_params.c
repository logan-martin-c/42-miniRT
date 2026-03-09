/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   json_to_params.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 22:39:37 by lomartin          #+#    #+#             */
/*   Updated: 2026/03/08 22:39:55 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
//
#include "json.h"

int	json_cam_params(t_pair *pair, t_cam_data *cam, t_parsing_check *check,
		t_global_data *g_data)
{
	char	*error;
	float	temp;
	int		ret;

	if (!ft_strcmp(pair->key, "position") && !check->pos)
		return (check->pos = 1, parse_json_pos(&pair->value, &cam->pos, false));
	if (!ft_strcmp(pair->key, "rotation") && !check->rot)
		return (check->rot = 1, parse_json_pos(&pair->value, &cam->forward,
				true));
	if (!ft_strcmp(pair->key, "fov") && !check->fov)
	{
		check->fov = 1;
		ret = parse_json_float(&pair->value, &temp, _fov);
		cam->fov = (int)temp;
		return (ret);
	}
	error = ft_strjoin_mult(3, "invalid camera parameter '", pair->key, "'");
	ft_maperror(error, -1, g_data->prog_name);
	return (free(error), 1);
}

int	json_to_cam(t_json json, t_parsing_data *p_data, t_global_data *g_data,
		t_world_data *world)
{
	size_t			i;
	t_parsing_check	check;

	if (p_data->map_data.cam)
		return (ft_maperror("Multiple cam definition is forbidden",
				p_data->line_nb, g_data->prog_name));
	ft_bzero(&check, sizeof(check));
	if (json.e_type != _brace)
		return (1);
	i = -1;
	while (++i < json.u_data.s_brace.size)
	{
		if (json_cam_params(json.u_data.s_brace.data + i, &world->cam, &check,
				g_data))
			return (1);
	}
	if (!check.pos || !check.rot || !check.fov)
		return (ft_maperror("incomplete plane parameters", -1,
				g_data->prog_name));
	p_data->map_data.cam = true;
	return (0);
}

int	json_a_light_params(t_pair *pair, t_ambient_light_data *a_light,
		t_parsing_check *check, t_global_data *g_data)
{
	char	*error;

	if (!ft_strcmp(pair->key, "color") && !check->color)
		return (check->color = 1, parse_json_raw_color(&pair->value,
				&a_light->color));
	if (!ft_strcmp(pair->key, "ratio") && !check->ratio)
		return (check->ratio = 1, parse_json_float(&pair->value,
				&a_light->ratio, _ratio));
	error = ft_strjoin_mult(3, "invalid ambient light parameter '", pair->key,
			"'");
	ft_maperror(error, -1, g_data->prog_name);
	return (free(error), 1);
}

int	json_to_a_light(t_json json, t_parsing_data *p_data, t_global_data *g_data,
		t_world_data *world)
{
	size_t			i;
	t_parsing_check	check;

	if (p_data->map_data.ambient_light)
		return (ft_maperror("Multiple ambient light definition is forbidden",
				p_data->line_nb, g_data->prog_name));
	ft_bzero(&check, sizeof(check));
	if (json.e_type != _brace)
		return (1);
	i = -1;
	while (++i < json.u_data.s_brace.size)
	{
		if (json_a_light_params(json.u_data.s_brace.data + i,
				&world->ambient_light, &check, g_data))
			return (1);
	}
	if (!check.color || !check.ratio)
		return (ft_maperror("incomplete ambient light parameters", -1,
				g_data->prog_name));
	p_data->map_data.ambient_light = true;
	return (0);
}
