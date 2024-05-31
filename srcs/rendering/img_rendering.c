/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_rendering.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 15:14:25 by yusengok          #+#    #+#             */
/*   Updated: 2024/05/31 12:16:15 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	render_image(t_cub3d *data)
{
	if (data->win_ptr)
	{
		ft_raycasting(data);
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
			data->img.img, 0, 0);
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
			data->mmap.img.img, 0, 0);
	}
	return (0);
}
