#include "fdf.h"
#include "libs/minilibx-macos/mlx.h"


int	init_fdf(t_fdf *fdf)
{
	fdf->mlx = mlx_init();
	if (!fdf->mlx)
		return (write(2, "MLX init error\n", 15), 1);
	fdf->window = mlx_new_window(fdf->mlx, 1000, 1000, "FdF");
	if (!fdf->window)
		return (write(2, "Window error\n", 13), 1);
	fdf->window_width = 1000;
	fdf->window_height = 1000;
	fdf->use_color = 1;
	fdf->z_max = INT_MIN;
	fdf->z_min = INT_MAX;
	fdf->x_angle = 0;
	fdf->y_angle = 0;
	fdf->z_angle = 0;
	fdf->zoom	= 10;
	fdf->z_scale = 0.1;
	fdf->x_offset = fdf->window_width / 2;
	fdf->y_offset = fdf->window_height / 2;
	fdf->img = mlx_new_image(fdf->mlx, fdf->window_width, fdf->window_height);
	fdf->img_addr = mlx_get_data_addr(fdf->img, &fdf->bpp, &fdf->line_len, &fdf->endian);
	mlx_key_hook(fdf->window, handle_key, fdf);
	return (1);
}

int	main(int argc, char **argv)
{
	t_fdf	*fdf;
	
	fdf = malloc(sizeof(t_fdf));
	init_fdf(fdf);
	if (argc != 2)
		return (1);
	parse_map(fdf, argv[1]);
	if (!fdf)
		return (write(2, "Map error\n", 10), 1);
	draw_map(fdf);
	mlx_loop(fdf->mlx);
	return (0);
}


