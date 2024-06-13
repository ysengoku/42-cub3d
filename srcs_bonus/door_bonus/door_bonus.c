/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 09:14:18 by yusengok          #+#    #+#             */
/*   Updated: 2024/06/13 09:48:39 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	open_door(t_cub3d *data)
{
	// int	d_x;
	// int	d_y;
	
	// d_x = data->player.pos_x + data->player.dir_x;
	// d_y = data->player.pos_y + data->player.dir_y;
	// if (data->map.map[d_y][d_x] == 'D')
	// {
	// 	data->map.map[d_y][d_x] = 'O';
	// 	data->player.moved = 1;
	// }
	int	i;
	i = 0;
	while (i < data->door_count)
	{
		data->map.map[data->doors[i].map_y][data->doors[i].map_x] = 'O';
		i++;
	}
	data->player.moved = 1;
}

void	close_door(t_cub3d *data)
{
	int	i;

	i = 0;
	while (i < data->door_count)
	{
		data->map.map[data->doors[i].map_y][data->doors[i].map_x] = 'D';
		i++;
	}
	data->player.moved = 1;
}
