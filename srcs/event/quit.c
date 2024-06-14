/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 08:02:02 by yusengok          #+#    #+#             */
/*   Updated: 2024/06/14 16:33:59 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	close_window(t_cub3d *data)
{
	int	i;

	i = 0;
	// while (i < 5) // if not bonus, while (i < 4)
	// {
	// 	mlx_destroy_image(data->mlx_ptr, data->wall[i].img);
	// 	free(data->wall[i].path);
	// 	i++;
	// }
	clear_texture_img(data);
	if (BONUS && data->mmap.img.img)
		mlx_destroy_image(data->mlx_ptr, data->mmap.img.img);
	mlx_destroy_image(data->mlx_ptr, data->img.img);
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
	free_data_map(&data->map);
	exit(0);
}
