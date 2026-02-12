/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 12:58:52 by lomartin          #+#    #+#             */
/*   Updated: 2026/02/11 16:38:01 by lomartin         ###   ########.fr       */
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
