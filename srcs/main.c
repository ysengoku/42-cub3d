/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmougel <jmougel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 08:09:57 by yusengok          #+#    #+#             */
/*   Updated: 2024/06/07 20:04:54 by jmougel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* static void	init_player(t_player *player)
{
	player->fov = FOV * M_PI / 180;
	player->pos_x = 0;
	player->pos_y = 0;
	player->dir = 0.0;
	player->dir_x = 0;
	player->dir_y = 0;
	player->plane_length = tan(player->fov / 2);
	player->plane_x = 0;
	player->plane_y = 0;
	player->moved = 1;
}

static void	init_cub3d_data(t_cub3d *data)
{
	int	i;

	i = -1;
	data->mlx_ptr = 0;
	data->win_ptr = 0;
	ft_memset(&data->img, 0, sizeof(data->img));
	init_player(&data->player);
	data->ceiling_color = 0;
	data->floor_color = 0;
	ft_memset(&data->mmap, 0, sizeof(data->mmap));
	ft_memset(&data->mmap.img, 0, sizeof(data->mmap.img));
	//------ if we use texture for minimap ----------------------
	ft_memset(&data->mmap.floor, 0, sizeof(data->mmap.floor));
	ft_memset(&data->mmap.wall, 0, sizeof(data->mmap.wall));
	ft_memset(&data->mmap.player, 0, sizeof(data->mmap.player));
	//-----------------------------------------------------------
	data->key_pressed_left = 0;
	data->key_pressed_right = 0;
	data->key_pressed_w = 0;
	data->key_pressed_s = 0;
	data->key_pressed_a = 0;
	data->key_pressed_d = 0;
}

static int	ft_init_mlx(t_cub3d *data)
{
	data->mlx_ptr = mlx_init();
	if (!(data->mlx_ptr))
	{
		ft_putendl_fd("MLX: Initialization failed", 2);
		free_data_map(&data->map);
		return (1);
	}
	data->win_ptr = mlx_new_window(data->mlx_ptr, WIN_W, WIN_H, WINNAME);
	if (!(data->win_ptr))
	{
		perror("MLX");
		free(data->mlx_ptr);
		free_data_map(&data->map);
		return (1);
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
		return (1);
	}
	data->img.addr = mlx_get_data_addr(data->img.img, &data->img.bits_per_pxl,
			&data->img.line_len, &data->img.endian);
	return (0);
} */

void	init_data(t_cub3d *data)
{
	int	i;

	i = 0;
	ft_memset(&data->mmap, 0, sizeof(t_minimap));
	ft_memset(&data->img, 0, sizeof(t_imgdata));
	ft_memset(&data->player, 0, sizeof(t_player));
	while (i < 4)
		ft_memset(&data->wall[i++], 0, sizeof(t_xpm_img));
}

void	init_win(t_cub3d *data)
{
	data->mlx_ptr = mlx_init();
	mlx_get_screen_size(data->mlx_ptr, &data->max_x, &data->max_y);
	data->win_ptr = mlx_new_window(data->mlx_ptr, data->max_x, data->max_y, WINNAME);
}

void	draw_minimap_zone(t_cub3d *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while(j < ((MMAP_SCALE + MMAP_BORDER) * MMAP_SIZE))
	{
		while(i < ((MMAP_SCALE + MMAP_BORDER) * MMAP_SIZE))
		{
			put_pxl_color(&data->mmap.img, i, j, (int)0xB0BEC5);
			i++;
		}
		i = 0;
		j++;
	}
	i = 0;
	j = 0;
	while (i < ((MMAP_SCALE + MMAP_BORDER) * MMAP_SIZE) - 1)
	{
		put_pxl_color(&data->mmap.img, i, j, MMAP_WALL);
		i++;
	}
	while (j < ((MMAP_SCALE + MMAP_BORDER) * MMAP_SIZE) - 1)
	{
		put_pxl_color(&data->mmap.img, i, j, MMAP_WALL);
		j++;
	}
	while (i > 0)
	{
		put_pxl_color(&data->mmap.img, i, j, MMAP_WALL);
		i--;
	}
	while (j > 0)
	{
		put_pxl_color(&data->mmap.img, i, j, MMAP_WALL);
		j--;
	}
}

