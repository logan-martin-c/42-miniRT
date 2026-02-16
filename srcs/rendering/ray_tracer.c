/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 21:36:21 by lomartin          #+#    #+#             */
/*   Updated: 2026/02/16 15:50:07 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#define _USE_MATH_DEFINES

void	init_viewport(t_viewport *viewport, int fov)
{
	viewport->aspect_ratio = (double)WIN_WIDTH / (double)WIN_HEIGHT;
	viewport->theta = fov * M_PI / 180.0;
	viewport->vp_h = 2 * tan(viewport->theta / 2);
	viewport->vp_w = viewport->aspect_ratio * viewport->vp_h;
	viewport->step_w = viewport->vp_w / WIN_WIDTH;
	viewport->step_h = viewport->vp_h / WIN_HEIGHT;
}

t_pos_xyz	get_ray(int x, int y, t_viewport *viewport)
{
	double		u;
	double		v;

	x = x * viewport->step_w;
	y = y * viewport->step_h;
	u = ((double)x + 0.5) / WIN_WIDTH - 0.5;
	v = 0.5 - ((double)y + 0.5) / WIN_HEIGHT;
	return((t_pos_xyz){u * viewport->vp_w, v * viewport->vp_h, 1});
}

// int	color(t_pos_xyz	ray, t_object *objects)
// {
//
// }

// void	trace_rays(t_world_data *world, t_mlx_data *mlx)
// {
// 	t_pos_xyz	ray;

// 	(void)mlx;
// 	ray = get_ray(0, 0, world->cam.fov);
// 	(void)ray;
// }

void	render_canva(t_pos_xyz start, t_pos_xyz end, t_world_data *world, t_mlx_data *mlx, int color)
{
	t_pos_xyz	pointer;

	pointer.y = start.y;
	while (pointer.y <= end.y)
	{
		pointer.x = start.x;
		while (pointer.x <= end.x)
		{
			my_mlx_pixel_put(mlx, pointer, color_sup(color, get_prev_color(pointer, mlx)));
			get_ray(pointer.x, pointer.y, &world->viewport);
			pointer.x++;
		}
		pointer.y++;
	}
}
