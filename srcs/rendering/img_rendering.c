/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_rendering.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 15:14:25 by yusengok          #+#    #+#             */
/*   Updated: 2024/05/30 16:05:17 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	render_image(t_cub3d *data)
{
	// int	x;
	
	// x = -1;
	if (data->win_ptr)
	{	
		// while (++x < WIN_W)
		// {
		// 	draw_ceiling(data, x,  WIN_H / 2, data->ceiling_color);
		// 	draw_floor(data, x, WIN_H / 2, data->floor_color);
		// }
		
		ft_raycasting(data);
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
			data->img.img, 0, 0);
		// set_minimap(data);
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
			data->mmap.img.img, 0, 0);
	}
	return (0);
}
