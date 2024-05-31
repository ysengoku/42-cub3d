/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 13:08:42 by yusengok          #+#    #+#             */
/*   Updated: 2024/05/31 17:22:29 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_tile_color(t_minimap *mmap, int color);
static void	draw_tile(t_cub3d *data, t_minimap *mmap);
static void	draw_player(t_cub3d *data);
static void	draw_player_dir(t_cub3d *data);

void	set_minimap(t_cub3d *data)
{
	int			map_x;
	int			map_y;

	map_y = 0;
	data->mmap.minimap_y = 0;
	while (map_y < data->map.maxh)
	{
		map_x = 0;
		data->mmap.minimap_x = 0;
		while (map_x < data->map.maxw)
		{
			if (data->map.mapdata[map_y][map_x] == '1')
				draw_tile_color(&data->mmap, MMAP_WALL);
			else if (data->map.mapdata[map_y][map_x] == ' ')
				draw_tile_color(&data->mmap, MMAP_SPACE);
			else
				draw_tile(data, &data->mmap);
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

static void	draw_tile(t_cub3d *data, t_minimap *mmap)
{ 
	int	x;
	int	y;
	int	src_x;
	int	src_y;
	int	color;

	y = mmap->minimap_y;
	mmap->floor.img.img = mlx_xpm_file_to_image(data->mlx_ptr, MMAP_F, &mmap->minimap_x, &mmap->minimap_y);
	mmap->floor.img.addr = mlx_get_data_addr(mmap->floor.img.img,
		&mmap->floor.img.bits_per_pxl, &mmap->floor.img.line_len, &mmap->floor.img.endian);
	src_y = 0;
	while (y < mmap->minimap_y + MMAP_SCALE)
	{
		x = mmap->minimap_x;
		src_x = 0;
		while (x < mmap->minimap_x + MMAP_SCALE)
		{
			color = mmap->floor.img.addr[src_y * mmap->minimap_x + src_x];
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

	y = data->player.pos_y * MMAP_SCALE;
	i = 0;
	while (i < MMAP_SCALE)
	{
		j = -1;
		x = data->player.pos_x * MMAP_SCALE;
		while (++j < MMAP_SCALE)
			put_pxl_color(&data->mmap.img, x++, y, MMAP_P);
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
	steps = MMAP_SCALE * 2;
	while (steps > 0)
	{
		put_pxl_color(&data->mmap.img, (int)dir_x, (int)dir_y, MMAP_DIR);
		dir_x += data->player.dir_x;
		dir_y += data->player.dir_y;
		steps--;
	}
}

// static void	set_xpmimg()
// {
	
// }