void	draw_cube(t_cub3d *data, char c, int size)
{
	int	i;
	int	j;

	i = data->mmap.minimap_x;
	j = data->mmap.minimap_y;
	while(j < (size + data->mmap.minimap_y))
	{
		while(i < (size + data->mmap.minimap_x))
		{
			if (c == '1')
			{
				put_pxl_color(&data->mmap.img, i, j, MMAP_WALL);
			}
			else if (c == '0' || c == 'P')
			{
				put_pxl_color(&data->mmap.img, i, j, MMAP_FLOOR);
			}
			else
			{
				put_pxl_color(&data->mmap.img, i, j, MMAP_SPACE);
			}
			i++;
		}
		i = data->mmap.minimap_x;
		j++;
	}
}

void	draw_minimap(t_cub3d *data)
{
	int	cam_x;
	int	cam_y;

	cam_y = data->map.pos_y - 5;
	cam_x = data->map.pos_x - 5;
	data->mmap.minimap_x = 0;
	data->mmap.minimap_y = 0;
	while(cam_y < (data->map.pos_y + 6))
	{
		while(cam_x < (data->map.pos_x + 6))
		{
			if (cam_y < 0 || cam_x < 0)
			{
				draw_cube(data, 0, MMAP_SCALE);
			}
			else if (cam_y < data->map.map_len_y && cam_x < data->map.map_len_x && data->map.map[cam_y])
			{
				draw_cube(data, data->map.map[cam_y][cam_x], MMAP_SCALE);
			}
			else
			{
				draw_cube(data, 0, MMAP_SCALE);
			}
			data->mmap.minimap_x += MMAP_SCALE + 1;
			cam_x++;
		}
		cam_x = data->map.pos_x - 5;
		data->mmap.minimap_x = 0;
		data->mmap.minimap_y += MMAP_SCALE + 1;
		cam_y++;
	}
	data->mmap.minimap_x = 0;
	data->mmap.minimap_y = 0;
}

void	draw_player(t_cub3d *data)
{
	int	i;
	int	j;

	i = data->mmap.p_x;
	j = data->mmap.p_y;

	while(j < (MMAP_P_SCALE + data->mmap.p_y))
	{
		while(i < (MMAP_P_SCALE  + data->mmap.p_x))
		{
			put_pxl_color(&data->mmap.img, i, j, MMAP_P);
			i++;
		}
		i = data->mmap.p_x;
		j++;
	}
}

typedef struct	s_mat4 {
	float		mat[16];
}	t_mat4;

void	make_minimap(t_cub3d *data)
{
	data->mmap.img.img = mlx_new_image(data->mlx_ptr, ((MMAP_SCALE + MMAP_BORDER) * MMAP_SIZE), ((MMAP_SCALE + MMAP_BORDER) * MMAP_SIZE));
	data->mmap.img.addr = mlx_get_data_addr(data->mmap.img.img, &data->mmap.img.bits_per_pxl, &data->mmap.img.line_len, &data->mmap.img.endian);
	draw_minimap_zone(data);
	draw_minimap(data);
	draw_player(data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->mmap.img.img, 0, 0);
}

void	init_minimap(t_cub3d *data)
{
	data->mmap.p_x = (MMAP_SCALE * MMAP_SIZE) / 2;
	data->mmap.p_y = (MMAP_SCALE * MMAP_SIZE) / 2;
	make_minimap(data);
}

int	key_event(int keycode, void *param)
{
	t_cub3d *data;
	int		player_x;
	int		player_y;

	data = param;
	player_x = data->map.pos_x;
	player_y = data->map.pos_y;
	if (keycode == XK_Escape)
		exit(EXIT_SUCCESS);
	else if (keycode == XK_w)
	{
		if (data->map.map[player_y - 1][player_x] != '1')
		{
			//data->mmap.p_y -= 1;
			data->map.map[player_y][player_x] = '0';
			data->map.map[player_y - 1][player_x] = 'P';
			data->map.pos_y -= 1;
			make_minimap(data);
		}
	}
	else if (keycode == XK_s)
	{
		if (data->map.map[player_y + 1][player_x] != '1')
		{
			//data->mmap.p_y += 1;
			data->map.map[player_y][player_x] = '0';
			data->map.map[player_y + 1][player_x] = 'P';
			data->map.pos_y += 1;
			make_minimap(data);
		}
	}
	else if (keycode == XK_a)
	{
		if (data->map.map[player_y][player_x - 1] != '1')
		{
			//data->mmap.p_x -= 1;
			data->map.map[player_y][player_x] = '0';
			data->map.map[player_y][player_x - 1] = 'P';
			data->map.pos_x -= 1;
			make_minimap(data);
		}
	}
	else if (keycode == XK_d)
	{
		if (data->map.map[player_y][player_x + 1] != '1')
		{
			//data->mmap.p_x += 1;
			data->map.map[player_y][player_x] = '0';
			data->map.map[player_y][player_x + 1] = 'P';
			data->map.pos_x += 1;
			make_minimap(data);
		}
	}
	else
		printf("%d\n", keycode);
	return (EXIT_SUCCESS);
}

