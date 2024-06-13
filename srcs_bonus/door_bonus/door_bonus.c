/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 09:14:18 by yusengok          #+#    #+#             */
/*   Updated: 2024/06/13 13:17:21 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	switch_door_status(t_cub3d *data)
{
	int	target_x;
	int	target_y;

	target_x = (int)data->player.pos_x;
	target_y = (int)data->player.pos_y;
	if (data->player.dir_x > 0)
		target_x += round(data->player.dir_x);
	else if (data->player.dir_x < 0)
		target_x -= round(-data->player.dir_x);
	if (data->player.dir_y > 0)
		target_y += round(data->player.dir_y);
	else if (data->player.dir_y < 0)
		target_y -= round(-data->player.dir_y);
	if (data->map.map[target_y][target_x] == 'D')
	{
		anim_open_door();
		data->map.map[target_y][target_x] = 'O';
		data->player.moved = 1;
	}
	else if (data->map.map[target_y][target_x] == 'O')
	{
		anim_close_door();
		data->map.map[target_y][target_x] = 'D';
		data->player.moved = 1;
	}
}
