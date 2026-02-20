/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adastugu <adastugu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 15:24:04 by lomartin          #+#    #+#             */
/*   Updated: 2026/02/20 17:24:12 by adastugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	main(int ac, char *av[])
{
	t_global_data	g_data;
	t_parsing_data	p_data;

	printf("%s\n", av[1]);
	init(&g_data, &p_data, av[0]);
	parser(ac, av, &g_data, &p_data);
	// if (DEBUG)
	// 	print_array(&g_data.world);
	if (init_mlx(&g_data.mlx))
	{
		ft_perror("mlx", g_data.prog_name);
		clean_exit(EXIT_FAILURE, &g_data, &p_data);
	}
	init_viewport(&g_data.world.viewport, g_data.world.cam.fov);
	set_hooks(&g_data);
	mlx_do_key_autorepeatoff(g_data.mlx.mlx);
	mlx_loop(g_data.mlx.mlx);
}
