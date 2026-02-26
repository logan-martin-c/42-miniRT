/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 11:40:00 by lomartin          #+#    #+#             */
/*   Updated: 2026/02/26 14:48:28 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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

void	free_world(t_world_data *world)
{
	free(world->objs);
	free(world->lights);
	free(world->color_tab);
}

void	clean_exit(int exit_status, t_global_data *g_data,
		t_parsing_data *p_data, t_exec_data *e_data)
{
	char	*gnl;

	if (p_data)
	{
		if (p_data->map_fd > 2)
			close(p_data->map_fd);
		gnl = get_next_line(p_data->map_fd);
		free(gnl);
		ft_lstclear(&p_data->obj_lst, free);
	}
	free_world(&g_data->world);
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
