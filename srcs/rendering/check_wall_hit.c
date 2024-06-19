/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_wall_hit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 08:07:02 by yusengok          #+#    #+#             */
/*   Updated: 2024/06/19 13:56:28 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_ray_hit(t_cub3d *data, t_ray *ray, int *vertical_side, char c);
static void	next_step(t_ray *ray, int *is_vertical_side);
static int	get_wall_side(t_ray *ray, t_player *player, int is_vertical_side);

void	check_hit(t_cub3d *data, t_ray *ray)
{
	int		vertical_side;

	vertical_side = 0;
	while (!ray->w_hit)
	{
		if (data->map.map[ray->map_y][ray->map_x] == '1')
		{
			ray->w_hit = 1;
			if (vertical_side)
				ray->wall.dist = ray->sidedist.y - ray->delta.y;
			else
				ray->wall.dist = ray->sidedist.x - ray->delta.x;
			if (ray->wall.dist < 0.0001)
				ray->wall.dist = 0.0001;
			ray->wall.side = get_wall_side(ray, &data->player, vertical_side);
			ray->wall.h = (int)(WIN_H / ray->wall.dist);
		}
		if  (data->map.map[ray->map_y][ray->map_x] == 'D' && !ray->close_door_hit)
		{
			ray->close_door_hit = 1;
			if (vertical_side)
				ray->closed_d.dist = ray->sidedist.y - ray->delta.y;
			else
				ray->closed_d.dist = ray->sidedist.x - ray->delta.x;
			if (ray->closed_d.dist < 0.0001)
			ray->closed_d.dist = 0.0001;
			ray->closed_d.h = (int)(WIN_H / ray->closed_d.dist);
			ray->closed_d.side =  get_wall_side(ray, &data->player, vertical_side);
		}
		if  (data->map.map[ray->map_y][ray->map_x] == 'O' && !ray->open_door_hit)
		{
			ray->open_door_hit = 1;
			if (vertical_side)
				ray->open_d.dist = ray->sidedist.y - ray->delta.y;
			else
				ray->open_d.dist = ray->sidedist.x - ray->delta.x;
			if (ray->open_d.dist < 0.0001)
			ray->open_d.dist = 0.0001;
			ray->open_d.h = (int)(WIN_H / ray->open_d.dist);
			ray->open_d.side =  get_wall_side(ray, &data->player, vertical_side);
		}
		next_step(ray, &vertical_side);
	}
}

void	check_door_hit(t_cub3d *data, t_ray *ray, int x, char c)
{
	int		is_vertical_side;

	is_vertical_side = 0;
	while (ray->hit == NOTHING)
		set_ray_hit(data, ray, &is_vertical_side, c);
	if (is_vertical_side)
		ray->wall.dist = ray->sidedist.y - ray->delta.y;
	else
		ray->wall.dist = ray->sidedist.x - ray->delta.x;
	if (ray->wall.dist < 0.0001)
		ray->wall.dist = 0.0001;
	data->wall_zbuffer[x] = ray->wall.dist;
	ray->wall.side = get_wall_side(ray, &data->player, is_vertical_side);
	ray->wall.h = (int)(WIN_H / ray->wall.dist);
}

static void	set_ray_hit(t_cub3d *data, t_ray *ray, int *vertical_side, char c)
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
		next_step(ray, vertical_side);
}

static void	next_step(t_ray *ray, int *is_vertical_side)
{
	if (ray->sidedist.x < ray->sidedist.y)
	{
		ray->sidedist.x += ray->delta.x;
		ray->map_x += ray->step_x;
		*is_vertical_side = 0;
	}
	else
	{
		ray->sidedist.y += ray->delta.y;
		ray->map_y += ray->step_y;
		*is_vertical_side = 1;
	}
}

static int	get_wall_side(t_ray *ray, t_player *player, int is_vertical_side)
{
	if (is_vertical_side == 1)
	{
		if (ray->map_y < player->pos.y)
			return (NO);
		return (SO);
	}
	if (ray->map_x < player->pos.x)
		return (WE);
	return (EA);
}
