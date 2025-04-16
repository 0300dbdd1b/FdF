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
	int			window_height;
	int			window_width;
	t_mlx		mlx;
	t_window	window;
	t_point		**points;

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


#if defined(__APPLE__)
typedef enum e_KEYCODE
{
	KEY_LEFT	= 123,
	KEY_RIGHT	= 124,
	KEY_DOWN	= 125,
	KEY_UP		= 126,
	KEY_PLUS	= 69,
	KEY_MINUS	= 78,
	KEY_O		= 31,
	KEY_I		= 34,
}	t_KEYCODE;
#endif


#endif
