/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 08:30:08 by yusengok          #+#    #+#             */
/*   Updated: 2024/06/17 10:51:23 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_camera(t_cub3d *data);
static void	set_ray(t_cub3d *data, t_ray *ray, int x);
static void	set_sidedist(t_ray *ray, t_player *player);

int	display(t_cub3d *data)
{
	int	x;

	x = 0;
	init_camera(data);
	if (BONUS)
	{
		draw_minimap_zone(data, (data->mmap.totalsize));
		draw_minimap(data);
		animations(data);
	}
	while (x < WIN_W)
	{
		raycasting(data, x, &data->wall[DR + data->animation]);
		x++;
	}
	if (BONUS)
		draw_mmap_player_dir(data);
	return (0);
}

void	raycasting(t_cub3d *data, int x, t_xpm_img *door)
{
	t_ray	ray;

	ft_memset(&ray, 0, sizeof(ray));
	set_ray(data, &ray, x);
	draw_ceiling(data, x, data->win_half_h, data->ceiling_color);
	draw_floor(data, x, data->win_half_h, data->floor_color);
	check_wall_hit(data, &ray);
	draw_wall(data, x, &ray);
	if (BONUS)
	{
		set_ray(data, &ray, x);
		check_door_hit(data, &ray);
		if (ray.hit == DOOR)
			draw_door(data, x, &ray, door);
		if (data->keys.key_pressed_x == 1)
			draw_ray_mmap(data, &ray);
	}
}

static void	init_camera(t_cub3d *data)
{
	double	direction_rad;

	direction_rad = data->player.dir_degree * M_PI / 180;
	// data->player.dir_x = cos(direction_rad);
	// data->player.dir_y = sin(direction_rad);
	data->player.dir.x = cos(direction_rad);
	data->player.dir.y = sin(direction_rad);
	// data->player.plane_x = -data->player.dir_y * data->player.plane_length;
	// data->player.plane_y = data->player.dir_x * data->player.plane_length;
	data->player.plane.x = -data->player.dir.y * data->player.plane_length;
	data->player.plane.y = data->player.dir.x * data->player.plane_length;
}

static void	set_ray(t_cub3d *data, t_ray *ray, int x)
{
	ray->hit = NOTHING;
	ray->w_dist = 0;
	ray->camera_p = 2 * x / (double)WIN_W - 1;
	// ray->dir_x = data->player.dir_x + data->player.plane_x * ray->camera_p;
	// ray->dir_y = data->player.dir_y + data->player.plane_y * ray->camera_p;
	ray->dir.x = data->player.dir.x + data->player.plane.x * ray->camera_p;
	ray->dir.y = data->player.dir.y + data->player.plane.y * ray->camera_p;
	// ray->map_x = (int)data->player.pos_x;
	// ray->map_y = (int)data->player.pos_y;
	ray->map_x = (int)data->player.pos.x;
	ray->map_y = (int)data->player.pos.y;
	// ray->delta_x = fabs(1 / ray->dir_x);
	// ray->delta_y = fabs(1 / ray->dir_y);
	ray->delta_x = fabs(1 / ray->dir.x);
	ray->delta_y = fabs(1 / ray->dir.y);
	set_sidedist(ray, &data->player);
}

static void	set_sidedist(t_ray *ray, t_player *player)
{
	// if (ray->dir_x < 0)
	// {
	// 	ray->step_x = -1;
	// 	ray->sidedist_x = (player->pos_x - ray->map_x) * ray->delta_x;
	// }
	// else
	// {
	// 	ray->step_x = 1;
	// 	ray->sidedist_x = (ray->map_x + 1.0 - player->pos_x) * ray->delta_x;
	// }
	// if (ray->dir_y < 0)
	// {
	// 	ray->step_y = -1;
	// 	ray->sidedist_y = (player->pos_y - ray->map_y) * ray->delta_y;
	// }
	// else
	// {
	// 	ray->step_y = 1;
	// 	ray->sidedist_y = (ray->map_y + 1.0 - player->pos_y) * ray->delta_y;
	// }
	if (ray->dir.x < 0)
	{
		ray->step_x = -1;
		ray->sidedist.x = (player->pos.x - ray->map_x) * ray->delta_x;
	}
	else
	{
		ray->step_x = 1;
		ray->sidedist.x = (ray->map_x + 1.0 - player->pos.x) * ray->delta_x;
	}
	if (ray->dir.y < 0)
	{
		ray->step_y = -1;
		ray->sidedist.y = (player->pos.y - ray->map_y) * ray->delta_y;
	}
	else
	{
		ray->step_y = 1;
		ray->sidedist.y = (ray->map_y + 1.0 - player->pos.y) * ray->delta_y;
	}
}
