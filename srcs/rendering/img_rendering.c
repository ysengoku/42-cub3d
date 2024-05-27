/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_rendering.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 15:14:25 by yusengok          #+#    #+#             */
/*   Updated: 2024/05/27 15:19:07 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	render_image(t_cub3d *data)
{
	int	x;

	x = 0;
	if (data->win_ptr)
	{	
	
		while (x < WIN_W)
		{
		/*=== TEST ===========================================================*/
			draw_ceiling(data, x, WIN_H / 2, convert_color(data->ceiling));
			draw_floor(data, x, WIN_H / 2, convert_color(data->floor));
		/*====================================================================*/

		// --- To code ---
		// check hit
		// if (hit_wall)
		// {
		// 	draw_ceiling(data, x, <start point of wall>, convert_color(data->ceiling));
		//	Draw wall (texture)
		//	draw_floor(data, x, <end point of wall>, convert_color(data->floor));
		//	}
			x++;
		}
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
			data->img.img, 0, 0);
	}
	return (0);
}

void	draw_ceiling(t_cub3d *data, int x, int end, int ceiling_color)
{
	while (end >= 0)
		put_pxl_color(&data->img, x, end--, ceiling_color);
}

void	draw_floor(t_cub3d *data, int x, int start, int floor_color)
{
	while (start <= WIN_H)
		put_pxl_color(&data->img, x, start++, floor_color);
}
