/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adastugu <adastugu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 18:51:58 by lomartin          #+#    #+#             */
/*   Updated: 2026/02/24 14:01:24 by adastugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	set_cam(t_parsing_data *p_data, char *obj_line, t_global_data *g_data)
{
	char	**params;

	if (p_data->map_data.cam)
		return (ft_maperror("Multiple cam definition is forbidden",
				p_data->line_nb, g_data->prog_name));
	params = ft_split_charset(obj_line, " \t\v\f\r");
	if (!params)
		return (ft_perror(NULL, g_data->prog_name));
	if (check_args_count(params, 4, 4) == -1)
		return (ft_free_strs(params), ft_maperror("camera : invalid parameters",
				p_data->line_nb, g_data->prog_name));
	if (parse_pos(params[1], &g_data->world.cam.pos, 0) || parse_pos(params[2],
			&g_data->world.cam.forward, 1) || !ft_isdigit_str(params[3]))
		return (ft_free_strs(params), ft_maperror("camera : invalid parameters",
				p_data->line_nb, g_data->prog_name));
	g_data->world.cam.fov = ft_atoi(params[3]);
	if (g_data->world.cam.fov > 180 || g_data->world.cam.fov < 0)
		return (ft_free_strs(params),
			ft_maperror("camera : invalid "
				"parameters",
				p_data->line_nb,
				g_data->prog_name));
	p_data->map_data.cam = 1;
	return (ft_free_strs(params), 0);
}

int	set_ambient_light(t_parsing_data *p_data, char *obj_line,
		t_global_data *g_data)
{
	char	**params;
	float	raw_ratio;

	if (p_data->map_data.ambient_light)
		return (ft_maperror("Multiple ambient light definition is forbidden",
				p_data->line_nb, g_data->prog_name));
	params = ft_split_charset(obj_line, " \t\v\f\r");
	if (!params)
		return (ft_perror(NULL, g_data->prog_name));
	if (check_args_count(params, 3, 3) == -1)
		return (ft_free_strs(params),
			ft_maperror("ambient light : invalid parameters", p_data->line_nb,
				g_data->prog_name));
	if (!ft_isfloat_str(params[1]) || parse_raw_color(params[2],
			&g_data->world.ambient_light.color))
		return (ft_free_strs(params),
			ft_maperror("ambient light : invalid parameters", p_data->line_nb,
				g_data->prog_name));
	raw_ratio = ft_atof(params[1]);
	if (raw_ratio > 1 || raw_ratio < 0)
		return (ft_free_strs(params),
			ft_maperror("ambient light : invalid ratio", p_data->line_nb,
				g_data->prog_name));
	g_data->world.ambient_light.ratio = 255 * raw_ratio;
	return (p_data->map_data.ambient_light = 1, ft_free_strs(params), 0);
}

void	parse_params(t_parsing_data *p_data, char *obj_line,
		t_global_data *g_data)
{
	int	ret;

	ret = 1;
	if (!ft_strncmp(obj_line, "C", 1) && ft_isspace(obj_line[1]))
		ret = set_cam(p_data, obj_line, g_data);
	else if (!ft_strncmp(obj_line, "A", 1) && ft_isspace(obj_line[1]))
		ret = set_ambient_light(p_data, obj_line, g_data);
	if (ret)
		(free(obj_line), clean_exit(1, g_data, p_data, NULL));
}
