/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 14:44:17 by lomartin          #+#    #+#             */
/*   Updated: 2026/02/26 14:44:26 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	new_light(t_parsing_data *p_data, char *obj_line, t_global_data *g_data,
		t_object *node)
{
	char	**params;

	params = ft_split_charset(obj_line, " \t\v\f\r");
	if (!params)
		return (ft_perror(NULL, g_data->prog_name));
	if (check_args_count(params, 4, 4) == -1)
		return (ft_free_strs(params), ft_maperror("light : invalid parameters",
				p_data->line_nb, g_data->prog_name));
	if (parse_pos(params[1], &node->pos, 0) || !ft_isfloat_str(params[2])
		|| parse_raw_color(params[3], &node->color))
		return (ft_free_strs(params), ft_maperror("light : invalid parameters",
				p_data->line_nb, g_data->prog_name));
	node->u_data.light.ratio = ft_atof(params[2]);
	if (node->u_data.light.ratio > 1 || node->u_data.light.ratio < 0)
		return (ft_free_strs(params), ft_maperror("light : invalid ratio",
				p_data->line_nb, g_data->prog_name));
	node->e_type = _light;
	ft_lstadd_front(&p_data->obj_lst, ft_lstnew(node));
	return (ft_free_strs(params), 0);
}
