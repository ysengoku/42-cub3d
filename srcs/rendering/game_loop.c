/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmougel <jmougel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 15:14:25 by yusengok          #+#    #+#             */
/*   Updated: 2024/06/14 14:33:39 by jmougel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	game_loop(t_cub3d *data)
{
	static int	i = 0;
	int	j;

	j = 0;
	display(data, i);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
		data->img.img, 0, 0);
	if (BONUS)
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
			data->mmap.img.img, 0, 0);
	if (data->key_pressed_right)
		rotate_clockwise(data);
	if (data->key_pressed_left)
		rotate_counterclockwise(data);
	if (data->key_pressed_w)
		move_forward(data, &data->player, &data->map);
	if (data->key_pressed_a)
		move_left(data, &data->player, &data->map);
	if (data->key_pressed_s)
		move_backward(data, &data->player, &data->map);
	if (data->key_pressed_d)
		move_right(data, &data->player, &data->map);
	if (BONUS)
	{
		if (data->anim_open == true && i <= 3)
		{
			i++;
			while (j < 90000000)
				j++;
		}
		if (data->anim_open == true && i > 3)
		{
			i = 0;
			data->anim_open = false;
			data->map.map[(int)round(data->player.dir_y)
				+ (int)data->player.pos_y][(int)round(data->player.dir_x)
				+ (int)data->player.pos_x] = 'O';
		}
		if (data->anim_close == true && i == 2)
		{
			while (j < 90000000)
				j++;
			i = 0;
			data->anim_close = false;
			data->map.map[(int)round(data->player.dir_y)
				+ (int)data->player.pos_y][(int)round(data->player.dir_x)
				+ (int)data->player.pos_x] = 'D';
		}
		else if (data->anim_close == true)
			i = 2;
	}
	return (0);
}
