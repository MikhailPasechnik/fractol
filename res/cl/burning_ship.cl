#include "complex.hcl"
#include "utils.hcl"

__kernel void burning_ship(
		const float		zoom,
		const float		mouse_x,
		const float		mouse_y,
		const double	offset_x,
		const double	offset_y,
		const int		width,
		const int		height,
		const int		iterations,
		uint			gradient_len,
		__global uchar4	*gradient,
		__global int	*result
)
{
	int			i;
	int			id;
	t_complex	c;
	t_complex	z;
	double2		point;
	double		temp;

	id = get_global_id(0);
	point.x = id % width - width  / 2;
	point.y = id / width - height / 2;
	point /= zoom;
	point.x += offset_x;
	point.y += offset_y;
	point.x *= -5.0 / ((double)width / 2);
	point.y *= 2.0 / ((double)height / 2);
	i = 0;
	c = (t_complex){point.x, point.y};
	z = c;
	while (c_abs(z).r < 4 && i < iterations)
	{
		temp = z.r * z.r - z.i * z.i + c.r;
		z.i = fabs(2 * z.r * z.i) + c.i;
		z.r = fabs(temp);
		i++;
	}
	result[id] = iteration_to_color(
		smooth_iteration(i, z.r, z.i), iterations, gradient, gradient_len
	);
}
