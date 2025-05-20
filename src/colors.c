#include "fdf.h"


int	interpolate_channel(int start, int end, double t)
{
	return (int)(start + (end - start) * t);
}

int	interpolate_color(int color1, int color2, double t)
{
	int r1 = (color1 >> 16) & 0xFF;
	int g1 = (color1 >> 8) & 0xFF;
	int b1 = color1 & 0xFF;

	int r2 = (color2 >> 16) & 0xFF;
	int g2 = (color2 >> 8) & 0xFF;
	int b2 = color2 & 0xFF;

	int r = interpolate_channel(r1, r2, t);
	int g = interpolate_channel(g1, g2, t);
	int b = interpolate_channel(b1, b2, t);

	return ((r << 16) | (g << 8) | b);
}

int	get_color(t_fdf *fdf, int z)
{
	if (!fdf->use_color || fdf->z_max == fdf->z_min)
		return 0xFFFFFF;

	double percent = (double)(z - fdf->z_min) / (fdf->z_max - fdf->z_min);

	if (percent < 0.0) percent = 0.0;
	if (percent > 1.0) percent = 1.0;

	if (percent <= 0.1)
		return interpolate_color(0x444444, 0x5A3A22, percent / 0.1); // gris → brun
	else if (percent <= 0.4)
		return interpolate_color(0x5A3A22, 0x1E90FF, (percent - 0.1) / 0.3); // brun → bleu
	else if (percent <= 0.6)
		return interpolate_color(0x1E90FF, 0x228B22, (percent - 0.4) / 0.2); // bleu → vert foncé
	else if (percent <= 0.8)
		return interpolate_color(0x228B22, 0xADFF2F, (percent - 0.6) / 0.2); // vert foncé → vert clair
	else
		return interpolate_color(0xADFF2F, 0xFFFFFF, (percent - 0.8) / 0.2); // vert clair → blanc
}

