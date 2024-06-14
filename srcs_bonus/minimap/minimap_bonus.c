/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmougel <jmougel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 13:08:42 by yusengok          #+#    #+#             */
/*   Updated: 2024/06/14 13:01:55 by jmougel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_mmap_player_dir(t_cub3d *data)
{
	double	dir_x;
	double	dir_y;
	double	p_x;
	double	p_y;

	dir_x = (MMAP_TOTAL_SIZE) * 0.5;
	dir_y = (MMAP_TOTAL_SIZE) * 0.5;
	p_x = (int)data->player.pos_x;
	p_y = (int)data->player.pos_y;
	p_x += 0.5;
	p_y += 0.5;
	while ((int)dir_x > 0 && (int)dir_y > 0
		&& (int)dir_x < MMAP_TOTAL_SIZE && (int)dir_y < MMAP_TOTAL_SIZE)
	{
		p_x += (data->player.dir_x / (MMAP_BORDER + MMAP_SCALE));
		p_y += (data->player.dir_y / (MMAP_BORDER + MMAP_SCALE));
		if (!data->map.map[(int)floor(p_y)]
			|| !data->map.map[(int)floor(p_y)][(int)floor(p_x)]
			|| data->map.map[(int)floor(p_y)][(int)floor(p_x)] == ' '
			|| data->map.map[(int)floor(p_y)][(int)floor(p_x)] == '1')
			break ;
		put_pxl_color(&data->mmap.img, (int)dir_x, (int)dir_y, MMAP_DIR);
		dir_x += data->player.dir_x;
		dir_y += data->player.dir_y;
	}
}

void	draw_ray_mmap(t_cub3d *data, t_ray *ray)
{
	double	dir_x;
	double	dir_y;
	double	p_x;
	double	p_y;

	dir_x = (MMAP_TOTAL_SIZE) * 0.5;
	dir_y = (MMAP_TOTAL_SIZE) * 0.5;
	p_x = (int)data->player.pos_x;
	p_y = (int)data->player.pos_y;
	p_x += 0.5;
	p_y += 0.5;
	while ((int)dir_x > 0 && (int)dir_y > 0
		&& (int)dir_x < MMAP_TOTAL_SIZE && (int)dir_y < MMAP_TOTAL_SIZE)
	{
		p_x += (ray->dir_x / (MMAP_BORDER + MMAP_SCALE));
		p_y += (ray->dir_y / (MMAP_BORDER + MMAP_SCALE));
		if (!data->map.map[(int)floor(p_y)]
			|| !data->map.map[(int)floor(p_y)][(int)floor(p_x)]
			|| data->map.map[(int)floor(p_y)][(int)floor(p_x)] == ' '
			|| data->map.map[(int)floor(p_y)][(int)floor(p_x)] == '1')
			break ;
		put_pxl_color(&data->mmap.img, (int)dir_x, (int)dir_y, MMAP_RAY);
		dir_x += ray->dir_x;
		dir_y += ray->dir_y;
	}
}

void	draw_minimap_zone(t_cub3d *data, int size)
{
	int	x;
	int	y;

	y = 0;
	while (y < size)
	{
		x = 0;
		while (x < size)
			put_pxl_color(&data->mmap.img, x++, y, MMAP_EMPTY);
		y++;
	}
	x = 0;
	y = 0;
	while (x < (size))
		put_pxl_color(&data->mmap.img, x++, y, MMAP_WALL);
	while (y < (size))
		put_pxl_color(&data->mmap.img, x, y++, MMAP_WALL);
	while (x > 0)
		put_pxl_color(&data->mmap.img, x--, y, MMAP_WALL);
	while (y > 0)
		put_pxl_color(&data->mmap.img, x, y--, MMAP_WALL);
}

void	draw_minimap(t_cub3d *data)
{
	int	cam_x;
	int	cam_y;

	cam_x = data->map.pos_x - 4;
	cam_y = data->map.pos_y - 4;
	data->mmap.minimap_x = 1;
	data->mmap.minimap_y = 1;
	while (cam_y < data->map.pos_y + 5)
	{
		while (cam_x < data->map.pos_x + 5)
		{
			if (cam_x < 0 || cam_y < 0)
				draw_scale(data, MMAP_EMPTY, MMAP_SCALE);
			else if (data->map.map[cam_y] && data->map.map[cam_y][cam_x])
			{
				if (data->map.map[cam_y][cam_x] == '1')
					draw_scale(data, MMAP_WALL, MMAP_SCALE);
				else if (data->map.map[cam_y][cam_x] == '0')
					draw_scale(data, MMAP_FLOOR, MMAP_SCALE);
				else if (data->map.map[cam_y][cam_x] == 'P')
					draw_scale(data, MMAP_FLOOR, MMAP_SCALE);
				else if (data->map.map[cam_y][cam_x] == 'O' || data->map.map[cam_y][cam_x] == 'D')
					draw_scale(data, MMAP_DOOR, MMAP_SCALE);
			}
			else
				draw_scale(data, MMAP_EMPTY, MMAP_SCALE);
			cam_x++;
			data->mmap.minimap_x += MMAP_SCALE + MMAP_BORDER;
		}
		data->mmap.minimap_x = 1;
		data->mmap.minimap_y += MMAP_SCALE + MMAP_BORDER;
		cam_x = data->map.pos_x - 4;
		cam_y++;
	}
}

void	draw_mmap_player(t_cub3d *data)
{
	draw_circle(data,
		((MMAP_SCALE * MMAP_SIZE + MMAP_BORDER * MMAP_SIZE) * 0.5),
		((MMAP_SCALE * MMAP_SIZE + MMAP_BORDER * MMAP_SIZE) * 0.5), 5);
}
