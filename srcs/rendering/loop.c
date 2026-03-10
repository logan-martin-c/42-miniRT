/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adastugu <adastugu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 15:30:17 by lomartin          #+#    #+#             */
/*   Updated: 2026/03/06 14:35:03 by adastugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
//
#include "colors_maths.h"
#include "mlx_utils.h"

void	render_image(t_global_data *g_data, t_exec_data *e_data)
{
	e_data->tasks_done = 0;
	e_data->current_task = 0;
	e_data->to_do = e_data->nb_tasks;
	e_data->rendering = true;
	pthread_mutex_lock(&g_data->e_data->mutex);
	while (g_data->e_data->rendering)
	{
		pthread_mutex_unlock(&g_data->e_data->mutex);
		usleep(200);
		pthread_mutex_lock(&g_data->e_data->mutex);
	}
	pthread_mutex_unlock(&g_data->e_data->mutex);
}

int	update_display(t_global_data *g_data)
{
	unsigned long			time;
	static unsigned long	last_time = 0;
	int						elapsed;

	time = get_utime(0);
	elapsed = time - last_time;
	last_time = time;
	move_cam(&g_data->world, &g_data->mlx, &g_data->key,
		ft_min(elapsed, 500000));
	move_object(g_data->world.selected_obj, &g_data->world, &g_data->key,
		ft_min(elapsed, 500000));
	if (g_data->world.static_frames != -2)
		render_image(g_data, g_data->e_data);
	mlx_put_image_to_window(g_data->mlx.mlx, g_data->mlx.win,
		g_data->mlx.s_img_data.img, 0, 0);
	display_gui(&g_data->world, &g_data->mlx, elapsed);
	return (0);
}
