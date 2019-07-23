#pragma OPENCL EXTENSION cl_khr_byte_addressable_store : enable
__kernel void mandelbrot(
		const float zoom,
		const float offset_x,
		const float offset_y,
		const int   width,
		const int   height,
		const int   iterations,
		__global int         *result
)
{
	float	tmp;
	int		id;
	int		i;
	int		x;
	int		y;
	float 	zx;
	float	zy;
	float 	zx_start;
	float 	zy_start;

	i = 0;
	id = get_global_id(0);
	x = id % width;
	y = id / width;
	zx_start = 1.5 * (x - width  / 2) / (0.5 * zoom * width)  + offset_x;
	zy_start = 1.0 * (y - height / 2) / (0.5 * zoom * height) + offset_y;
	zx = zx_start;
	zy = zy_start;
	while (pow(zx, 2) + pow(zy, 2) < 4 && i < iterations)
	{
		tmp = pow(zx, 2) - pow(zy, 2) + zx_start;
		zy = 2.0 * zx * zy + zy_start;
		zx = tmp;
		i++;
	}
	result[id] = i;
}
