/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 17:18:35 by lomartin          #+#    #+#             */
/*   Updated: 2026/02/21 17:21:27 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_vect2	get_next_pos(t_vect2 prev_pos, size_t prev_strlen)
{
	if (prev_pos.x + prev_strlen + 30 < WIN_WIDTH)
		return ((t_vect2){prev_pos.x + prev_strlen + 30, prev_pos.y});
	if (prev_pos.y < WIN_HEIGHT / 2)
		return ((t_vect2){10, WIN_HEIGHT - prev_pos.y});
	return ((t_vect2){10, WIN_HEIGHT - prev_pos.y + 30});
}

void	display_int(char *name, int value, t_mlx_data *mlx, bool reset)
{
	char			int_str[12];
	static t_vect2	pos = {10, 20};
	int				total_print_len;

	if (reset)
		pos = (t_vect2){10, 20};
	ft_itoa_pure(value, int_str);
	total_print_len = (ft_strlen(name) + ft_strlen(int_str)) * 5 + 5;
	if (pos.x + total_print_len > WIN_WIDTH - 10)
		pos = get_next_pos(pos, total_print_len);
	mlx_string_put(mlx->mlx, mlx->win, pos.x, pos.y, 0xFFFFFF, name);
	mlx_string_put(mlx->mlx, mlx->win, pos.x + ft_strlen(name) * 5 + 5, pos.y,
		0xFFFFFF, int_str);
	pos = get_next_pos(pos, total_print_len);
}

void	display_gui(t_world_data *world, t_mlx_data *mlx, int elapsed)
{
	static int	fps = __INT_MAX__;

	if (fps == __INT_MAX__)
		fps = 1000000.0 / elapsed;
	else
		fps = (fps * 19 + 1000000.0 / elapsed) / 20;
	display_int("fps: ", fps, mlx, true);
	display_int("x: ", world->cam.pos.x, mlx, false);
	display_int("y: ", world->cam.pos.y, mlx, false);
	display_int("z: ", world->cam.pos.z, mlx, false);
	display_int("fov: ", world->cam.fov, mlx, false);
	display_int("speed: ", world->cam.speed, mlx, false);
}
