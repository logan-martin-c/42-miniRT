/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 15:30:17 by lomartin          #+#    #+#             */
/*   Updated: 2026/02/18 15:31:51 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
//
#include "colors_maths.h"
#include "mlx_utils.h"

void	render_image(t_global_data *g_data)
{
	create_tasks(g_data->e_data);
	while (g_data->e_data->rendering)
		usleep(100);
}

int	update_display(t_global_data *g_data)
{
	unsigned long			time;
	static unsigned long	last_time = 0;
	int						elapsed;

	time = get_utime(0);
	elapsed = time - last_time;
	last_time = time;
	move_cam(&g_data->world, &g_data->mlx, &g_data->key, elapsed);
	if (g_data->world.static_frames != 2000)
	{
		render_image(g_data);
	}
	mlx_put_image_to_window(g_data->mlx.mlx, g_data->mlx.win,
		g_data->mlx.s_img_data.img, 0, 0);
	display_gui(&g_data->world, &g_data->mlx, elapsed);
	return (0);
}
