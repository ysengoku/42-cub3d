/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 08:09:43 by yusengok          #+#    #+#             */
/*   Updated: 2024/06/14 16:32:26 by yusengok         ###   ########.fr       */
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

# ifndef FOV
#  define FOV 90
# endif
# define MOVE 0.1
# define ROTATE 5

/*+++++ BONUS ++++++++++++++++++++++++++++++++++++++++++++++*/
# define MINI_MAP_W 100
# define MINI_MAP_H 100

# define MOUSE_DOWN 4
# define MOUSE_UP 5
# define PITCH 1

# define MMAP_SCALE 20
# define MMAP_SIZE 9
# define MMAP_BORDER 1
# define MMAP_TOTAL_SIZE MMAP_SCALE * MMAP_SIZE + MMAP_BORDER * MMAP_SIZE
# define MMAP_EMPTY 0
# define MMAP_WALL 4868682
# define MMAP_FLOOR 13816530
# define MMAP_P 12915042
# define MMAP_DIR 13959168
# define MMAP_RAY 16776623
# define MMAP_SPACE 11977418
# define MMAP_DOOR 9868950

# define DOOR_TEX "./textures/door/fence1.xpm"
# define DOOR_TEX1 "./textures/door/fence2.xpm"
# define DOOR_TEX2 "./textures/door/fence3.xpm"
# define DOOR_TEX3 "./textures/door/fence4.xpm"
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
	NO = 0,
	SO = 1,
	WE = 2,
	EA = 3,
	DR = 4,
	DR1 = 5,
	DR2 = 6,
	DR3 = 7
};

enum	e_hit
{
	WALL = 1,
	DOOR = 2,
	NOTHING = 0
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

typedef struct s_map
{
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
	double				pos_x;
	double				pos_y;
	double				dir;
	double				dir_x;
	double				dir_y;
	double				plane_length;
	double				plane_x;
	double				plane_y;
	int					moved;
	int					pitch;
}				t_player;

typedef struct s_door
{
	int	map_x;
	int	map_y;
}			t_door;

typedef struct s_ray
{
	enum e_hit		hit;
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
	double			w_dist;
	int				wall_height;
	enum e_wallside	w_side;
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
	t_xpm_img	floor;
	t_xpm_img	player;
	t_xpm_img	wall;
}				t_minimap;

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
	t_xpm_img	wall[8];
	int			key_pressed_left;
	int			key_pressed_right;
	int			key_pressed_w;
	int			key_pressed_s;
	int			key_pressed_a;
	int			key_pressed_d;
	int			key_pressed_m;
	/*++++++ Bonus +++++++++++++++++++*/
	int			key_pressed_x;
	int			previous_mouse_x;
	t_minimap	mmap;
	bool		anim_open;
	bool		anim_close;
	/*+++++++++++++++++++++++++++++++++*/
}				t_cub3d;

/*===== functions ============================================================*/

/*----- Parsing -----*/
int				parsing(char *file, t_cub3d *map);
char			**get_file(char *file);
int				get_data(t_cub3d *data);
int				get_sprites_path(t_cub3d *map);
int				get_colors_rgb(t_map *data_map);
int				get_maps(t_map *data_map);
int				check_map(t_map *data_map);
int				algo_flood_fill(t_map *data_map);
void			flood_fill(char **dup_map, int pos_x, int pos_y, bool *valid);
void			free_split(char **map);
void			free_data_map(t_map *data_map);
void			exit_parsing(t_map *data_map, char *message);
void			set_data(t_cub3d *data, t_player *player, t_map *map);
int				set_wall_texture(t_cub3d *data, t_xpm_img *wall);

/*----- Ray casting -----*/
int				display(t_cub3d *data, int i);
void			raycasting(t_cub3d *data, int x, t_xpm_img *door);
void			check_wall_hit(t_cub3d *data, t_ray *ray);

/*----- Image rendering -----*/
int				game_loop(t_cub3d *data);
void			draw_wall(t_cub3d *data, int x, t_ray *ray);
void			draw_ceiling(t_cub3d *data, int x, int end, int ceiling_color);
void			draw_floor(t_cub3d *data, int start, int end, int floor_color);
void			draw_minimap(t_cub3d *data);
void			draw_full_minimap(t_cub3d *data);
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
void			clear_texture_img(t_cub3d *data);

/*===== bonus part functions =================================================*/

/*----- Minimap -----*/
int				create_minimap_img(t_cub3d *data, t_minimap *mmap);
void			draw_mmap_player(t_cub3d *data);
void			draw_mmap_player_dir(t_cub3d *data);
void			draw_ray_mmap(t_cub3d *data, t_ray *ray);
void			draw_circle(t_cub3d *data, int xc, int yc, int r);
void			draw_scale(t_cub3d *data, int color, int size);

/*----- Mouse move -----*/
int				mousemove(int x, int y, t_cub3d *data);
int				mousescroll(int event, int x, int y, t_cub3d *data);

/*----- Doors -----*/
int				get_door_texture_paths(t_cub3d *data);
// void			store_doors_coordinates(t_cub3d *data);
void			switch_door_status(t_cub3d *data);
void			check_door_hit(t_cub3d *data, t_ray *ray);
// void			draw_door(t_cub3d *data, int x, t_ray *ray);
void			draw_door(t_cub3d *data, int x, t_ray *r, t_xpm_img *tex);
void			anim_open_door(t_cub3d *data);

#endif
