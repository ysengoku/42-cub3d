/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 08:09:43 by yusengok          #+#    #+#             */
/*   Updated: 2024/06/19 13:42:31 by yusengok         ###   ########.fr       */
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
# include <stdbool.h>
# include "libft.h"
# include "mlx.h"
# include "mlx_int.h"

/*===== paths sprits ======================================================*/

# define SPRITE_NO "./textures/walls/stone00.xpm"
# define SPRITE_SO "./textures/walls/stone01.xpm"
# define SPRITE_WE "./textures/walls/stone02.xpm"
# define SPRITE_EA "./textures/walls/stone03.xpm"

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

# ifndef FOV
#  define FOV 90
# endif
# define MOVE 0.1
# define ROTATE 2

/*+++++ BONUS ++++++++++++++++++++++++++++++++++++++++++++++*/
# define MINI_MAP_W 100
# define MINI_MAP_H 100

# define MOUSE_DOWN 4
# define MOUSE_UP 5
# define PITCH 1

# define MMAP_SCALE 20
# define MMAP_SIZE 9
# define MMAP_BORDER 1
# define MMAP_EMPTY 0
# define MMAP_WALL 4868682
# define MMAP_FLOOR 13816530
# define MMAP_P 12915042
# define MMAP_DIR 13959168
# define MMAP_RAY 16776623
# define MMAP_SPACE 11977418
# define MMAP_DOOR 9868950

# define DOOR_TEX_CLOSE "./textures/door/door.xpm"
# define DOOR_TEX1 "./textures/door/door1.xpm"
# define DOOR_TEX2 "./textures/door/door2.xpm"
# define DOOR_TEX3 "./textures/door/door3.xpm"
# define DOOR_TEX4 "./textures/door/door4.xpm"
# define DOOR_TEX5 "./textures/door/door5.xpm"
# define DOOR_TEX_OPEN "./textures/door/door6.xpm"

# define TREASURE_TEX "./textures/treasure/treasure.xpm"
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

# ifndef BONUS
#  define BONUS 1
# endif

/*===== enum definition =====================================================*/
enum	e_direction
{
	N = 270,
	E = 0,
	S = 90,
	W = 180
};

enum	e_wallside
{
	NO,
	SO,
	WE,
	EA,
	DR_C,
	DR1,
	DR2,
	DR3,
	DR4,
	DR5,
	DR_O,
	TR
};

enum	e_hit
{
	NOTHING,
	WALL,
	DOOR_OPEN,
	DOOR_CLOSE,
	DOOR_ANIM
};

/*===== structures ===========================================================*/
typedef struct s_vector
{
	double	x;
	double	y;
}				t_vector;

typedef struct s_imgdata
{
	void	*img;
	char	*addr;
	int		bits_per_pxl;
	int		line_len;
	int		endian;
}				t_imgdata;

typedef struct s_xpm_img
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

typedef struct s_check_map
{
	int		player;
	int		treasure;
	bool	catch_treasure;
	bool	invalid_map;
	char	old_char;
	char	new_char;
}	t_check_map;

typedef struct s_map
{
	t_check_map			check;
	char				**data_map;
	char				**map;
	char				**dup_map;
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
	double				fov;
	t_vector			pos;
	double				dir_degree;
	t_vector			dir;
	double				plane_length;
	t_vector			plane;
}				t_player;

typedef struct s_hit
{
	double			dist;
	int				h;
	enum e_wallside	side;
	enum e_wallside	tex;
}				t_hit;

typedef struct s_ray
{
	enum e_hit		hit;
	int				w_hit;
	int				close_door_hit;
	int				open_door_hit;
	double			camera_p;
	t_vector		dir;
	int				map_x;
	int				map_y;
	int				step_x;
	int				step_y;
	t_vector		sidedist;
	t_vector		delta;
	t_hit			wall;
	t_hit			closed_d;
	t_hit			open_d;
}			t_ray;

typedef struct s_line
{
	int		y;
	int		y_start;
	int		y_end;
	int		tx_x;
	int		tx_y;
	double	tx_start_y;
	double	span;
	int		color;
}				t_line;

typedef struct s_minimap
{
	t_imgdata	img;
	int			minimap_x;
	int			minimap_y;
	int			totalsize;
	t_xpm_img	floor;
	t_xpm_img	player;
	t_xpm_img	wall;
}				t_minimap;

typedef struct s_keys
{
	int			key_pressed_left;
	int			key_pressed_right;
	int			key_pressed_w;
	int			key_pressed_s;
	int			key_pressed_a;
	int			key_pressed_d;
	int			key_pressed_m;
	/*++++++ Bonus +++++++++++++++++++*/
	int			key_pressed_x;
	/*++++++++++++++++++++++++++++++++*/
}	t_keys;

