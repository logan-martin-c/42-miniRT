/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 15:30:17 by lomartin          #+#    #+#             */
/*   Updated: 2026/02/16 15:50:27 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "../../includes/minirt.h"

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
	// if (vars->r_data.funky_mode)
	// 	vars->r_data.color += 0x00030205 * elapsed;
	update_move_status(&g_data->world.cam, &g_data->key);
	update_cam_pos(&g_data->world.cam, elapsed);
	rotate_cam(&g_data->world.cam, &g_data->mlx);
	// int	c_a = get_color_chars(255, 255, 126, 32);
	// int	c_b = get_color_chars(255, 0, 0, 0);
	ft_bzero(g_data->mlx.s_img_data.addr, WIN_HEIGHT * WIN_WIDTH
	 	* g_data->mlx.s_img_data.bits_per_pixel / 8);
	// ft_memset_int(g_data->mlx.s_img_data.addr, color_sup(c_a, c_b), WIN_HEIGHT * WIN_WIDTH
	// 	* g_data->mlx.s_img_data.bits_per_pixel / 8);
	// draw_map(vars, -1, -1);
	//trace_rays(&g_data->world, &g_data->mlx);
	t_pos_xyz test = project((t_pos_xyz){0, 0, 0}, &g_data->world.cam);
	int	color = color_sup(get_color_chars(255, 255, 255, 255), 0);
	my_mlx_pixel_put(&g_data->mlx, test, color);
	test = project((t_pos_xyz){50000, 0, 0}, &g_data->world.cam);
	color = color_sup(get_color_chars(255, 255, 0, 0), 0);
	if (test.z > 1)
	my_mlx_pixel_put(&g_data->mlx, test, color);
	test = project((t_pos_xyz){0, 50000, 0}, &g_data->world.cam);
	color = color_sup(get_color_chars(255, 0, 255, 0), 0);
	if (test.z > 1)
	my_mlx_pixel_put(&g_data->mlx, test, color);
	test = project((t_pos_xyz){0, 0, 50000}, &g_data->world.cam);
	color = color_sup(get_color_chars(255, 0, 0, 255), 0);
	if (test.z > 1)
	my_mlx_pixel_put(&g_data->mlx, test, color);
	color = get_color_chars(50, 54, 167, 221);
	render_canva((t_pos_xyz){0, 0, 0}, (t_pos_xyz){WIN_WIDTH, WIN_HEIGHT, 0}, &g_data->world, &g_data->mlx, color);
	// color = get_color_chars(150, 35, 154, 124);
	// render_canva((t_pos_xyz){100, 100, 0}, (t_pos_xyz){300, 200, 0}, &g_data->world, &g_data->mlx, color);
	mlx_put_image_to_window(g_data->mlx.mlx, g_data->mlx.win,
		g_data->mlx.s_img_data.img, 0, 0);
	ft_itoa_pure(fps, s_fps);
	mlx_string_put(g_data->mlx.mlx, g_data->mlx.win, 10, 20, 0xFFFFFF, s_fps);
	return (0);
}
