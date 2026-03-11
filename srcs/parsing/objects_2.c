/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 11:45:10 by adastugu          #+#    #+#             */
/*   Updated: 2026/03/09 15:20:13 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	new_cone(t_parsing_data *p_data, char *obj_line, t_global_data *g_data,
		t_object *node)
{
	char	**params;

	params = ft_split_charset(obj_line, " \t\v\f\r");
	set_default_obj(node);
	if (!params)
		free(node);
	if (!params)
		clean_exit(ft_perror(NULL, g_data->prog_name), g_data, p_data, NULL);
	if (check_args_count(params, 6, 8) == -1)
		return (ft_free_strs(params),
			ft_maperror("cone : invalid parameters", p_data->line_nb,
				g_data->prog_name));
	if (parse_pos(params[1], &node->pos, 0) || parse_pos(params[2], &node->rot,
			1) || parse_float(params[3], &node->u_data.cone.radius)
		|| parse_float(params[4], &node->u_data.cone.height)
		|| parse_raw_color(params[5], &node->material.color))
		return (ft_free_strs(params),
			ft_maperror("cone : invalid parameters", p_data->line_nb,
				g_data->prog_name));
	if (parse_material(&node->material, &params[6]))
		return (ft_perror(NULL, g_data->prog_name));
	if (put_in_lst(node, g_data, p_data))
		return (ft_perror(NULL, g_data->prog_name));
	return (node->e_type = _cone, ft_free_strs(params), 0);
}
