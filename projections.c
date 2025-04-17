#include "fdf.h"
#include <math.h>

static void apply_rotations(double *x, double *y, double *z, t_fdf *fdf)
{
    double y1, z1, x2, z2, x3, y3;

    y1 = *y * cos(fdf->x_angle) - *z * sin(fdf->x_angle);
    z1 = *y * sin(fdf->x_angle) + *z * cos(fdf->x_angle);
    x2 = *x * cos(fdf->y_angle) + z1 * sin(fdf->y_angle);
    z2 = -*x * sin(fdf->y_angle) + z1 * cos(fdf->y_angle);
    x3 = x2 * cos(fdf->z_angle) - y1 * sin(fdf->z_angle);
    y3 = x2 * sin(fdf->z_angle) + y1 * cos(fdf->z_angle);
    *x = x3;
    *y = y3;
    *z = z2;
}

static t_point project_iso(t_fdf *fdf, double x, double y, double z)
{
    t_point proj;
    double angle = 0.523599; // 30°

    proj.x = (x - y) * cos(angle) + fdf->x_offset;
    proj.y = (x + y) * sin(angle) - z + fdf->y_offset;
    return proj;
}

static t_point project_parallel(t_fdf *fdf, double x, double y, double z)
{
    t_point proj;

    proj.x = x + fdf->x_offset;
    proj.y = y - z + fdf->y_offset;
    return proj;
}

static t_point project_cabinet(t_fdf *fdf, double x, double y, double z)
{
    t_point proj;
    double angle = 0.523599; // 30°

    proj.x = x + z * cos(angle) * 0.5 + fdf->x_offset;
    proj.y = y - z * sin(angle) * 0.5 + fdf->y_offset;
    return proj;
}

static t_point project_perspective(t_fdf *fdf, double x, double y, double z)
{
    t_point proj;
    double distance = 500.0;
    double factor = distance / (distance + z);

    proj.x = x * factor + fdf->x_offset;
    proj.y = y * factor + fdf->y_offset;
    return proj;
}

static t_point project_conic(t_fdf *fdf, double x, double y, double z)
{
    t_point proj;
    double r = sqrt(x * x + y * y);
    double theta = atan2(y, x);

    proj.x = r * cos(theta * 0.5) + fdf->x_offset;
    proj.y = r * sin(theta * 0.5) - z + fdf->y_offset;
    return proj;
}

t_point project_point(t_fdf *fdf, t_point p)
{
    double x, y, z;

    x = p.x - fdf->map_width / 2.0;
    y = p.y - fdf->map_height / 2.0;
    z = p.z * fdf->z_scale;
    apply_rotations(&x, &y, &z, fdf);
    x *= fdf->zoom;
    y *= fdf->zoom;
    z *= fdf->zoom;
    if (fdf->projection_type == PROJECTION_ISO)
        return project_iso(fdf, x, y, z);
    if (fdf->projection_type == PROJECTION_PARALLEL)
        return project_parallel(fdf, x, y, z);
    if (fdf->projection_type == PROJECTION_CABINET)
        return project_cabinet(fdf, x, y, z);
    if (fdf->projection_type == PROJECTION_PERSPECTIVE)
        return project_perspective(fdf, x, y, z);
    return project_conic(fdf, x, y, z);
}

