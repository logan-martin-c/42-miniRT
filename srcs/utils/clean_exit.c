/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 11:40:00 by lomartin          #+#    #+#             */
/*   Updated: 2026/03/08 23:20:31 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
//
#include "json.h"

void	clean_parsing(t_parsing_data *p_data)
{
	char	*gnl;

	if (p_data->map_fd > 2)
		close(p_data->map_fd);
	if (p_data->stream)
		fclose(p_data->stream);
	free_json(p_data->json);
	gnl = get_next_line(p_data->map_fd);
	free(gnl);
	ft_lstclear(&p_data->obj_lst, free);
}

void	clean_exec(t_exec_data *e_data)
{
	unsigned int	i;

	i = -1;
	e_data->stop = true;
	while (++i < e_data->nb_threads)
		pthread_join(e_data->threads[i], NULL);
	free(e_data->threads);
	free(e_data->tasks);
}

void	free_world(t_world_data *world, void *mlx)
{
	int	i;

	i = -1;
	while (++i < world->obj_count)
	{
		free(world->objs[i].material.tex_name);
		free(world->objs[i].material.normal_name);
		if (world->objs[i].material.tex.img)
			mlx_destroy_image(mlx, world->objs[i].material.tex.img);
	}
	free(world->objs);
	free(world->lights);
	free(world->color_tab);
}

void	clean_exit(int exit_status, t_global_data *g_data,
		t_parsing_data *p_data, t_exec_data *e_data)
{
	if (p_data)
		clean_parsing(p_data);
	free_world(&g_data->world, g_data->mlx.mlx);
	if (e_data)
		clean_exec(e_data);
	if (g_data->mlx.mlx)
	{
		mlx_do_key_autorepeaton(g_data->mlx.mlx);
		if (g_data->mlx.s_img_data.img)
			mlx_destroy_image(g_data->mlx.mlx, g_data->mlx.s_img_data.img);
		if (g_data->mlx.win)
			mlx_destroy_window(g_data->mlx.mlx, g_data->mlx.win);
		mlx_destroy_display(g_data->mlx.mlx);
		free(g_data->mlx.mlx);
	}
	exit(exit_status);
}
