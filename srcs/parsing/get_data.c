/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmougel <jmougel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 16:40:20 by jmougel           #+#    #+#             */
/*   Updated: 2024/06/24 10:38:07 by jmougel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_data(t_cub3d *data)
{
	if (get_sprites_path(data) == EXIT_FAILURE)
		return (exit_parsing(data, "invalid wall texture", false));
	if (get_colors_rgb(data) == EXIT_FAILURE)
		return (exit_parsing(data, "invalid RGB", false));
	return (EXIT_SUCCESS);
}
