/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adastugu <adastugu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 15:24:04 by lomartin          #+#    #+#             */
/*   Updated: 2026/03/07 15:04:12 by adastugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	main(int ac, char *av[])
{
	t_global_data	g_data;
	t_parsing_data	p_data;
	t_exec_data		e_data;

	init(&g_data, &p_data, &e_data, av[0]);
	parser(ac, av, &g_data, &p_data);
	if (DEBUG)
		print_array(&g_data.world);
	if (init_mlx(&g_data.mlx))
	{
		ft_perror("mlx", g_data.prog_name);
		clean_exit(EXIT_FAILURE, &g_data, NULL, NULL);
	}
	init_texture(&g_data);
	init_normal(&g_data);
	init_viewport(&g_data.world.viewport, g_data.world.cam.fov);
	if (init_exec(&e_data, &g_data))
	{
		ft_perror("threads", g_data.prog_name);
		clean_exit(EXIT_FAILURE, &g_data, &p_data, &e_data);
	}
	set_hooks(&g_data);
	mlx_do_key_autorepeatoff(g_data.mlx.mlx);
	mlx_loop(g_data.mlx.mlx);
}
