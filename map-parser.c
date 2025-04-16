#include "fdf.h"

static int	count_words(char *line)
{
	int		i = 0;
	char	**split;
	int		count = 0;

	if (!line)
		return (0);
	split = ft_split(line, ' ');
	if (!split)
		return (0);
	while (split[count])
		count++;
	while (split[i])
		free(split[i++]);
	free(split);
	return (count);
}

static int	scan_dimensions(const char *filename, int *width, int *height)
{
	int		fd;
	char	*line;
	int		w;
	int		max_width = 0;
	int		h = 0;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (0);
	while ((line = get_next_line(fd)))
	{
		w = count_words(line);
		if (w > max_width)
			max_width = w;
		h++;
		free(line);
	}
	close(fd);
	*width = max_width;
	*height = h;
	return (1);
}

static void	fill_points(t_fdf *fdf, t_point *row, char *line, int y, int width)
{
	char	**split = ft_split(line, ' ');
	int		x = 0;

	while (split[x] && x < width)
	{
		row[x].x = x;
		row[x].y = y;
		row[x].z = ft_atoi(split[x]);
		if (row[x].z < fdf->z_min)
			fdf->z_min = row[x].z;
		if (row[x].z > fdf->z_max)
			fdf->z_max = row[x].z;

		free(split[x]);
		x++;
	}
	while (x < width)
	{
		row[x].x = x;
		row[x].y = y;
		row[x].z = 0;
		x++;
	}
	free(split);
}

static void	free_rows(t_point **rows, int filled)
{
	int	i = 0;

	while (i < filled)
		free(rows[i++]);
	free(rows);
}

int	parse_map(t_fdf *fdf, const char *filename)
{
	char	*line;
	int		fd;
	int		y;

	if (!scan_dimensions(filename, &fdf->map_width, &fdf->map_height))
		return (0);
	fdf->points = malloc(sizeof(t_point *) * fdf->map_height);
	if (!fdf->points)
		return (0);

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (free(fdf->points), 0);
	y = 0;
	while ((line = get_next_line(fd)))
	{
		fdf->points[y] = malloc(sizeof(t_point) * fdf->map_width);
		if (!fdf->points[y])
			return (free(line), free_rows(fdf->points, y), 0);
		fill_points(fdf, fdf->points[y], line, y, fdf->map_width);
		free(line);
		y++;
	}
	close(fd);
	return (1);
}

