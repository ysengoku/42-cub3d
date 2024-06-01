/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmougel <jmougel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 08:09:57 by yusengok          #+#    #+#             */
/*   Updated: 2024/06/01 17:27:37 by jmougel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*== TEST CODE ===============================================================*/

// 111111
// 100101
// 101001
// 1100N1
// 111111

// int	test[5][6] =
// {
// 	{1,1,1,1,1,1},
// 	{1,0,0,1,0,1},
// 	{1,0,1,0,0,1},
// 	{1,1,0,0,0,1},
// 	{1,1,1,1,1,1}
// };
/*============================================================================*/

/* static int	ft_init_mlx(t_cub3d *data)
{
	data->mlx_ptr = mlx_init();
	if (!(data->mlx_ptr))
	{
		ft_putendl_fd("MLX: Initialization failed", 2);
		return (1);
	}
	data->win_ptr = mlx_new_window(data->mlx_ptr, WIN_W, WIN_H, WINNAME);
	if (!(data->win_ptr))
	{
		perror("MLX");
		mlx_destroy_display(data->mlx_ptr);
		return (1);
	}
	return (0);
} */

int	main(int argc, char **argv)
{
	t_cub3d	data;
	t_map	data_map;

/*=== TEST ===============================================================*/
	data.ceiling.r = 169;
	data.ceiling.g = 169;
	data.ceiling.b = 169;
	data.floor.r = 52;
	data.floor.g = 52;
	data.floor.b = 52;
	data.colors[0].r = 135;
	data.colors[0].g = 206;
	data.colors[0].b = 235;
	data.colors[1].r = 255;
	data.colors[1].g = 127;
	data.colors[1].b = 80;
	data.colors[2].r = 50;
	data.colors[2].g = 205;
	data.colors[2].b = 50;
	data.colors[3].r = 221;
	data.colors[3].g = 160;
	data.colors[3].b = 221;

	data.player.pos_x = 4; //* TEXTURE_SIZE + TEXTURE_SIZE / 2;
	data.player.pos_y = 3; //* TEXTURE_SIZE + TEXTURE_SIZE / 2;
	data.player.dir = 90;
	data.player.fov = FOV * M_PI / 180;
	data.player.plane_length = tan(data.player.fov / 2);
/*========================================================================*/
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