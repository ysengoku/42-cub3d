/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmougel <jmougel@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 09:59:51 by yusengok          #+#    #+#             */
/*   Updated: 2024/06/03 19:05:23 by jmougel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_forward(t_cub3d *data, double player_dir, int *x, int *y)
{
	if (((player_dir >= 0 && player_dir < 22.5)
			|| (player_dir >= 337.5 && player_dir < 360))
		&& data->map.map[*y][*x + MOVE] != '1')
		*x += MOVE;
	if (player_dir >= 22.5 && player_dir < 67.5)
		move_north_east(data, x, y);
	if ((player_dir >= 67.5 && player_dir < 112.5)
		&& data->map.map[*y - MOVE][*x] != '1')
		*y -= MOVE;
	if (player_dir >= 112.5 && player_dir < 157.5)
		move_north_west(data, x, y);
	if ((player_dir >= 157.5 && player_dir < 202.5)
		&& data->map.map[*y][*x - MOVE] != '1')
		*x -= MOVE;
	if (player_dir >= 202.5 && player_dir < 247.5)
		move_south_west(data, x, y);
	if ((player_dir >= 247.5 && player_dir < 292.5)
		&& data->map.map[*y + MOVE][*x] != '1')
		*y += MOVE;
	if (player_dir >= 292.5 && player_dir < 337.5)
		move_south_east(data, x, y);
	data->player.moved = 1;
}

void	move_backward(t_cub3d *data, double player_dir, int *x, int *y)
{
	if (((player_dir >= 0 && player_dir < 22.5)
			|| (player_dir >= 337.5 && player_dir < 360))
		&& data->map.map[*y][*x - MOVE] != '1')
		*x -= MOVE;
	if (player_dir >= 22.5 && player_dir < 67.5)
		move_south_west(data, x, y);
	if ((player_dir >= 67.5 && player_dir < 112.5)
		&& data->map.map[*y + MOVE][*x] != '1')
		*y += MOVE;
	if (player_dir >= 112.5 && player_dir < 157.5)
		move_south_east(data, x, y);
	if ((player_dir >= 157.5 && player_dir < 202.5)
		&& data->map.map[*y][*x + MOVE] != '1')
		*x += MOVE;
	if (player_dir >= 202.5 && player_dir < 247.5)
		move_north_east(data, x, y);
	if ((player_dir >= 247.5 && player_dir < 292.5)
		&& data->map.map[*y - MOVE][*x] != '1')
		*y -= MOVE;
	if (player_dir >= 292.5 && player_dir < 337.5)
		move_north_west(data, x, y);
	data->player.moved = 1;
}

void	move_right(t_cub3d *data, double player_dir, int *x, int *y)
{
	if (((player_dir >= 0 && player_dir < 22.5)
			|| (player_dir >= 337.5 && player_dir < 360))
		&& data->map.map[*y + MOVE][*x] != '1')
		*y += MOVE;
	if (player_dir >= 22.5 && player_dir < 67.5)
		move_south_east(data, x, y);
	if ((player_dir >= 67.5 && player_dir < 112.5)
		&& data->map.map[*y][*x + MOVE] != '1')
		*x += MOVE;
	if (player_dir >= 112.5 && player_dir < 157.5)
		move_north_east(data, x, y);
	if ((player_dir >= 157.5 && player_dir < 202.5)
		&& data->map.map[*y - MOVE][*x] != '1')
		*y -= MOVE;
	if (player_dir >= 202.5 && player_dir < 247.5)
		move_north_west(data, x, y);
	if ((player_dir >= 247.5 && player_dir < 292.5)
		&& data->map.map[*y][*x - MOVE] != '1')
		*x -= MOVE;
	if (player_dir >= 292.5 && player_dir < 337.5)
		move_south_west(data, x, y);
	data->player.moved = 1;
}

void	move_left(t_cub3d *data, double player_dir, int *x, int *y)
{
	if (((player_dir >= 0 && player_dir < 22.5)
			|| (player_dir >= 337.5 && player_dir < 360))
		&& data->map.map[*y - MOVE][*x] != '1')
		*y -= MOVE;
	if (player_dir >= 22.5 && player_dir < 67.5)
		move_north_west(data, x, y);
	if ((player_dir >= 67.5 && player_dir < 112.5)
		&& data->map.map[*y][*x - MOVE] != '1')
		*x -= MOVE;
	if (player_dir >= 112.5 && player_dir < 157.5)
		move_south_west(data, x, y);
	if ((player_dir >= 157.5 && player_dir < 202.5)
		&& data->map.map[*y + MOVE][*x] != '1')
		*y += MOVE;
	if (player_dir >= 202.5 && player_dir < 247.5)
		move_south_east(data, x, y);
	if ((player_dir >= 247.5 && player_dir < 292.5)
		&& data->map.map[*y][*x + MOVE] != '1')
		*x += MOVE;
	if (player_dir >= 292.5 && player_dir < 337.5)
		move_north_east(data, x, y);
	data->player.moved = 1;
}
