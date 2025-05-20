
#include "fdf.h"
#include <stdlib.h> // for exit()

int	handle_key(int keycode, t_fdf *fdf)
{
	ft_printf("Key pressed: %d\n", keycode);
	if (keycode == KEY_ESC)
		exit(0);

	if (keycode == KEY_E)
		fdf->use_color = !fdf->use_color;
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
	if (keycode == KEY_W)
		fdf->z_scale += 0.1;
	if (keycode == KEY_S)
		fdf->z_scale -= 0.1;

	// Rotation
	#define ROTATE_STEP 0.05

	// Pitch (X-axis)
	if (keycode == KEY_L)
		fdf->x_angle += ROTATE_STEP;
	if (keycode == KEY_H)
		fdf->x_angle -= ROTATE_STEP;

	// Yaw (Y-axis)
	if (keycode == KEY_J)
		fdf->y_angle -= ROTATE_STEP;
	if (keycode == KEY_K)
		fdf->y_angle += ROTATE_STEP;

	// Roll (Z-axis)
	if (keycode == KEY_V)
		fdf->z_angle += ROTATE_STEP;
	if (keycode == KEY_C)
		fdf->z_angle -= ROTATE_STEP;

	if (keycode == KEY_1)
		fdf->projection_type = PROJECTION_ISO;
	else if (keycode == KEY_2)
		fdf->projection_type = PROJECTION_PARALLEL;
	else if (keycode == KEY_3)
		fdf->projection_type = PROJECTION_CABINET;
	else if (keycode == KEY_4)
		fdf->projection_type = PROJECTION_PERSPECTIVE;

		mlx_clear_window(fdf->mlx, fdf->window);
	draw_map(fdf);
	return (0);
}

