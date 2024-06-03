/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 10:42:38 by yusengok          #+#    #+#             */
/*   Updated: 2024/06/03 10:28:10 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	handle_keypress(int keysym, t_cub3d *data)
{
	if (keysym == XK_Escape)
		close_window(data);
	if (keysym == XK_Right)
		data->key_pressed_right = 1;
	if (keysym == XK_Left)
		data->key_pressed_left = 1;
	if (keysym == XK_w)
		move_forward(data, data->player.dir, &data->player.pos_x,
			&data->player.pos_y);
	if (keysym == XK_a)
		move_left(data, data->player.dir, &data->player.pos_x,
			&data->player.pos_y);
	if (keysym == XK_s)
		move_backward(data, data->player.dir, &data->player.pos_x,
			&data->player.pos_y);
	if (keysym == XK_d)
		move_right(data, data->player.dir, &data->player.pos_x,
			&data->player.pos_y);
	return (0);
}

int	handle_keyrelease(int keysym, t_cub3d *data)
{
	if (keysym == XK_Right)
		data->key_pressed_right = 0;
	if (keysym == XK_Left)
		data->key_pressed_left = 0;
	return (0);
}

// int	handle_mouseevents(int mousecode, int x, int y, t_cub3d *data)
// {
// 	(void)y;
// 	(void)x;
// 	if (mousecode == 4) //scroll up
// 		rotate_counterclockwise(data);
// 	if (mousecode == 5) //scroll down
// 		rotate_clockwise(data);
// 	return (0);
// }

// For bonus
int handle_mousemove(int x, int y, t_cub3d *data)
{
	// to code
	if (BONUS)
	{
		(void)x;
		(void)y;
		(void)data;
	}
	return (0);
}
