/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 08:09:43 by yusengok          #+#    #+#             */
/*   Updated: 2024/05/23 15:16:10 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/* ----- libraries ----- */
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

/* ----- math definition ----- */
# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

/* ----- window definition ----- */
# define WINNAME "cub3D"
# define WIN_W 1280
# define WIN_H 720

/* ----- enum definition ----- */
enum	e_direction
{
	NORTH = 1,
	SOUTH = 2,
	EAST = 3,
	WEST = 4
};

/* ----- type definition ----- */
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
	/* JUST FOR TEST */
	char	**mapdata;
}				t_map;

typedef struct s_player
{
	/* JUST FOR TEST */
	float				pos_x;
	float				pos_y;
	enum e_direction	direction; 
}				t_player;

typedef struct s_color
{
	float	r;
	float	g;
	float	b;
}				t_color;

typedef struct s_cub3d
{
	t_xvar		*mlx_ptr;
	t_win_list	*win_ptr;
	t_imgdata	img;
	/* JUST FOR TEST */
	t_map		map;
	t_player	player;
}				t_cub3d;

/* ----- Image rendering ----- */
int		render_image(t_cub3d *data);

/* ----- Event handler ----- */
int		handle_keyevents(int keysym, t_cub3d *data);
int		handle_mouseevents(int mousecode, int x, int y);
int		handle_closebutton(t_cub3d *data);

/* ----- Error handling ----- */
void	ft_perror_exit(char *message, int code);
void	ft_error_exit(char *message, int code);

#endif
