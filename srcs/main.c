/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 08:09:57 by yusengok          #+#    #+#             */
/*   Updated: 2024/06/17 11:31:31 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_player(t_player *player)
{
	player->fov = FOV * M_PI / 180;
	player->pos.x = 0;
	player->pos.y = 0;
	player->dir_degree = 0.0;
	player->dir.x = 0;
	player->dir.y = 0;
	player->plane_length = tan(player->fov * 0.5);
	player->plane.x = 0;
	player->plane.y = 0;
}

static void	init_cub3d_data(t_cub3d *data)
{
	int	i;

	i = -1;
	data->mlx_ptr = 0;
	data->win_ptr = 0;
	data->win_half_w = WIN_W * 0.5;
	data->win_half_h = WIN_H * 0.5;
	ft_memset(&data->img, 0, sizeof(data->img));
	init_player(&data->player);
	data->ceiling_color = 0;
	data->floor_color = 0;
	data->keys.key_pressed_left = 0;
	data->keys.key_pressed_right = 0;
	data->keys.key_pressed_w = 0;
	data->keys.key_pressed_s = 0;
	data->keys.key_pressed_a = 0;
	data->keys.key_pressed_d = 0;
	if (BONUS)
	{
		ft_memset(&data->mmap, 0, sizeof(data->mmap));
		ft_memset(&data->mmap.img, 0, sizeof(data->mmap.img));
		data->previous_mouse_x = 0;
		data->keys.key_pressed_x = 0;
	}
}

static int	ft_init_mlx(t_cub3d *data)
{
	data->mlx_ptr = mlx_init();
	if (!(data->mlx_ptr))
	{
		free_data_map(&data->map);
		ft_perror_exit("MLX", 1);
	}
	data->win_ptr = mlx_new_window(data->mlx_ptr, WIN_W, WIN_H, WINNAME);
	if (!(data->win_ptr))
	{
		free(data->mlx_ptr);
		free_data_map(&data->map);
		ft_perror_exit("MLX", 1);
	}
	return (0);
}

static int	create_main_image(t_cub3d *data)
{
	data->img.img = mlx_new_image(data->mlx_ptr, WIN_W, WIN_H);
	if (data->img.img == NULL)
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
		free_data_map(&data->map);
		ft_perror_exit("MLX", 1);
	}
	data->img.addr = mlx_get_data_addr(data->img.img, &data->img.bits_per_pxl,
			&data->img.line_len, &data->img.endian);
	return (0);
}

int	main(int argc, char **argv)
{
	t_cub3d	data;

	if (argc != 2 || ft_strnstr_r(argv[1], ".cub") != 0)
		ft_error_exit("Usage: ./cub3D <path/map_name.cub>", 1);
	if (parsing(argv[1], &data) == EXIT_FAILURE)
		return (2);
	init_cub3d_data(&data);
	set_data(&data, &data.player, &data.map);
	ft_init_mlx(&data);
	create_main_image(&data);
	set_wall_texture(&data, data.wall);
	create_minimap_img(&data, &data.mmap);
	mlx_hook(data.win_ptr, DestroyNotify, StructureNotifyMask,
		closebutton, &data);
	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, keypress, &data);
	mlx_hook(data.win_ptr, KeyRelease, KeyReleaseMask, keyrelease, &data);
	if (BONUS)
		mlx_hook(data.win_ptr, MotionNotify, PointerMotionMask,
			mousemove, &data);
	mlx_loop_hook(data.mlx_ptr, game_loop, &data);
	mlx_loop(data.mlx_ptr);
	return (0);
}
