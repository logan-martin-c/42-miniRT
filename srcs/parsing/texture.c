/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adastugu <adastugu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 16:08:54 by adastugu          #+#    #+#             */
/*   Updated: 2026/03/10 11:09:28 by adastugu         ###   ########.fr       */
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
				ft_maperror("wrong texture file", -1, g_data->prog_name);
				clean_exit(1, g_data, NULL, NULL);
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
				ft_maperror("wrong normal file", -1, g_data->prog_name);
				clean_exit(1, g_data, NULL, NULL);
			}
			data = mlx_get_data_addr(g_data->world.objs[i].material.normal.img,
					&tmp, &tmp, &tmp);
			g_data->world.objs[i].material.normal.pixels = (int *)data;
		}
	}
}
