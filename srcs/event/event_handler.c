/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmougel <jmougel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 10:42:38 by yusengok          #+#    #+#             */
/*   Updated: 2024/06/14 14:04:55 by jmougel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	keypress(int keysym, t_cub3d *data)
{
	if (keysym == XK_Escape)
		close_window(data);
	if (keysym == XK_Right)
		data->key_pressed_right = 1;
	if (keysym == XK_Left)
		data->key_pressed_left = 1;
	if (keysym == XK_w)
		data->key_pressed_w = 1;
	if (keysym == XK_a)
		data->key_pressed_a = 1;
	if (keysym == XK_s)
		data->key_pressed_s = 1;
	if (keysym == XK_d)
		data->key_pressed_d = 1;
	/*=== bonus ===============*/
	if (keysym == XK_e)
		switch_door_status(data);
	/*=========================*/
	if (keysym == XK_x && data->key_pressed_x == 0)
		data->key_pressed_x = 1;
	else if (keysym == XK_x && data->key_pressed_x == 1)
		data->key_pressed_x = 0;
	return (0);
}

int	keyrelease(int keysym, t_cub3d *data)
{
	if (keysym == XK_Right)
		data->key_pressed_right = 0;
	if (keysym == XK_Left)
		data->key_pressed_left = 0;
	if (keysym == XK_w)
		data->key_pressed_w = 0;
	if (keysym == XK_a)
		data->key_pressed_a = 0;
	if (keysym == XK_s)
		data->key_pressed_s = 0;
	if (keysym == XK_d)
		data->key_pressed_d = 0;
	return (0);
}

int	closebutton(t_cub3d *data)
{
	close_window(data);
	return (0);
}
