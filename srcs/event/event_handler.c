/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 10:42:38 by yusengok          #+#    #+#             */
/*   Updated: 2024/05/30 14:06:28 by yusengok         ###   ########.fr       */
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
	if (keysym == XK_w) // forward
		move_forward(data, data->player.dir, &data->player.pos_x, &data->player.pos_y);
	// if (keysym == XK_a) //right
	// {
	// 	data->player.pos_x -= 1;  // TEST
	// 	data->player.moved = 1;
	// }
	// if (keysym == XK_s) // back
	// {
	// 	data->player.pos_y += 1;  // TEST
	// 	data->player.moved = 1;
	// }
	// if (keysym == XK_d) // left
	// {
	// 	data->player.pos_x += 1;  // TEST
	// 	data->player.moved = 1;
	// }
	return (0);
}

int	handle_closebutton(t_cub3d *data)
{
	close_window(data);
	return (0);
}

// For bonus
int	handle_mouseevents(int mousecode, int x, int y)
{
	(void)x;
	(void)y;
	if (mousecode == 4) //mouse down
		printf("TEST: mouse down\n"); //TEST
	if (mousecode == 5) //mouse up
		printf("TEST: mouse up\n"); //TEST
	return (0);
}
