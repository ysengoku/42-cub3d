/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 08:43:31 by yusengok          #+#    #+#             */
/*   Updated: 2024/06/17 08:56:05 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rotate_clockwise(t_cub3d *data)
{
	data->player.dir_degree += ROTATE;
	if (data->player.dir_degree >= 360)
		data->player.dir_degree = 0;
	data->player.moved = 1;
}

void	rotate_counterclockwise(t_cub3d *data)
{
	data->player.dir_degree -= ROTATE;
	if (data->player.dir_degree < 0)
		data->player.dir_degree = 360 - ROTATE;
	data->player.moved = 1;
}
