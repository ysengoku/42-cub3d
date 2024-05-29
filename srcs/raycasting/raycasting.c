/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 08:30:08 by yusengok          #+#    #+#             */
/*   Updated: 2024/05/29 15:08:33 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_camera(t_cub3d *data);
static void	set_ray(t_cub3d *data, t_ray *ray, int x);
static void check_wall_hit(t_cub3d *data, t_ray *ray);

int	ft_raycasting(t_cub3d *data)
{
	int		x;
	t_ray	ray;

	x = 0;
	init_camera(data);
	while (x < WIN_W)
	{	
		set_ray(data, &ray, x);	
		check_wall_hit(data, &ray);
//		Calculate wall_height & check which side
//			-----> start point of wall = WIN_H / 2 - wall_height / 2
//			-----> end point of wall = WIN_H / 2 + wall_height / 2
	/*=== TEST ===========================================================*/
		ray.wall_height = 0;
	/*====================================================================*/
		draw_ceiling(data, x,  WIN_H / 2 - ray.wall_height / 2,
				convert_color(data->ceiling));
//		draw wall (texture)
		draw_floor(data, x, WIN_H / 2 + ray.wall_height / 2,
				convert_color(data->floor));
		x++;
	}
	return (0);
}

static void	init_camera(t_cub3d *data)
{
	double direction_rad;
	
	direction_rad = data->player.dir * M_PI / 180;
	data->player.dir_x = cos(direction_rad);
	data->player.dir_y = -sin(direction_rad);
	data->player.plane_x = data->player.dir_y * data->player.plane_length;
	data->player.plane_y = data->player.dir_x * data->player.plane_length;
}

static void	set_ray(t_cub3d *data, t_ray *ray, int x)
{
	ray->camera_p = 2 * x / (double)WIN_W - 1;
	ray->dir_x = data->player.dir_x + data->player.plane_x * ray->camera_p;
	ray->dir_y = data->player.dir_y + data->player.plane_y * ray->camera_p;
	ray->map_x = data->player.pos_x;
	ray->map_y = data->player.pos_y;
	ray->sidedist_x = 0;
	ray->sidedist_y = 0;
	// if (ray->dir_x == 0)
	// 	ray->delta_x = -1;
	// else
		ray->delta_x = fabs(1 / ray->dir_x);
	// if (ray->dir_y == 0)
	// 	ray->delta_y = -1;
	// else
		ray->delta_y = fabs(1 / ray->dir_y);
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->sidedist_x = (data->player.pos_x - ray->map_x) * ray->delta_x;
	}
	else
	{
		ray->step_x = 1;
		ray->sidedist_x = (ray->map_x + 1.0 - data->player.pos_x) * ray->delta_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->sidedist_y = (data->player.pos_y - ray->map_y) * ray->delta_y;
	}
	else
	{
		ray->step_y = 1;
		ray->sidedist_y = (ray->map_y + 1.0 - data->player.pos_y) * ray->delta_y;
	}
}

static void check_wall_hit(t_cub3d *data, t_ray *ray)
{
	char	test[5][6] = {
		{"111111"},
		{"100101"},
		{"101001"},
		{"110001"},
		{"111111"}};
		
	int		hit;
	int		side; // 0 = x (north or south), 1 = y (west or east)
	double	distance;

	(void) data;
	hit = 0;
	side = 0;
	while (!hit)
	{
		if (test[ray->map_y][ray->map_x] == '1')
		// if (data->map.mapdata[ray->map_y][ray->map_x] == '1')
			hit = 1;
		else
		{
			if (ray->sidedist_x > ray->sidedist_y)
			{
				ray->sidedist_x += ray->delta_x;
				ray->map_x += ray->step_x;
				side = 0;
			}
			else
			{
				ray->sidedist_y += ray->delta_y;
				ray->map_y += ray->step_y;
				side = 1;
			}
		}
	}
	if (side == 0)
	{
		distance = ray->sidedist_y - ray->delta_y;
		if (ray->map_y < data->player.pos_y)
			ray->wall_side = NO;
		else
			ray->wall_side = SO;
	}
	else
	{
		distance = ray->sidedist_x - ray->delta_x;
		if (ray->map_x < data->player.pos_x)
			ray->wall_side = WE;
		else
			ray->wall_side = EA;
	}
}
