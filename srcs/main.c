/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 08:09:57 by yusengok          #+#    #+#             */
/*   Updated: 2024/05/29 16:31:45 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*== TEST CODE ===============================================================*/

// 111111111111
// 100001111101
// 100000011001
// 111100000001
// 111100000001
// 111100000001
// 111100000001
// 11110000N001
// 111100000001
// 111111111111
/*============================================================================*/

static int	ft_init_mlx(t_cub3d *data)
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
}

int	main(int argc, char **argv)
{
	t_cub3d	data;

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

	data.player.pos_x = 9; //* TEXTURE_SIZE + TEXTURE_SIZE / 2;
	data.player.pos_y = 7; //* TEXTURE_SIZE + TEXTURE_SIZE / 2;
	data.player.dir = N;
	data.player.fov = FOV * M_PI / 180;
	data.player.plane_length = tan(data.player.fov / 2);
/*========================================================================*/

	if (argc != 2 || ft_strnstr_r(argv[1], ".cub") != 0)
		ft_error_exit("Usage: ./cub3D <path/map_name.cub>", 1);
	// map parsing
	if (ft_init_mlx(&data) == 1)
		exit(1);
	data.img.img = mlx_new_image(data.mlx_ptr, WIN_W, WIN_H);
	data.img.addr = mlx_get_data_addr(data.img.img, &data.img.bits_per_pxl,
			&data.img.line_len, &data.img.endian);
	mlx_key_hook(data.win_ptr, &handle_keyevents, &data);
	mlx_mouse_hook(data.win_ptr, &handle_mouseevents, &data.map); // For bonus
	mlx_hook(data.win_ptr, DestroyNotify, StructureNotifyMask,
		&handle_closebutton, &data);
	mlx_loop_hook(data.mlx_ptr, &render_image, &data);
	mlx_loop(data.mlx_ptr);
	return (0);
}
