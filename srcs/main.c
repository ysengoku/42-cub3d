/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmougel <jmougel@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 08:09:57 by yusengok          #+#    #+#             */
/*   Updated: 2024/06/03 19:15:27 by jmougel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* static int	ft_init_mlx(t_cub3d *data)
{
	data->mlx_ptr = mlx_init();
	if (!(data->mlx_ptr))
	{
		ft_putendl_fd("MLX: Initialization failed", 2);
		//== For test =============================
		for (int i = 0; data->map.map[i]; i++)
		free(data->map.map[i]);
		free(data->map.map);
		//=========================================
		return (1);
	}
	data->win_ptr = mlx_new_window(data->mlx_ptr, WIN_W, WIN_H, WINNAME);
	if (!(data->win_ptr))
	{
		perror("MLX");
		free(data->mlx_ptr);
		//== For test =============================
		for (int i = 0; data->map.map[i]; i++)
		free(data->map.map[i]);
		free(data->map.map);
		//=========================================
		return (1);
	}

	return (0);
}

static void	init_player(t_player *player)
{
	player->fov = FOV * M_PI / 180;
	player->pos_x = 0; // will be set after parsing
	player->pos_y = 0; // will be set after parsing
	player->initial_dir = 0; // will be set after parsing
	player->dir = 0.0; // will be set after parsing
	player->dir_x = 0; // will be set in init_camera
	player->dir_y = 0; // will be set in init_camera
	player->plane_length = tan(player->fov / 2);
	player->plane_x = 0; // will be set in init_camera
	player->plane_y = 0; // will be set in init_camera
	player->moved = 1; // must be always initialized to 1 to show initial view
}

static void init_cub3d_data(t_cub3d *data)
{
	int	i;

	i = -1;
	//void		*mlx_ptr; ?
	//void		*win_ptr; ?
	ft_bzero(&data->img, sizeof(data->img));
	ft_bzero(&data->map, sizeof(data->map));
	init_player(&data->player);
	data->ceiling_color = 0;
	data->floor_color = 0;
	while (++i < 4)
		ft_bzero(&data->wall[i], sizeof(data->wall[i]));
	ft_bzero(&data->mmap, sizeof(data->mmap));
	ft_bzero(&data->mmap.img, sizeof(data->mmap.img));
	ft_bzero(&data->mmap.floor, sizeof(data->mmap.floor)); // if we use texture for minimap
	ft_bzero(&data->mmap.wall, sizeof(data->mmap.wall)); // if we use texture for minimap
	ft_bzero(&data->mmap.player, sizeof(data->mmap.player)); // if we use texture for minimap
	data->key_pressed_left = 0;
	data->key_pressed_right = 0;
}

static void	set_data(t_cub3d *data, t_player *player, t_map *map)
{
	player->pos_x = map->pos_x;
	player->pos_y = map->pos_y;
	player->initial_dir = N; // from map ---------> Need to change
	player->dir = (double)player->initial_dir;
	data->ceiling_color = convert_color(data->map.c_rgb);
	data->floor_color = convert_color(data->map.f_rgb);
}

//temporary code
static int	set_texture(t_cub3d *data, t_xpm_img wall[4])
{
	int		i;

	wall[NO].path = ft_strdup(data->map.sprite_no);
	wall[SO].path = ft_strdup(data->map.sprite_so);
	wall[WE].path = ft_strdup(data->map.sprite_we);
	wall[EA].path = ft_strdup(data->map.sprite_ea);
	i = -1;
	while (++i < 4)
	{
		wall[i].img = mlx_xpm_file_to_image(data->mlx_ptr, wall[i].path,
			&wall[i].w, &wall[i].h);
		if (wall[i].img == NULL)
		{
			while (i > 0)
				mlx_destroy_image(data->mlx_ptr, wall[i--].img);
			while (i < 4)
				free(wall[i++].path);
			mlx_destroy_image(data->mlx_ptr, data->img.img);
			mlx_destroy_window(data->mlx_ptr, data->win_ptr);
			mlx_destroy_display(data->mlx_ptr);
			free(data->mlx_ptr);
			//== For test =============================
			for (int i = 0; data->map.map[i]; i++)
				free(data->map.map[i]);
			free(data->map.map);
			//=========================================
			return (1);
		}
		wall[i].addr = mlx_get_data_addr(wall[i].img,
			&wall[i].bits_per_pxl, &wall[i].line_len,
			&wall[i].endian);
	}
	return (0);
} */

