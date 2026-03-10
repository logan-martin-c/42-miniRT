/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 16:38:47 by lomartin          #+#    #+#             */
/*   Updated: 2026/03/10 14:10:25 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	key_press_2(int keycode, t_global_data *g_data, t_object *obj)
{
	if (keycode == RIGHT_BRACE && (obj->e_type == _sphere
			|| obj->e_type == _cylinder || obj->e_type == _cone
			|| obj->e_type == _light))
	{
		obj->u_data.sphere.radius++;
		g_data->world.static_frames = -1;
	}
	if (keycode == LEFT_BRACE && (obj->e_type == _sphere
			|| obj->e_type == _cylinder || obj->e_type == _cone
			|| obj->e_type == _light) && obj->u_data.sphere.radius > 0)
	{
		obj->u_data.sphere.radius--;
		g_data->world.static_frames = -1;
	}
	if (keycode == QUOTE && (obj->e_type == _cylinder || obj->e_type == _cone))
	{
		obj->u_data.cylinder.height++;
		g_data->world.static_frames = -1;
	}
	if (keycode == COLON && (obj->e_type == _cylinder || obj->e_type == _cone)
		&& obj->u_data.cylinder.height > 0)
	{
		obj->u_data.cylinder.height--;
		g_data->world.static_frames = -1;
	}
}

int	key_press(int keycode, t_global_data *g_data)
{
	if (keycode == ESC)
		win_close(g_data);
	if (keycode == W_KEY)
		g_data->key.w = 1;
	if (keycode == A_KEY)
		g_data->key.a = 1;
	if (keycode == S_KEY)
		g_data->key.s = 1;
	if (keycode == D_KEY)
		g_data->key.d = 1;
	if (keycode == SPACE_KEY)
		g_data->key.space = 1;
	if (keycode == CTRL_KEY)
		g_data->key.ctrl = 1;
	if (keycode == PLUS_KEY)
		g_data->world.cam.speed++;
	if (keycode == MINUS_KEY && g_data->world.cam.speed > 0)
		g_data->world.cam.speed--;
	if (keycode == RIGHT_BRACE || keycode == LEFT_BRACE || keycode == QUOTE
		|| (keycode == COLON && g_data->world.selected_obj))
		key_press_2(keycode, g_data, g_data->world.selected_obj);
	return (0);
}

int	key_release(int keycode, t_global_data *g_data)
{
	if (keycode == W_KEY)
		g_data->key.w = 0;
	if (keycode == A_KEY)
		g_data->key.a = 0;
	if (keycode == S_KEY)
		g_data->key.s = 0;
	if (keycode == D_KEY)
		g_data->key.d = 0;
	if (keycode == SPACE_KEY)
		g_data->key.space = 0;
	if (keycode == CTRL_KEY)
		g_data->key.ctrl = 0;
	return (0);
}

int	update_fov(int button, int x, int y, t_global_data *g_data)
{
	(void)x;
	(void)y;
	if (button == 1 || button == 3)
		object_picker(button, x, y, g_data);
	if (button == 4 && g_data->world.cam.fov > 1)
		g_data->world.cam.fov--;
	if (button == 5 && g_data->world.cam.fov < 180)
		g_data->world.cam.fov++;
	init_viewport(&g_data->world.viewport, g_data->world.cam.fov);
	g_data->world.static_frames = -1;
	return (1);
}

void	set_hooks(t_global_data *g_data)
{
	mlx_hook(g_data->mlx.win, 2, 1L, key_press, g_data);
	mlx_hook(g_data->mlx.win, 3, 1L << 1, key_release, g_data);
	mlx_hook(g_data->mlx.win, 4, 04, object_picker, g_data);
	mlx_hook(g_data->mlx.win, 17, 1L, win_close, g_data);
	mlx_hook(g_data->mlx.win, 4, 1L << 2, update_fov, g_data);
	mlx_loop_hook(g_data->mlx.mlx, update_display, g_data);
	mlx_mouse_move(g_data->mlx.mlx, g_data->mlx.win, WIN_WIDTH / 2, WIN_HEIGHT
		/ 2);
}
