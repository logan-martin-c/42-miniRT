/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 12:58:52 by lomartin          #+#    #+#             */
/*   Updated: 2026/02/21 17:11:48 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	init_mlx(t_mlx_data *mlx)
{
	mlx->mlx = mlx_init();
	if (!mlx->mlx)
		return (1);
	mlx->s_img_data.img = mlx_new_image(mlx->mlx, WIN_WIDTH, WIN_HEIGHT);
	mlx->win = mlx_new_window(mlx->mlx, WIN_WIDTH, WIN_HEIGHT, "miniRT");
	if (!mlx->win || !mlx->s_img_data.img)
		return (1);
	mlx->s_img_data.addr = mlx_get_data_addr(mlx->s_img_data.img,
			&mlx->s_img_data.bits_per_pixel, &mlx->s_img_data.line_length,
			&mlx->s_img_data.endian);
	if (!mlx->s_img_data.addr)
		return (1);
	ft_bzero(mlx->s_img_data.addr, WIN_HEIGHT * WIN_WIDTH
		* mlx->s_img_data.bits_per_pixel / 8);
	return (0);
}

void	init_cam(t_cam_data *cam)
{
	cam->pos.x = CAM_X;
	cam->pos.y = CAM_Y;
	cam->pos.z = CAM_Z;
	cam->angle.x = 0;
	cam->angle.y = 0;
	cam->angle.z = 1;
	cam->fov = CAM_FOV;
	cam->speed = 40;
}

void	init_ambient_light(t_ambient_light_data *ambient_light)
{
	ambient_light->ratio = A_LIGHT_RAT * 255;
	ambient_light->color = get_color_chars(0, A_LIGHT_R, A_LIGHT_G, A_LIGHT_B);
}

void	init(t_global_data *g_data, t_parsing_data *p_data, t_exec_data *e_data,
		char *av_zero)
{
	ft_bzero(g_data, sizeof(t_global_data));
	ft_bzero(p_data, sizeof(t_parsing_data));
	ft_bzero(e_data, sizeof(t_exec_data));
	g_data->prog_name = get_progname(av_zero);
	g_data->e_data = e_data;
	init_cam(&g_data->world.cam);
	init_ambient_light(&g_data->world.ambient_light);
}
