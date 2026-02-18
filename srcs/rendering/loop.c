/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 15:30:17 by lomartin          #+#    #+#             */
/*   Updated: 2026/02/18 11:50:07 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "colors_maths.h"
#include "mlx_utils.h"

int	update_display(t_global_data *g_data)
{
	unsigned long			time;
	static unsigned long	last_time = 0;
	int						elapsed;
	int						fps;
	char					s_fps[12];

	time = get_utime(0);
	elapsed = time - last_time;
	last_time = time;
	fps = 1000000 / elapsed;
	rotate_cam(&g_data->world.cam, &g_data->mlx);
	update_cam_pos(&g_data->key, &g_data->world.cam, elapsed);
	render_canva((t_pos_xyz){0, 0, 0}, (t_pos_xyz){WIN_WIDTH, WIN_HEIGHT, 0},
		&g_data->world, &g_data->mlx);
	mlx_put_image_to_window(g_data->mlx.mlx, g_data->mlx.win,
		g_data->mlx.s_img_data.img, 0, 0);
	ft_itoa_pure(fps, s_fps);
	mlx_string_put(g_data->mlx.mlx, g_data->mlx.win, 10, 20, 0xFFFFFF, s_fps);
	return (0);
}
