/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adastugu <adastugu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 16:08:54 by adastugu          #+#    #+#             */
/*   Updated: 2026/03/07 15:25:34 by adastugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void init_texture(t_global_data *g_data)
{
	int i;
	char *data;
	int bpp, size_line, endian;

	i = 0;
	while (i < g_data->world.obj_count)
	{
		if (g_data->world.objs[i].tex_name)
		{
			g_data->world.objs[i].tex.img = mlx_xpm_file_to_image(g_data->mlx.mlx,
					g_data->world.objs[i].tex_name,
					&g_data->world.objs[i].tex.width,
					&g_data->world.objs[i].tex.height);
			if (!g_data->world.objs[i].tex.img)
			{
				g_data->world.objs[i].tex_name = "UV";
				i++;
				continue ;
			}
			data = mlx_get_data_addr(g_data->world.objs[i].tex.img, &bpp,
					&size_line, &endian);
			g_data->world.objs[i].tex.pixels = (int *)data;
		}
		i++;
	}
}

void init_normal(t_global_data *g_data)
{
	int i;
	char *data;
	int bpp, size_line, endian;

	i = 0;
	while (i < g_data->world.obj_count)
	{
		if (g_data->world.objs[i].normal_name)
		{
			g_data->world.objs[i].normal.img = mlx_xpm_file_to_image(g_data->mlx.mlx,
					g_data->world.objs[i].normal_name,
					&g_data->world.objs[i].normal.width,
					&g_data->world.objs[i].normal.height);
			if (!g_data->world.objs[i].normal.img)
			{
				g_data->world.objs[i].normal_name = "error";
				i++;
				continue ;
			}
			data = mlx_get_data_addr(g_data->world.objs[i].normal.img, &bpp,
					&size_line, &endian);
			g_data->world.objs[i].normal.pixels = (int *)data;
		}
		i++;
	}
}
