#include "complex.h"
#include "utils.h"

__kernel void julia(
		const float zoom,
		const float mouse_x,
		const float mouse_y,
		const float offset_x,
		const float offset_y,
		const int   width,
		const int   height,
		const int   iterations,
		__global int         *result
)
{
	int 		id;
	int 		x;
	int 		y;
	int 		i;
	t_complex 	c;
	t_complex 	z;

	id = get_global_id(0);
	x = id % width;
	y = id / width;
	i = 0;
	c = (t_complex){mouse_x / 200.0, mouse_y / 200.0};
	z = (t_complex){
			1.5 * (x - width  / 2) / (0.5 * zoom * width)  + offset_x,
			1 * (y - height / 2) / (0.5 * zoom * height) + offset_y
	};
	while (c_abs(z).r <= 2 && i < iterations)
	{
		z = c_add(c_mul(z, z), c);
		i++;
	}
	result[id] = iteration_to_color(i, iterations);
}
