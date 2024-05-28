/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 08:30:08 by yusengok          #+#    #+#             */
/*   Updated: 2024/05/28 15:07:09 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void check_wall_hit(t_cub3d *data, t_ray *ray);

int	ft_raycasting(t_cub3d *data)
{
	int		count;
	t_ray	ray;

	count = 0;
	// init ray struct
	while (count < WIN_W)
	{	
		ray.x = data->player.pos_x;
		ray.y = data->player.pos_y;
//	/*=== TO CODE ===*/ 
		check_wall_hit(data, &ray);
//		Calculate wall_height & check which side
//			-----> start point of wall = WIN_H / 2 - wall height / 2
//			-----> end point of wall = WIN_H / 2 + wall height / 2
	/*=== TEST ===========================================================*/
		ray.wall_height = 0;
	/*====================================================================*/
		draw_ceiling(data, count,  WIN_H / 2 - ray.wall_height / 2,
				convert_color(data->ceiling));
//		draw wall (texture)
		draw_floor(data, count, WIN_H / 2 + ray.wall_height / 2,
				convert_color(data->floor));
		count++;
	}
	return (0);
}

static void check_wall_hit(t_cub3d *data, t_ray *ray)
{
	int	test[5][6] = {
		{1,1,1,1,1,1},
		{1,0,0,1,0,1},
		{1,0,1,0,0,1},
		{1,1,0,0,0,1},
		{1,1,1,1,1,1}};
		
	int	hit;

	hit = 0;
	while (!hit)
	{
		if (test[(int)ray->x][(int)ray->y] == 1)
		// if (data->map.mapdata[(int)ray->x][(int)ray->y] == 1)
			hit = 1;
	}
}

    // t_player player;
    
    // player.angle = 270 * 3.14 / 180;
    // player.dir_x = cos(player.angle);
    // player.dir_y = sin(player.angle);
    // printf("%f, %f\n", round(player.dir_x), round(player.dir_y));