int	main(int argc, char **argv)
{
	t_cub3d	data;

//=== TEST ===============================================================
	data.colors[0] = 9852907;
	data.colors[1] = 16775920;
	data.colors[2] = 11393254;
	data.colors[3] = 9419927;
//========================================================================
	if (argc != 2 || ft_strnstr_r(argv[1], ".cub") != 0)
		ft_error_exit("Usage: ./cub3D <path/map_name.cub>", 1);
	if (parsing(argv[1], &data.map) == EXIT_FAILURE)
		return (2);
	/*init_cub3d_data(&data);
	set_data(&data, &data.player, &data.map);
	if (ft_init_mlx(&data) == 1)
		return(1);
	data.img.img = mlx_new_image(data.mlx_ptr, WIN_W, WIN_H);
	if (data.img.img == NULL)
	{
		mlx_destroy_window(data.mlx_ptr, data.win_ptr);
		mlx_destroy_display(data.mlx_ptr);
		free(data.mlx_ptr);
		//== For test =============================
		for (int i = 0; data.map.map[i]; i++)
			free(data.map.map[i]);
		free(data.map.map);
		//=========================================
		return (1);
	}
	data.img.addr = mlx_get_data_addr(data.img.img, &data.img.bits_per_pxl,
			&data.img.line_len, &data.img.endian);
	if (set_texture(&data, data.wall) == 1)
		return (1);
	if (BONUS)
	{
		data.mmap.img.img = mlx_new_image(data.mlx_ptr,
				(data.map.map_len_x - 1) * MMAP_SCALE, data.map.map_len_y * MMAP_SCALE);
		// NULL check
		data.mmap.img.addr = mlx_get_data_addr(data.mmap.img.img,
			&data.mmap.img.bits_per_pxl, &data.mmap.img.line_len,
			&data.mmap.img.endian);
	}
	//=== TEST ===============================================================
	if (BONUS)
	{
		data.mmap.floor.img = mlx_xpm_file_to_image(data.mlx_ptr, MMAP_F,
				&data.mmap.floor.w, &data.mmap.floor.h);
		data.mmap.floor.addr = mlx_get_data_addr(data.mmap.floor.img,
				&data.mmap.floor.bits_per_pxl, &data.mmap.floor.line_len,
				&data.mmap.floor.endian);
		data.mmap.player.img = mlx_xpm_file_to_image(data.mlx_ptr, MMAP_PL,
				&data.mmap.player.w, &data.mmap.player.h);
		data.mmap.player.addr = mlx_get_data_addr(data.mmap.player.img,
				&data.mmap.player.bits_per_pxl, &data.mmap.player.line_len,
				&data.mmap.player.endian);
		data.mmap.wall.img = mlx_xpm_file_to_image(data.mlx_ptr, MMAP_WL,
				&data.mmap.wall.w, &data.mmap.wall.h);
		data.mmap.wall.addr = mlx_get_data_addr(data.mmap.wall.img,
				&data.mmap.wall.bits_per_pxl, &data.mmap.wall.line_len,
				&data.mmap.wall.endian);
	}
	//========================================================================
	mlx_hook(data.win_ptr, DestroyNotify, StructureNotifyMask, handle_closebutton, &data);
	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, handle_keypress, &data);
	mlx_hook(data.win_ptr, KeyRelease, KeyReleaseMask, handle_keyrelease, &data);
	// mlx_mouse_hook(data.win_ptr, &handle_mouseevents, &data); // ---> Doesn't need ??
	mlx_loop_hook(data.mlx_ptr, game_loop, &data);
	mlx_loop(data.mlx_ptr); */
	return (0);
}


//SEGFAULT si la map n'a pas de retour a la ligne a la fin