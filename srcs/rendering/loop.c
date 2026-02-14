/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 15:30:17 by lomartin          #+#    #+#             */
/*   Updated: 2026/02/14 19:16:09 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	update_display(t_global_data *data)
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
	// if (vars->r_data.funky_mode)
	// 	vars->r_data.color += 0x00030205 * elapsed;
	// update_move_status(vars);
	// update_cam_pos(vars, elapsed);
	// rotate_cam(vars);
	ft_bzero(data->mlx.s_img_data.addr, WIN_HEIGHT * WIN_WIDTH
		* data->mlx.s_img_data.bits_per_pixel / 8);
	// ft_memset_int(data->mlx.s_img_data.addr, get_color_chars(255, 255, 67,
	//		39), WIN_HEIGHT * WIN_WIDTH
	//  	* data->mlx.s_img_data.bits_per_pixel / 8);
	// draw_map(vars, -1, -1);
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.win,
		data->mlx.s_img_data.img, 0, 0);
	ft_itoa_pure(fps, s_fps);
	mlx_string_put(data->mlx.mlx, data->mlx.win, 10, 20, 0xFFFFFF, s_fps);
	return (0);
}
