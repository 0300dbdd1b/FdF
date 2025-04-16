
#include "fdf.h"
#include <math.h>

#define SCALE 20

t_point	project_iso(t_fdf *fdf, t_point p)
{
	t_point projected;

	projected.x = (p.x - p.y) * cos(0.523599) * fdf->zoom + fdf->x_offset;
	projected.y = (p.x + p.y) * sin(0.523599) * fdf->zoom - p.z * fdf->z_scale + fdf->y_offset;
	return (projected);
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
			if (x + 1 < fdf->map_width)
				draw_line(fdf, fdf->points[y][x], fdf->points[y][x + 1], 0xFFFFFF);
			if (y + 1 < fdf->map_height)
				draw_line(fdf, fdf->points[y][x], fdf->points[y + 1][x], 0xFFFFFF);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(fdf->mlx, fdf->window, fdf->img, 0, 0);
}