typedef struct s_treasure
{
	t_vector	map;
	t_vector	relative_pos;
	t_vector	camera;
	int			screen_x;
	int			draw_height;
	int			draw_width;
	int			start_x;
	int			end_x;
	int			start_y;
	int			end_y;
	int			visible;
}				t_treasure;

typedef struct s_cub3d
{
	void		*mlx_ptr;
	void		*win_ptr;
	int			win_half_w;
	int			win_half_h;
	t_imgdata	img;
	t_map		map;
	t_player	player;
	int			ceiling_color;
	int			floor_color;
	t_xpm_img	wall[12];
	t_keys		keys;
	/*++++++ Bonus +++++++++++++++++++*/
	int			previous_mouse_x;
	t_minimap	mmap;
	bool		anim_open;
	bool		anim_close;
	bool		anim;
	int			animation;
	t_treasure	treasure;
	double		wall_zbuffer[WIN_W];
	/*+++++++++++++++++++++++++++++++++*/
}				t_cub3d;

/*===== functions ============================================================*/

/*----- Parsing -----*/
int				parsing(char *file, t_cub3d *map);
char			**get_file(char *file);
int				get_data(t_cub3d *data);
int				get_sprites_path(t_cub3d *map);
int				get_colors_rgb(t_map *data_map);
int				get_maps(t_cub3d *data);
int				check_map(t_cub3d *data);
int				algo_flood_fill(t_cub3d *data);
void			flood_fill(t_cub3d *data, char **dup_map, int pos_x, int pos_y);
void			free_split(char **map);
void			free_data_map(t_map *data_map);
void			exit_parsing(t_map *data_map, char *message);
void			set_data(t_cub3d *data, t_player *player, t_map *map);
int				set_wall_texture(t_cub3d *data, t_xpm_img *wall);

/*----- Ray casting -----*/
int				display(t_cub3d *data);
void			raycasting(t_cub3d *data, int x, t_xpm_img *door);
void			check_hit(t_cub3d *data, t_ray *ray);
void			check_door_hit(t_cub3d *data, t_ray *ray, int x, char c);

/*----- Image rendering -----*/
int				game_loop(t_cub3d *data);
void			draw_wall(t_cub3d *data, int x, t_ray *ray);
void			draw_ceiling(t_cub3d *data, int x, int end, int ceiling_color);
void			draw_floor(t_cub3d *data, int start, int end, int floor_color);
void			draw_minimap(t_cub3d *data);
void			draw_minimap_zone(t_cub3d *data, int size);
int				convert_color(int rgb[3]);
unsigned int	get_txcolor(t_xpm_img *texture, int x, int y);
void			put_pxl_color(t_imgdata *img, int x, int y, int color);

/*----- Event handler -----*/
int				keypress(int keysym, t_cub3d *data);
int				keyrelease(int keysym, t_cub3d *data);
int				closebutton(t_cub3d *data);
void			close_window(t_cub3d *data);
void			move_forward(t_cub3d *data, t_player *player, t_map *map);
void			move_backward(t_cub3d *data, t_player *player, t_map *map);
void			move_right(t_cub3d *data, t_player *player, t_map *map);
void			move_left(t_cub3d *data, t_player *player, t_map *map);
void			rotate_counterclockwise(t_cub3d *data);
void			rotate_clockwise(t_cub3d *data);

/*----- Error handling & free -----*/
void			ft_perror_exit(char *message, int code);
void			ft_error_exit(char *message, int code);
int				free_all(t_cub3d *data, int status);
void			free_texture_paths(t_xpm_img *wall, int size);
void			clear_data(t_cub3d *data);
void			clear_texture_img(t_cub3d *data);

/*===== bonus part functions =================================================*/

/*----- Minimap -----*/
int				create_minimap_img(t_cub3d *data, t_minimap *mmap);
void			draw_mmap_player_dir(t_cub3d *data);
void			draw_ray_mmap(t_cub3d *data, t_ray *ray);
void			draw_scales(t_cub3d *data, int *cam_x, int *cam_y);
void			draw_player(t_cub3d *data, int xc, int yc, int r);

/*----- Event -----*/
int				mousemove(int x, int y, t_cub3d *data);
void			action_event(t_cub3d *data);

/*----- Doors -----*/
int				get_door_and_treasure_texture_paths(t_cub3d *data);
void			draw_door(t_cub3d *data, int x, t_ray *r, t_hit *door);
void			draw_anim_door(t_cub3d *data, int x, t_ray *r, t_xpm_img *tex);
void			animations(t_cub3d *data);
void			anim_door(t_cub3d *data, int target_y, int target_x);

/*----- Treasures -----*/
void			store_sprite_coordinates(t_cub3d *data);
void			set_treasure_data(t_cub3d *data, t_treasure *treasures);
void			draw_treasure(t_cub3d *data, t_treasure *treasure);

#endif
