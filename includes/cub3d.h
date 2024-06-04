/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 08:09:43 by yusengok          #+#    #+#             */
/*   Updated: 2024/06/04 13:57:03 by yusengok         ###   ########.fr       */
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
#include <stdbool.h>
# include "libft.h"
# include "mlx.h"
# include "mlx_int.h"

/*===== paths sprits ======================================================*/

# define SPRITE_NO "./textures/test/north.xpm"
# define SPRITE_SO "./textures/test/south.xpm"
# define SPRITE_WE "./textures/test/west.xpm"
# define SPRITE_EA "./textures/test/east.xpm"

/*===== colors ======================================================*/

# define RGB_F "169,169,169"
# define RGB_C "52,52,52"

/*===== math definition ======================================================*/
# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

/*===== macro definition =====================================================*/
# define WINNAME "cub3D"
# define WIN_W 960
# define WIN_H 720
# define TEX_SIZE 64

# ifndef FOV
#  define FOV 90
# endif
# define MOVE 0.33
# define ROTATE 5

# define MMAP_SCALE	8
# define MMAP_WALL 24676 //(int)0x006064
# define MMAP_FLOOR 11583173 //(int)0xB0BEC5
# define MMAP_P 12915042 //(int)0xC51162
# define MMAP_DIR 13959168 //(int)0xD50000
# define MMAP_SPACE 11977418 //(int)0xB6C2CA
# define MMAP_F "./textures/minimap/floor.xpm"
# define MMAP_PL "./textures/minimap/player.xpm"
# define MMAP_WL "./textures/minimap/wall.xpm"

# ifndef BONUS
#  define BONUS 1
# endif

/*===== enum definition =====================================================*/
enum	e_direction
{
	N = 90,
	E = 0,
	S = 270,
	W = 180
};

enum	e_wallside
{
	NO = 0,
	SO = 1,
	WE = 2,
	EA = 3
};

/*===== structures ===========================================================*/
typedef struct s_imgdata
{
	void	*img;
	char	*addr;
	int		bits_per_pxl;
	int		line_len;
	int		endian;
}				t_imgdata;

typedef struct 	s_xpm_img
{
	void		*img;
	char		*addr;
	int			bpp;
	int			line_len;
	int			endian;
    int			w;
    int			h;
	char		*path;
}				t_xpm_img;

typedef struct s_map
{
	char				**data_map;
	char				**map;
	char				**dup_map;
	char				*sprite_no;
	char				*sprite_so;
	char				*sprite_we;
	char				*sprite_ea;
	char				player;
	int					f_rgb[3];
	int					c_rgb[3];
	int					map_len_x;
	int					map_len_y;
	int					pos_x;
	int					pos_y;
	enum e_direction	p_dir;
}				t_map;

typedef struct s_player
{
	double				fov; // FOV in radians
	double				pos_x;
	double				pos_y;
	enum e_direction	initial_dir;
	double				dir; //direction in degree
	double				dir_x;
	double				dir_y;
	double				plane_length;
	double				plane_x;
	double				plane_y;
	int					moved;

}				t_player;

typedef struct s_ray
{
	double			camera_p;
	double			dir_x;
	double			dir_y;
	int				map_x;
	int				map_y;
	int				step_x;
	int				step_y;
	double			sidedist_x;
	double			sidedist_y;
	double			delta_x;
	double			delta_y;
	double			distance;
	int				wall_height;
	enum e_wallside	wall_side;
}			t_ray;

typedef struct s_line
{
	int		y;
	int		y_start;
	int		y_end;
	int		tex_x;
	int		tex_y;
	double	span;
}				t_line;

typedef struct s_minimap
{
	t_imgdata	img;
	int			minimap_x;
	int			minimap_y;
	t_xpm_img	floor;
	t_xpm_img	player;
	t_xpm_img	wall;
}				t_minimap;

typedef struct s_cub3d
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_imgdata	img;
	t_map		map;
	t_player	player;
	int			ceiling_color;
	int			floor_color;
	t_xpm_img	wall[4];
	//--- For TEST -----------
	int			colors[4];
	//------------------------
	int			key_pressed_left;
	int			key_pressed_right;
	int			key_pressed_w;
	int			key_pressed_s;
	int			key_pressed_a;
	int			key_pressed_d;
	t_minimap	mmap;
}				t_cub3d;

/*===== functions ============================================================*/
/*----- Parsing -----*/
int		parsing(char *file, t_map *data_map);
char	**get_file(char *file);
int		get_data(t_map *data_map);
int		get_sprites_path(t_map *data_map);
int		get_colors_rgb(t_map *data_map);
int		get_maps(t_map *data_map);
int		check_map(t_map *data_map);
void	free_split(char **map);
void	free_data_map(t_map *data_map);
void	exit_parsing(t_map *data_map, char *message);
void	set_data(t_cub3d *data, t_player *player, t_map *map);
int		set_wall_texture(t_cub3d *data, t_xpm_img wall[4]);

/*----- Ray casting -----*/
int		ft_raycasting(t_cub3d *data);
void	check_wall_hit(t_cub3d *data, t_ray *ray);

/*----- Image rendering -----*/
int		game_loop(t_cub3d *data);
void	draw_wall_tmp(t_cub3d *data, int x, t_ray *ray); // Temporary version without texture
void	draw_wall(t_cub3d *data, int x, t_ray *ray);
void	draw_ceiling(t_cub3d *data, int x, int end, int ceiling_color);
void	draw_floor(t_cub3d *data, int start, int end, int floor_color);
int		convert_color(int rgb[3]);
void	put_pxl_color(t_imgdata *img, int x, int y, int color);

/*----- Event handler -----*/
int		handle_keypress(int keysym, t_cub3d *data);
int		handle_keyrelease(int keysym, t_cub3d *data);
// int		handle_mouseevents(int mousecode, int x, int y, t_cub3d *data);
int 	handle_mousemove(int x, int y, t_cub3d *data);
int		handle_closebutton(t_cub3d *data);
void	close_window(t_cub3d *data);
// void	move_forward(t_cub3d *data, double player_dir, int *x, int *y);
void	move_forward(t_cub3d *data, t_player *player, t_map *map);
void	move_backward(t_cub3d *data, t_player *player, t_map *map);
void	move_right(t_cub3d *data, t_player *player, t_map *map);
void	move_left(t_cub3d *data, t_player *player, t_map *map);
// void	move_right(t_cub3d *data, double player_dir, int *x, int *y);
// void	move_left(t_cub3d *data, double player_dir, int *x, int *y);
// void	move_north_east(t_cub3d *data, int *x, int *y);
// void	move_north_west(t_cub3d *data, int *x, int *y);
// void	move_south_east(t_cub3d *data, int *x, int *y);
// void	move_south_west(t_cub3d *data, int *x, int *y);
void	rotate_counterclockwise(t_cub3d *data);
void	rotate_clockwise(t_cub3d *data);

/*----- Error handling -----*/
void	ft_perror_exit(char *message, int code);
void	ft_error_exit(char *message, int code);
void	free_mapdata(t_map *map);
int		free_all(t_cub3d *data, int status);

/*----- Minimap -----*/
int		create_minimap_img(t_cub3d *data, t_minimap *mmap);
void	set_minimap(t_cub3d *data);

#endif
