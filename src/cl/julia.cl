#pragma OPENCL EXTENSION cl_khr_byte_addressable_store : enable

__kernel void julia(
		const float c_x,    /// -0.7
		const float c_y,    /// 0.27015
		const float zoom,
		const float offset_x,
		const float offset_y,
		const int 	width,
		const int 	height,
		const int 	iterations,
		__global int *result
)
{
	float	tmp;
	int		id;
	int		i;
	int		x;
	int		y;
	float 	zx;
	float	zy;

	i = 0;
	id = get_global_id(0);
	x = id % width;
	y = id / width;
	zx = 1.5 * (x - width / 2) / (0.5 * zoom * width) + offset_x;
	zy = 1.0 * (y - height / 2) / (0.5 * zoom * height) + offset_y;
	while (pow(zx, 2) + pow(zy, 2) < 4 && i < iterations)
	{
		tmp = pow(zx, 2) - pow(zy, 2) + c_x;
		zy = 2.0 * zx * zy + c_y;
		zx = tmp;
		i++;
	}
	result[id] = i;
}
