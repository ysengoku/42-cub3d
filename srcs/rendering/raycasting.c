/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 10:25:16 by yusengok          #+#    #+#             */
/*   Updated: 2024/06/19 13:41:08 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_ray(t_cub3d *data, t_ray *ray, int x);
static void	reset_ray(t_cub3d *data, t_ray *ray);
static void	set_sidedist(t_ray *ray, t_player *player);

void	raycasting(t_cub3d *data, int x, t_xpm_img *door)
{
	t_ray	ray;

	ft_memset(&ray, 0, sizeof(ray));
	set_ray(data, &ray, x);
	draw_ceiling(data, x, data->win_half_h, data->ceiling_color);
	draw_floor(data, x, data->win_half_h, data->floor_color);
	check_hit(data, &ray);
	draw_wall(data, x, &ray);
	if (BONUS)
	{
		if (ray.close_door_hit)
			draw_door(data, x, &ray, &ray.closed_d);
		if (ray.open_door_hit)
			draw_door(data, x, &ray, &ray.open_d);
		reset_ray(data, &ray);
		check_door_hit(data, &ray, x, 'A');
		if (ray.hit == DOOR_ANIM)
			draw_anim_door(data, x, &ray, door);
		if (data->keys.key_pressed_x == 1)
			draw_ray_mmap(data, &ray);
	}
}

static void	set_ray(t_cub3d *data, t_ray *ray, int x)
{
	ray->closed_d.tex = DR_C;
	ray->open_d.tex = DR_O;
	ray->camera_p = 2 * x / (double)WIN_W - 1;
	ray->dir.x = data->player.dir.x + data->player.plane.x * ray->camera_p;
	ray->dir.y = data->player.dir.y + data->player.plane.y * ray->camera_p;
	ray->map_x = (int)data->player.pos.x;
	ray->map_y = (int)data->player.pos.y;
	ray->delta.x = fabs(1 / ray->dir.x);
	ray->delta.y = fabs(1 / ray->dir.y);
	set_sidedist(ray, &data->player);
}

static void	reset_ray(t_cub3d *data, t_ray *ray)
{
	ray->hit = NOTHING;
	ray->wall.dist = 0;
	ray->map_x = (int)data->player.pos.x;
	ray->map_y = (int)data->player.pos.y;
	set_sidedist(ray, &data->player);
}

static void	set_sidedist(t_ray *ray, t_player *player)
{
	if (ray->dir.x < 0)
	{
		ray->step_x = -1;
		ray->sidedist.x = (player->pos.x - ray->map_x) * ray->delta.x;
	}
	else
	{
		ray->step_x = 1;
		ray->sidedist.x = (ray->map_x + 1.0 - player->pos.x) * ray->delta.x;
	}
	if (ray->dir.y < 0)
	{
		ray->step_y = -1;
		ray->sidedist.y = (player->pos.y - ray->map_y) * ray->delta.y;
	}
	else
	{
		ray->step_y = 1;
		ray->sidedist.y = (ray->map_y + 1.0 - player->pos.y) * ray->delta.y;
	}
}