/* void	forward(t_cub3d *data)
{
	int		player_x;
	int		player_y;

	player_x = data->map.pos_x;
	player_y = data->map.pos_y;
	data->mmap.p_y -= 0.1;
	data->map.map[player_y][player_x] = '0';
	data->map.map[player_y][player_x + 1] = 'P';
	data->map.pos_y -= 0.1;
	make_minimap(data);
}

void	left(t_cub3d *data)
{
	int		player_x;
	int		player_y;

	player_x = data->map.pos_x;
	player_y = data->map.pos_y;
	data->mmap.p_x -= 0.1;
	data->map.map[player_y][player_x] = '0';
	data->map.map[player_y][player_x - 1] = 'P';
	data->map.pos_x -= 0.1;
	make_minimap(data);
}

void	backward(t_cub3d *data)
{
	int		player_x;
	int		player_y;

	player_x = data->map.pos_x;
	player_y = data->map.pos_y;
	data->mmap.p_y += 0.1;
	data->map.map[player_y][player_x] = '0';
	data->map.map[player_y][player_x + 1] = 'P';
	data->map.pos_y += 0.1;
	make_minimap(data);
}

void	right(t_cub3d *data)
{
	int		player_x;
	int		player_y;

	player_x = data->map.pos_x;
	player_y = data->map.pos_y;
	data->mmap.p_x += 0.1;
	data->map.map[player_y][player_x] = '0';
	data->map.map[player_y][player_x + 1] = 'P';
	data->map.pos_x += 0.1;
	make_minimap(data);
}

int	main_loop(t_cub3d *data)
{
	int		player_x;
	int		player_y;

	player_x = data->map.pos_x;
	player_y = data->map.pos_y;
	if (data->key_pressed_w)
		forward(data);
	if (data->key_pressed_a)
		left(data);
	if (data->key_pressed_s)
		backward(data);
	if (data->key_pressed_d)
		right(data);
	return (EXIT_SUCCESS);
} */

int	main(int argc, char **argv)
{
	t_cub3d	data;

	if (argc != 2 || ft_strnstr_r(argv[1], ".cub") != 0)
		ft_error_exit("Usage: ./cub3D <path/map_name.cub>", 1);
	if (parsing(argv[1], &data) == EXIT_FAILURE)
		return (2);
	/* init_cub3d_data(&data);
	set_data(&data, &data.player, &data.map);
	if (ft_init_mlx(&data) == 1)
		return (1);
	if (create_main_image(&data) == 1)
		return (1);
	if (set_wall_texture(&data, data.wall) == 1)
		return (1);
	if (create_minimap_img(&data, &data.mmap) == 1)
		return (1);
	mlx_hook(data.win_ptr, DestroyNotify, StructureNotifyMask,
		handle_closebutton, &data);
	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, handle_keypress, &data);
	mlx_hook(data.win_ptr, KeyRelease, KeyReleaseMask,
		handle_keyrelease, &data);
	mlx_mouse_hook(data.win_ptr, &handle_mouseevents, &data); // ---> Doesn't need ??
	mlx_loop_hook(data.mlx_ptr, game_loop, &data);
	mlx_loop(data.mlx_ptr);*/
	init_data(&data);
	init_win(&data);
	mlx_key_hook(data.win_ptr, key_event, &data);
	init_minimap(&data);
	//mlx_hook(data.win_ptr, KeyPress, KeyPressMask, handle_keypress, &data);
	//mlx_hook(data.win_ptr, KeyRelease, KeyReleaseMask, handle_keyrelease, &data);
	//mlx_loop_hook(data.mlx_ptr, main_loop, &data);
	mlx_loop(data.mlx_ptr);
	return (0);
}
