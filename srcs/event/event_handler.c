/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 10:42:38 by yusengok          #+#    #+#             */
/*   Updated: 2024/05/31 14:07:41 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	close_window(t_cub3d *data)
{
	mlx_destroy_image(data->mlx_ptr, data->mmap.img.img);
	mlx_destroy_image(data->mlx_ptr, data->img.img);
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
	// free other things if needed
	/*== For test =============================*/
	for (int i = 0; data->map.mapdata[i]; i++)
		free(data->map.mapdata[i]);
	free(data->map.mapdata);
	/*=========================================*/
	exit(1);
}

int	handle_keyevents(int keysym, t_cub3d *data)
{
	if (keysym == XK_Escape)
		close_window(data);
	if (keysym == XK_Left)
		rotate_counterclockwise(data);
	if (keysym == XK_Right)
		rotate_clockwise(data);
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

int	handle_closebutton(t_cub3d *data)
{
	close_window(data);
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
	(void)x;
	(void)y;
	(void)data;
	return (0);
}