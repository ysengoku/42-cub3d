/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmougel <jmougel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 13:36:40 by yusengok          #+#    #+#             */
/*   Updated: 2024/06/14 13:01:55 by jmougel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_circle(t_cub3d *data, int xc, int yc, int r)
{
	int	i;
	int	x;
	int	y;

	x = 0;
	while (x <= r)
	{
		y = (int)sqrt(r * r - x * x);
		i = -y;
		while (i <= y)
		{
			put_pxl_color(&data->mmap.img, xc + x, yc + i, MMAP_P);
			put_pxl_color(&data->mmap.img, xc - x, yc + i, MMAP_P);
			i++;
		}
		x++;
	}
}

void	draw_scale(t_cub3d *data, int color, int size)
{
	int	x;
	int	y;

	x = data->mmap.minimap_x;
	y = data->mmap.minimap_y;
	while (y < data->mmap.minimap_y + size)
	{
		while (x < data->mmap.minimap_x + size)
		{
			put_pxl_color(&data->mmap.img, x, y, color);
			x++;
		}
		x = data->mmap.minimap_x;
		y++;
	}
	draw_mmap_player_dir(data);
}
