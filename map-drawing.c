
#include "fdf.h"
#include <math.h>

#define SCALE 20






t_point project_iso(t_fdf *fdf, t_point p)
{
	t_point rotated;
	t_point projected;

	double center_x = fdf->map_width / 2.0;
	double center_y = fdf->map_height / 2.0;
	double center_z = 0;

	double x = p.x - center_x;
	double y = p.y - center_y;
	double z = (p.z - center_z) * fdf->z_scale;

	double rx = fdf->x_angle;
	double ry = fdf->y_angle;
	double rz = fdf->z_angle;

	// Rotation around X
	double y1 = y * cos(rx) - z * sin(rx);
	double z1 = y * sin(rx) + z * cos(rx);

	// Rotation around Y
	double x2 = x * cos(ry) + z1 * sin(ry);
	double z2 = -x * sin(ry) + z1 * cos(ry);

	// Rotation around Z
	double x3 = x2 * cos(rz) - y1 * sin(rz);
	double y3 = x2 * sin(rz) + y1 * cos(rz);

	// Apply zoom
	double zoomed_x = x3 * fdf->zoom;
	double zoomed_y = y3 * fdf->zoom;
	double zoomed_z = z2 * fdf->zoom; // (optionnel: tu peux garder z2 directement)

	// Isometric projection (30°)
	double angle = 0.523599;
	projected.x = (zoomed_x - zoomed_y) * cos(angle) + fdf->x_offset;
	projected.y = (zoomed_x + zoomed_y) * sin(angle) - zoomed_z + fdf->y_offset;

	return projected;
}




void	put_pixel(t_fdf *fdf, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= 1920 || y >= 1080)
		return ;
	dst = fdf->img_addr + (y * fdf->line_len + x * (fdf->bpp / 8));
	*(unsigned int *)dst = color;
}

void	draw_line(t_fdf *fdf, t_point a, t_point b, int color)
{
	int		dx;
	int		dy;
	int		steps;
	float	x_inc;
	float	y_inc;
	float	x;
	float	y;

	a = project_iso(fdf, a);
	b = project_iso(fdf, b);
	dx = b.x - a.x;
	dy = b.y - a.y;
	steps = fmax(abs(dx), abs(dy));
	x_inc = dx / (float)steps;
	y_inc = dy / (float)steps;
	x = a.x;
	y = a.y;
	while (steps--)
	{
		/* mlx_pixel_put(fdf->mlx, fdf->window, (int)x, (int)y, color); */
		put_pixel(fdf, (int)x, (int)y, color);
		x += x_inc;
		y += y_inc;
	}
}

void	draw_map(t_fdf *fdf)
{
	int	x;
	int	y;
	int color;

	if (fdf->img)
		mlx_destroy_image(fdf->mlx, fdf->img);

	fdf->img = mlx_new_image(fdf->mlx, fdf->window_width, fdf->window_height);
	fdf->img_addr = mlx_get_data_addr(fdf->img, &fdf->bpp, &fdf->line_len, &fdf->endian);
	y = 0;
	while (y < fdf->map_height)
	{
		x = 0;
		while (x < fdf->map_width)
		{
			color = get_color(fdf, fdf->points[y][x].z);
			if (x + 1 < fdf->map_width)
				draw_line(fdf, fdf->points[y][x], fdf->points[y][x + 1], color);
			if (y + 1 < fdf->map_height)
				draw_line(fdf, fdf->points[y][x], fdf->points[y + 1][x], color);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(fdf->mlx, fdf->window, fdf->img, 0, 0);
}
