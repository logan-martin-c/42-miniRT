/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adastugu <adastugu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 16:08:54 by adastugu          #+#    #+#             */
/*   Updated: 2026/03/09 13:47:43 by adastugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	init_texture(t_global_data *g_data)
{
	int		i;
	char	*data;
	int		tmp;

	i = -1;
	while (++i < g_data->world.obj_count)
	{
		if (g_data->world.objs[i].material.tex_name)
		{
			g_data->world.objs[i].material.tex.img
				= mlx_xpm_file_to_image(g_data->mlx.mlx,
					g_data->world.objs[i].material.tex_name,
					&g_data->world.objs[i].material.tex.width,
					&g_data->world.objs[i].material.tex.height);
			if (!g_data->world.objs[i].material.tex.img)
			{
				g_data->world.objs[i].material.tex_name = "UV";
				i++;
				continue ;
			}
			data = mlx_get_data_addr(g_data->world.objs[i].material.tex.img,
					&tmp, &tmp, &tmp);
			g_data->world.objs[i].material.tex.pixels = (int *)data;
		}
	}
}

void	init_normal(t_global_data *g_data)
{
	int		i;
	char	*data;
	int		tmp;

	i = -1;
	while (++i < g_data->world.obj_count)
	{
		if (g_data->world.objs[i].material.normal_name)
		{
			g_data->world.objs[i].material.normal.img
				= mlx_xpm_file_to_image(g_data->mlx.mlx,
					g_data->world.objs[i].material.normal_name,
					&g_data->world.objs[i].material.normal.width,
					&g_data->world.objs[i].material.normal.height);
			if (!g_data->world.objs[i].material.normal.img)
			{
				g_data->world.objs[i].material.normal_name = "error";
				i++;
				continue ;
			}
			data = mlx_get_data_addr(g_data->world.objs[i].material.normal.img,
					&tmp, &tmp, &tmp);
			g_data->world.objs[i].material.normal.pixels = (int *)data;
		}
	}
}
