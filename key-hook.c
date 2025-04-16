
#include "fdf.h"
#include <stdlib.h> // for exit()
int	handle_key(int keycode, t_fdf *fdf)
{

	ft_printf("Key pressed: %d\n", keycode);
	if (keycode == 53 || keycode == 65307) // ESC
		exit(0);
	// Arrow keys for translation
	if (keycode == KEY_LEFT)
		fdf->x_offset -= 20;
	if (keycode == KEY_RIGHT)
		fdf->x_offset += 20;
	if (keycode == KEY_UP)
		fdf->y_offset -= 20;
	if (keycode == KEY_DOWN)
		fdf->y_offset += 20;

	// Zoom in/out
	if (keycode == KEY_PLUS || keycode == KEY_I)
		fdf->zoom += 1;
	if (keycode == KEY_MINUS || keycode == KEY_O)
		fdf->zoom -= 1;

	// Altitude scale
	if (keycode == 13 || keycode == 119) // W
		fdf->z_scale += 1;
	if (keycode == 1 || keycode == 115) // S
		fdf->z_scale -= 1;

	mlx_clear_window(fdf->mlx, fdf->window);
	draw_map(fdf);
	return (0);
}
