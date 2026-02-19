/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 11:40:00 by lomartin          #+#    #+#             */
/*   Updated: 2026/02/15 22:12:27 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// void	free_node(void *node)
// {
// 	free(((t_object *)(node))->data);
// 	free(node);
// }

// void	free_objs_array(t_object *array, int size)
// {
// 	int	i;
//
// 	i = -1;
// 	while (++i < size)
// 	{
// 		if (array[i].e_type != _sphere)
// 			free(array[i].data);
// 	}
// 	free(array);
// }

void	clean_exit(int exit_status, t_global_data *g_data,
		t_parsing_data *p_data)
{
	char	*gnl;

	if (p_data)
	{
		gnl = "";
		while (gnl && p_data->map_fd != -1)
		{
			gnl = get_next_line(p_data->map_fd);
			free(gnl);
		}
		ft_lstclear(&p_data->obj_lst, free);
	}
	free(g_data->world.objs);
	// free_objs_array(g_data->world.objs, g_data->world.obj_count);
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
