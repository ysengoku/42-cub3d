# 42-cub3d

## Structure

### Player
```c
#define FOV 60
#define M_PI 3.14159265358979323846

typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	
}				t_player;
```
```c
/* Exemple map */
111111
100101
101001
1100N1
111111
// Player is represented by N (north direction)
```

#### pos_x, pos_y
Player's initial map coordinates (not pixel coordinate). He must be placed at the center of cell.
```c
In the exemple,  
pos_x = 4.5, pos_y = 3.5
// Coordinate on the map is (4, 3)
```

#### dir_x, dir_y
Player's initial direction
- NORTH : dir_x = 0, dir_y = -1
- SOUTH : dir_x = 0, dir_y = 1
- EAST : dir_x = 1, dir_y = 0
- WEST : dir_x = -1, dir_y = 0
```c
In the exemple,  
dir_x = 0, dir_y = -1
```

#### plane_x, plane_y (Camera plane vector)
Caluculate plane vector
1. Convert FOV° in radian
  fov_radians = FOV * M_PI / 180.0
2. Calculate plane length
  plane_length = tan(fov_radians / 2)
3. Calculate plane vector
  plane_x = dir_y * plane_length
  plane_y = dir_x * plane_length
```c
In the example,
fov_rad = 60 * M_PI / 180 = 1.047198
plane_length = tan(fov_rad / 2) = 0.57735
plane_x = dir_y * plane_length = -1 * 0.57735 = -0.57735
plane_y = dir_x * plane_length = 0 * 0.57735 = 0
```
