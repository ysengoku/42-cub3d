# 42-cub3d

## Usage
```bash
# Mandatory part
> make
> ./cub3D <path to map in .xpm format>

# Bonus part
> make bonus
> ./cub3D_bonus <path to map in .xpm format>
```

## Structures

### Data
```c
typedef struct s_cub3d
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_imgdata	img;
	t_map		map;
	t_player	player;
	int		ceiling_color;
	int		floor_color;
	t_xpm_img	wall[4]; // wall textures
	int		key_pressed_left; // flag for key event (press & release)
	int		key_pressed_right; // flag for key event (press & release)
	int		key_pressed_w; // flag for key event (press & release)
	int		key_pressed_s; // flag for key event (press & release)
	int		key_pressed_a; // flag for key event (press & release)
	int		key_pressed_d; // flag for key event (press & release)
	t_minimap	mmap;
}				t_cub3d;
```

### Map
```c
typedef struct s_map
{
	char			**data_map;
	char			**map; // will be used to check wall collision
	char			**dup_map;
	char			player;
	int			f_rgb[3]; // floor color
	int			c_rgb[3]; // ceiling color
	int			map_len_x; // max length of x-axis of the map
	int			map_len_y; // max length of y-axis of the map
	int			pos_x; // player's initial position
	int			pos_y; // player's initial position
	enum e_direction	p_dir; // player's initial direction
}				t_map;
```
```c
/* Exemple map */
111111
100101
101001
1100N1
111111

// Player is represented by N : cordinates (4, 3), face to north
// N = North (90°)
// E = East (270°)
// S = South (0°)
// W = West (180°)
```

### Player
```c
#define FOV 60
#define M_PI 3.14159265358979323846

ypedef struct s_player
{
	double	fov; // FOV in radians (calculate with FOV° * M_PI / 180.0)
	double	pos_x; // X coordinate on the map
	double	pos_y; // Y coordinate on the map
	double	dir; // direction in degree
	double	dir_x; // direction vector
	double	dir_y; // direction vector
	double	plane_length;
	double	plane_x;
	double	plane_y;
	int	moved; // Flag to signal player's movement

}		t_player;
```

#### Direction vector (dir_x, dir_y)

```c
t_player	player;
double 		dir_rad;

dir_rad = player.dir * M_PI / 180;
player.dir_x = cos(dir_rad);
player.dir_y = -sin(dir_rad);

// In the exemple,  
// dir_x = 0, dir_y = -1
```

#### Camera plane length & vector (plane_length, plane_x, plane_y)
1. Calculate plane length  
  `plane_length = tan(fov_radians / 2)`
2. Calculate plane vector   
  `plane_x = dir_y * plane_length`   
  `plane_y = dir_x * plane_length`
```c
// In the example,
plane_length = tan(fov / 2) = 1.000000

// The plane_x and plane_y for the initial player's position (dir_x = 0, dir_y = -1) is:
plane_x = dir_y * plane_length = -1 * 1.000000 = -1.000000
plane_y = dir_x * plane_length = 0 * 1.000000 = 0
```

## References
### Tutorials
* [Lode's Computer Graphics Tutorial - Raycasting](https://lodev.org/cgtutor/raycasting.html)
* [cub3d - HackMD](https://hackmd.io/@nszl/H1LXByIE2)
* [Cub3D Tutorial - Using angles](https://medium.com/@afatir.ahmedfatir/cub3d-tutorial-af5dd31d2fcf)
* [42 Docs - cub3d](https://harm-smits.github.io/42docs/projects/cub3d)

### Videos

### Turorial in Japanese
* [42Tokyo C言語で一人称視点のゲームを作った](https://qiita.com/susasaki/items/c74a228d7ddd48b818bd)
