/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_treasure_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 16:11:19 by yusengok          #+#    #+#             */
/*   Updated: 2024/06/17 17:41:08 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	store_sprite_coordinates(t_cub3d *data)
{
	int	x;
	int	y;

	y = 0;
	while (data->map.map[y])
	{
		x = 0;
		while(data->map.map[y][x])
		{
			if (data->map.map[y][x] == 'T')
			{
				data->treasure.map.x = (double)x + 0.5;
				data->treasure.map.y = (double)y + 0.5;
			}
			x++;
		}
		y++;
	}
	// data->treasure.relative_pos.x = data->treasure.map.x - data->player.pos.x;
	// data->treasure.relative_pos.y = data->treasure.map.y - data->player.pos.y;
	printf("Treasure coordinates: x = %f, y = %f\n", data->treasure.map.x, data->treasure.map.y);
	// printf("Player coordinates: x = %f, y = %f\n", data->player.pos.x, data->player.pos.y);
	// printf("Relative pos: x = %f, y = %f\n", data->treasure.relative_pos.x, data->treasure.relative_pos.y);
}
