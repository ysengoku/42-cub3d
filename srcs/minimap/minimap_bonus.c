/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 13:08:42 by yusengok          #+#    #+#             */
/*   Updated: 2024/06/03 14:22:35 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_tile_color(t_minimap *mmap, int color);
static void	draw_tile(t_cub3d *data, t_minimap *mmap, t_xpm_img *texture);
static void	draw_player(t_cub3d *data);
static void	draw_player_dir(t_cub3d *data);

void	set_minimap(t_cub3d *data)
{
	int			map_x;
	int			map_y;

	data->mmap.img.img = mlx_new_image(data->mlx_ptr,
		(data->map.map_len_x - 1) * MMAP_SCALE, data->map.map_len_y * MMAP_SCALE);
	// NULL check
	data->mmap.img.addr = mlx_get_data_addr(data->mmap.img.img,
		&data->mmap.img.bits_per_pxl, &data->mmap.img.line_len,
		&data->mmap.img.endian);
	/*===== If minimap with texture ==========================================*/
	data->mmap.floor.img = mlx_xpm_file_to_image(data->mlx_ptr, MMAP_F,
			&data->mmap.floor.w, &data->mmap.floor.h);
	data->mmap.floor.addr = mlx_get_data_addr(data->mmap.floor.img,
			&data->mmap.floor.bits_per_pxl, &data->mmap.floor.line_len,
			&data->mmap.floor.endian);
	data->mmap.player.img = mlx_xpm_file_to_image(data->mlx_ptr, MMAP_PL,
			&data->mmap.player.w, &data->mmap.player.h);
	data->mmap.player.addr = mlx_get_data_addr(data->mmap.player.img,
			&data->mmap.player.bits_per_pxl, &data->mmap.player.line_len,
			&data->mmap.player.endian);
	data->mmap.wall.img = mlx_xpm_file_to_image(data->mlx_ptr, MMAP_WL,
			&data->mmap.wall.w, &data->mmap.wall.h);
	data->mmap.wall.addr = mlx_get_data_addr(data->mmap.wall.img,
			&data->mmap.wall.bits_per_pxl, &data->mmap.wall.line_len,
			&data->mmap.wall.endian);
	/*========================================================================*/
	map_y = 0;
	data->mmap.minimap_y = 0;
	while (map_y < data->map.map_len_y)
	{
		map_x = 0;
		data->mmap.minimap_x = 0;
		while (data->map.map[map_y][map_x])
		{
			if (data->map.map[map_y][map_x] == '1')
				draw_tile(data, &data->mmap, &data->mmap.wall);
			//	draw_tile_color(&data->mmap, MMAP_WALL);
			else if (data->map.map[map_y][map_x] == ' ')
				draw_tile_color(&data->mmap, MMAP_SPACE);
			else
				draw_tile(data, &data->mmap, &data->mmap.floor);
			//	draw_tile_color(&data->mmap, MMAP_SPACE);
			map_x++;
		}
		while (map_x < data->map.map_len_x - 1)
		{
			draw_tile_color(&data->mmap, MMAP_SPACE);
			map_x++;
		}
		map_y++;
		data->mmap.minimap_y += MMAP_SCALE;
	}
	draw_player(data);
	draw_player_dir(data);
}

static void	draw_tile_color(t_minimap *mmap, int color)
{
	int	x;
	int	y;

	y = mmap->minimap_y;
	while (y < mmap->minimap_y + MMAP_SCALE)
	{
		x = mmap->minimap_x;
		while (x < mmap->minimap_x + MMAP_SCALE)
			put_pxl_color(&mmap->img, x++, y, color);
		y++;
	}
	mmap->minimap_x += MMAP_SCALE;
}

static void	draw_tile(t_cub3d *data, t_minimap *mmap, t_xpm_img *texture)
{ 
	int	x;
	int	y;
	int	src_x;
	int	src_y;
	int	color;

	(void) data;
	y = mmap->minimap_y;
	src_y = 0;
	while (y < mmap->minimap_y + MMAP_SCALE)
	{
		x = mmap->minimap_x;
		src_x = 0;
		while (x < mmap->minimap_x + MMAP_SCALE)
		{
			color = *(int *)(texture->addr + (src_y * texture->line_len
				+ src_x * (texture->bits_per_pxl / 8)));
			put_pxl_color(&mmap->img, x++, y, color);
			src_x++;
		}
		y++;
		src_y++;
	}
	mmap->minimap_x += MMAP_SCALE;
}


static void	draw_player(t_cub3d *data)
{
	int	x;
	int	y;
	int	i;
	int	j;
	int	color;

	y = data->player.pos_y * MMAP_SCALE;
	i = 0;
	while (i < MMAP_SCALE)
	{
		j = -1;
		x = data->player.pos_x * MMAP_SCALE;
		while (++j < MMAP_SCALE)
		{
			color = *(int *)(data->mmap.player.addr
				+ (i * data->mmap.player.line_len
				+ j * (data->mmap.player.bits_per_pxl / 8)));
			put_pxl_color(&data->mmap.img, x++, y, color);
//			put_pxl_color(&data->mmap.img, x++, y, MMAP_P);
		}
		i++;
		y++;
	}
}

static void	draw_player_dir(t_cub3d *data)
{
	double	dir_x;
	double	dir_y;
	int		steps;

	dir_x = (double)data->player.pos_x * MMAP_SCALE + MMAP_SCALE / 2 - 1;
	dir_y = (double)data->player.pos_y * MMAP_SCALE + MMAP_SCALE / 2 - 1;
	steps = (int)MMAP_SCALE * 1.5;
	while (steps > 0)
	{
		put_pxl_color(&data->mmap.img, (int)dir_x, (int)dir_y, MMAP_DIR);
		dir_x += data->player.dir_x;
		dir_y += data->player.dir_y;
		steps--;
	}
}
