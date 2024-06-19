/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_collision.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 08:07:02 by yusengok          #+#    #+#             */
/*   Updated: 2024/06/19 16:14:57 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_ray_hit(t_cub3d *data, t_ray *ray, int *vertical_side, char c);
static void	next_step(t_ray *ray, int *is_y_axis);
static void	set_collision_data(t_cub3d *data, t_ray *ray, t_hit *sprite, \
int is_y_axis);

void	check_hit(t_cub3d *data, t_ray *ray)
{
	int		is_y_axis;

	is_y_axis = 0;
	while (!ray->w_hit)
	{
		if (data->map.map[ray->map_y][ray->map_x] == '1')
		{
			ray->w_hit = 1;
			set_collision_data(data, ray, &ray->wall, is_y_axis);
		}
		if (BONUS)
		{
			if (data->map.map[ray->map_y][ray->map_x] == 'D' && !ray->dr_c_hit)
			{
				ray->dr_c_hit = 1;
				set_collision_data(data, ray, &ray->closed_d, is_y_axis);
			}
			if (data->map.map[ray->map_y][ray->map_x] == 'O' && !ray->dr_o_hit)
			{
				ray->dr_o_hit = 1;
				set_collision_data(data, ray, &ray->open_d, is_y_axis);
			}
		}
		next_step(ray, &is_y_axis);
	}
}

void	check_door_hit(t_cub3d *data, t_ray *ray, int x, char c)
{
	int		is_y_axis;

	is_y_axis = 0;
	while (ray->hit == NOTHING)
		set_ray_hit(data, ray, &is_y_axis, c);
	if (is_y_axis)
		ray->wall.dist = ray->sidedist.y - ray->delta.y;
	else
		ray->wall.dist = ray->sidedist.x - ray->delta.x;
	if (ray->wall.dist < 0.0001)
		ray->wall.dist = 0.0001;
	data->wall_zbuffer[x] = ray->wall.dist;
	if (is_y_axis && ray->map_y < data->player.pos.y)
		ray->wall.side = SO;
	else if (is_y_axis && ray->map_y > data->player.pos.y)
		ray->wall.side = NO;
	else if (!is_y_axis && ray->map_x < data->player.pos.x)
		ray->wall.side = EA;
	else
		ray->wall.side = WE;
	ray->wall.h = (int)(WIN_H / ray->wall.dist);
}

static void	set_ray_hit(t_cub3d *data, t_ray *ray, int *is_y_axis, char c)
{
	if (data->map.map[ray->map_y][ray->map_x] == '1')
		ray->hit = WALL;
	else if (data->map.map[ray->map_y][ray->map_x] == c)
	{
		if (c == 'D')
			ray->hit = DOOR_CLOSE;
		else if (c == 'O')
			ray->hit = DOOR_OPEN;
	}
	else if (c == 'A' && (data->map.map[ray->map_y][ray->map_x] == 'd'
		|| data->map.map[ray->map_y][ray->map_x] == 'o'))
		ray->hit = DOOR_ANIM;
	else
		next_step(ray, is_y_axis);
}

static void	next_step(t_ray *ray, int *is_y_axis)
{
	if (ray->sidedist.x < ray->sidedist.y)
	{
		ray->sidedist.x += ray->delta.x;
		ray->map_x += ray->step_x;
		*is_y_axis = 0;
	}
	else
	{
		ray->sidedist.y += ray->delta.y;
		ray->map_y += ray->step_y;
		*is_y_axis = 1;
	}
}

static void	set_collision_data(t_cub3d *data, t_ray *ray, t_hit *sprite, \
int is_y_axis)
{
	if (is_y_axis)
		sprite->dist = ray->sidedist.y - ray->delta.y;
	else
		sprite->dist = ray->sidedist.x - ray->delta.x;
	if (sprite->dist < 0.0001)
		sprite->dist = 0.0001;
	if (is_y_axis && ray->map_y < data->player.pos.y)
		sprite->side = SO;
	else if (is_y_axis && ray->map_y > data->player.pos.y)
		sprite->side = NO;
	else if (!is_y_axis && ray->map_x < data->player.pos.x)
		sprite->side = EA;
	else
		sprite->side = WE;
	sprite->h = (int)(WIN_H / sprite->dist);
}