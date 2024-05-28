/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 08:30:08 by yusengok          #+#    #+#             */
/*   Updated: 2024/05/28 11:06:29 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_raycasting(t_cub3d *data)
{
	int		count;
	// t_ray	ray;

	count = 0;
	// init ray struct
	while (count < WIN_W)
	{
	/*=== TEST ===========================================================*/
		draw_ceiling(data, count, WIN_H / 2, convert_color(data->ceiling));
		draw_floor(data, count, WIN_H / 2, convert_color(data->floor));
	/*====================================================================*/
	
//	/*=== TO CODE ===*/ 
// 		Check horizontal intersection & calculate the distance from Player's position to the wall
//		Check vertical intersection & calculate the distance from Player's position to the wall
// 		Get the smallest distance
//		Calculate wall_height & check which side
//			-----> start point of wall = WIN_H / 2 - wall height / 2
//			-----> end point of wall = WIN_H / 2 + wall height / 2
// 		draw_ceiling(data, x,  WIN_H / 2 - wall_height / 2, convert_color(data->ceiling));
//		draw wall (texture)
//		draw_floor(data, x, WIN_H / 2 + wall_height / 2, convert_color(data->floor));
// 		}
//		ray_angle += FOV / WIN_W
		count++;
	}
	return (0);
}

// Check horizontal intersection & calculate the distance from Player's position to the wall
// int	hit;
// 
// hit = 0;
// ray.inc_x = ?
// ray.inc_y = TEXTURE_SIZE;
// --- Check horizontal intersection ---
// Get the first ray position
// while (!hit)
// {
//		if (data->map->data[(int)ray.x][(int)ray.y] == 1)
// 			hit = 1;
// 		else
// 		{
//			ray.x += ray.inc_x;
// 			ray.y += ray.inc_y
// 		}
// }
// --- Calculate the distance --- Pythagoras’s theorem
// ray.x_distance = sqrt(pow(ray.x - data.player.pos_x, 2) + pow(ray.y - data-player.pos_y, 2))
