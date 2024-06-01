/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmougel <jmougel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 08:09:57 by yusengok          #+#    #+#             */
/*   Updated: 2024/06/01 17:01:18 by jmougel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_map	data_map;

	if (argc != 2 || ft_strnstr_r(argv[1], ".cub") != 0)
		ft_error_exit("Usage: ./cub3D <path/map_name.cub>", 1);
	if (parsing(argv[1], &data_map) == EXIT_FAILURE)
		return (2);
	/* if (ft_init_mlx(&data) == 1)
		exit(1);
	data.img.img = mlx_new_image(data.mlx_ptr, WIN_W, WIN_H);
	data.img.addr = mlx_get_data_addr(data.img.img, &data.img.bits_per_pxl,
			&data.img.line_len, &data.img.endian);
	mlx_key_hook(data.win_ptr, &handle_keyevents, &data);
	mlx_mouse_hook(data.win_ptr, &handle_mouseevents, &data.map); // For bonus
	mlx_hook(data.win_ptr, DestroyNotify, StructureNotifyMask,
		&handle_closebutton, &data);
	mlx_loop_hook(data.mlx_ptr, &render_image, &data);
	mlx_loop(data.mlx_ptr); */
	free_data_map(&data_map);
	return (0);
}


//SEGFAULT si la map n'a pas de retour a la ligne a la fin