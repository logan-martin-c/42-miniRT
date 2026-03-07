/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adastugu <adastugu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 11:45:10 by adastugu          #+#    #+#             */
/*   Updated: 2026/03/07 17:04:33 by adastugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	new_cone(t_parsing_data *p_data, char *obj_line, t_global_data *g_data,
		t_object *node)
{
	char	**params;

	params = ft_split_charset(obj_line, " \t\v\f\r");
	if (!params)
	{
		free(node);
		clean_exit(ft_perror(NULL, g_data->prog_name), g_data, p_data, NULL);
	}
	if (check_args_count(params, 6, 11) == -1)
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
	if (params[6])
		node->material.smoothness = ft_atof(params[6]);
	if (params[6] && params[7])
		node->material.refraction = ft_atof(params[7]);
	else
		node->material.refraction = 1;
	if (params[6] && params[7] && params[8])
		node->material.reflectance = ft_atof(params[8]);
	if (params[6] && params[7] && params[8] && params[9])
		node->tex_name = ft_strdup(params[9]);
	if (params[6] && params[7] && params[8] && params[9] && params[10])
		node->normal_name = ft_strdup(params[10]);
	node->e_type = _cone;
	ft_lstadd_front(&p_data->obj_lst, ft_lstnew(node));
	return (ft_free_strs(params), 0);
}
