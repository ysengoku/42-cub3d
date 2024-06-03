/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 08:02:02 by yusengok          #+#    #+#             */
/*   Updated: 2024/06/03 08:23:17 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	close_window(t_cub3d *data)
{
	int	i;

	mlx_destroy_image(data->mlx_ptr, data->img.img);
	i = 0;
	while (i < 4)
	{
		mlx_destroy_image(data->mlx_ptr, data->textures[i].img);
		free(data->textures[i].path);
		i++;
	}
	if (BONUS)
	{
		mlx_destroy_image(data->mlx_ptr, data->mmap.img.img);
		mlx_destroy_image(data->mlx_ptr, data->mmap.floor.img);
		mlx_destroy_image(data->mlx_ptr, data->mmap.player.img);
		mlx_destroy_image(data->mlx_ptr, data->mmap.wall.img);
	}
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
	// free other things if needed
	exit(0);
	/*== For test =============================*/
	for (int i = 0; i < data->map.maxh; i++)
		free(data->map.mapdata[i]);
	free(data->map.mapdata);
	/*=========================================*/
}

int	handle_closebutton(t_cub3d *data)
{
	close_window(data);
	return (0);
}
