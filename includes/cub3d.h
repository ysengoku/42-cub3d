/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 08:09:43 by yusengok          #+#    #+#             */
/*   Updated: 2024/05/28 15:09:07 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/*===== libraries ============================================================*/
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <math.h>
# include <errno.h>
# include "libft.h"
# include "mlx.h"
# include "mlx_int.h"

/*===== math definition ======================================================*/
# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

/*===== macro definition =====================================================*/
# define WINNAME "cub3D"
# define WIN_W 1280
# define WIN_H 720
# define TEXTURE_SIZE 64
# define FOV 60
// # define MOVE_SPEED 
// # define ROTATE_SPEED

// /*===== enum definition =====================================================*/
// enum	e_direction
// {
// 	NORTH = 1,
// 	SOUTH = 2,
// 	EAST = 3,
// 	WEST = 4
// };

/*===== structures ===========================================================*/
typedef struct s_imgdata
{
	void	*img;
	char	*addr;
	int		bits_per_pxl;
	int		line_len;
	int		endian;
}				t_imgdata;

typedef struct s_map
{
	// char	**mapdata;
	int		**mapdata;
}				t_map;

typedef struct s_player
{
	int		pos_x;
	int		pos_y;
	double	angle;
	double	dir_x;
	double	dir_y;
	// NORTH : dir_x = 0, dir_y = -1 (270)
	// SOUTH : dir_x = 0, dir_y = 1 (0)
	// EAST : dir_x = 1, dir_y = 0 (90)
	// WEST : dir_x = -1, dir_y = 0 (180)
	double	plane_x;
	double	plane_y;

}				t_player;

typedef struct s_color
{
	double	r;
	double	g;
	double	b;
}				t_color;

typedef struct s_ray
{
	double	angle_rad; // initialize: player's angle - FOV / 2 --> convert in radians
	// double	dir_x;
	// double	dir_y;
	double	inc_angle; // = FOV / WIN_W
	double	x;
	double	y;
	double	inc_x;
	double	inc_y;
	double	x_distance;
	double	y_distance;
	double	wall_height;
	/* texture */
	//--- For TEST -------
	t_color	wall_color_n;
	t_color	wall_color_s;
	t_color	wall_color_e;
	t_color	wall_color_w;
	//--------------------
}				t_ray;

typedef struct s_cub3d
{
	t_xvar		*mlx_ptr;
	t_win_list	*win_ptr;
	t_imgdata	img;
	t_map		map;
	t_player	player;
	t_color		ceiling;
	t_color		floor;
	// textures
}				t_cub3d;

/*===== functions ============================================================*/
/*----- Ray casting -----*/
int		ft_raycasting(t_cub3d *data);

/*----- Image rendering -----*/
int		render_image(t_cub3d *data);
void	draw_floor(t_cub3d *data, int start, int end, int floor_color);
void	draw_ceiling(t_cub3d *data, int x, int end, int ceiling_color);
int		convert_color(t_color color);
void	put_pxl_color(t_imgdata *img, int x, int y, int color);

/*----- Event handler -----*/
int		handle_keyevents(int keysym, t_cub3d *data);
int		handle_mouseevents(int mousecode, int x, int y);
int		handle_closebutton(t_cub3d *data);

/*----- Error handling -----*/
void	ft_perror_exit(char *message, int code);
void	ft_error_exit(char *message, int code);

#endif
