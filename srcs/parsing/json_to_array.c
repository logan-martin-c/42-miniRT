/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   json_to_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 14:45:52 by lomartin          #+#    #+#             */
/*   Updated: 2026/03/09 11:49:00 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
//
#include "json.h"

int	pair_to_array(t_pair *pair, t_parsing_data *p_data, t_global_data *g_data,
		t_world_data *world)
{
	if (!ft_strcmp("sphere", pair->key))
		return (json_to_sphere(pair->value, g_data, world));
	if (!ft_strcmp("cylinder", pair->key))
		return (json_to_cylinder(pair->value, g_data, world));
	if (!ft_strcmp("cone", pair->key))
		return (json_to_cone(pair->value, g_data, world));
	if (!ft_strcmp("plane", pair->key))
		return (json_to_plane(pair->value, g_data, world));
	if (!ft_strcmp("light", pair->key))
		return (json_to_light(pair->value, g_data, world));
	if (!ft_strcmp("ambient_light", pair->key))
		return (json_to_a_light(pair->value, p_data, g_data, world));
	if (!ft_strcmp("camera", pair->key))
		return (json_to_cam(pair->value, p_data, g_data, world));
	return (1);
}

int	json_to_array(t_parsing_data *p_data, t_global_data *g_data,
		t_world_data *world)
{
	char	*error;
	size_t	tokens_nb;
	size_t	i;

	if (p_data->json.e_type != _brace)
		return (ft_maperror("invalid map", -1, g_data->prog_name));
	tokens_nb = p_data->json.u_data.s_brace.size;
	i = -1;
	while (++i < tokens_nb)
	{
		if (pair_to_array(p_data->json.u_data.s_brace.data + i, p_data, g_data,
				world))
		{
			error = ft_strjoin_mult(3, "invalid object '",
					p_data->json.u_data.s_brace.data[i].key, "'");
			ft_maperror(error, -1, g_data->prog_name);
			return (free(error), 1);
		}
	}
	free_json(p_data->json);
	return (0);
}
