#ifndef FDF_H
# define FDF_H

# if defined(__APPLE__)
	#include "libs/minilibx-macos/mlx.h"
# elif defined(__linux__)
	#include "libs/minilibx-linux/mlx.h"
# else
	#error "Unsupported OS"
# endif

# include "libs/libft/libft.h"
# include <limits.h>
# include <stdio.h>
typedef void*	t_mlx;
typedef void*	t_window;
typedef void*	t_image;

typedef struct s_point
{
	int	x;
	int	y;
	int	z;
	int	color;
}	t_point;

typedef struct s_fdf
{
	int			map_height;
	int			map_width;
	int			z_min;
	int			z_max;
	int			window_height;
	int			window_width;
	t_mlx		mlx;
	t_window	window;
	t_point		**points;

	int			use_color;
	int			zoom;
	int			x_offset;
	int			y_offset;
	float		z_scale;

	float		x_angle;
	float		y_angle;
	float		z_angle;

	t_image		img;
	char		*img_addr;
	int			bpp;
	int			line_len;
	int			endian;
}	t_fdf;

int		parse_map(t_fdf *fdf, const char *filename);
void	draw_map(t_fdf *fdf);
int		handle_key(int keycode, t_fdf *fdf);

int	get_color(t_fdf *fdf, int z);

#if defined(__APPLE__)
typedef enum e_KEYCODE
{
	// Directional arrows
	KEY_LEFT     = 123,
	KEY_RIGHT    = 124,
	KEY_DOWN     = 125,
	KEY_UP       = 126,

	// Numpad keys
	KEY_PLUS     = 69,
	KEY_MINUS    = 78,

	// Letters (A–Z)
	KEY_A        = 0,
	KEY_B        = 11,
	KEY_C        = 8,
	KEY_D        = 2,
	KEY_E        = 14,
	KEY_F        = 3,
	KEY_G        = 5,
	KEY_H        = 4,
	KEY_I        = 34,
	KEY_J        = 38,
	KEY_K        = 40,
	KEY_L        = 37,
	KEY_M        = 46,
	KEY_N        = 45,
	KEY_O        = 31,
	KEY_P        = 35,
	KEY_Q        = 12,
	KEY_R        = 15,
	KEY_S        = 1,
	KEY_T        = 17,
	KEY_U        = 32,
	KEY_V        = 9,
	KEY_W        = 13,
	KEY_X        = 7,
	KEY_Y        = 16,
	KEY_Z        = 6,

	// Numbers (top row, not numpad)
	KEY_1        = 18,
	KEY_2        = 19,
	KEY_3        = 20,
	KEY_4        = 21,
	KEY_5        = 23,
	KEY_6        = 22,
	KEY_7        = 26,
	KEY_8        = 28,
	KEY_9        = 25,
	KEY_0        = 29,

	// Special
	KEY_ESC      = 53,
	KEY_SPACE    = 49,
	KEY_TAB      = 48,
	KEY_RETURN   = 36,
	KEY_DELETE   = 51,
	KEY_SHIFT_L  = 257,
	KEY_SHIFT_R  = 258,
	KEY_CTRL     = 256,
}	t_KEYCODE;
#endif


#endif
