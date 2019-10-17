#include "utils.hcl"

double				smooth_iteration(double iterations, double r, double i)
{
	double	modulus;

	modulus = sqrt(r * r + i * i);
	return (iterations + 1 - (log(log(modulus))) / log (2.0));
}

static inline void	get_gradient_range(double pos, __global uchar4 *gradient, uint gradient_len, uint *a, uint *b)
{
	uint	i;

	*a = 0;
	*b = 1;
	i = 0;
	while (i < gradient_len - 1)
	{
		if (pos > gradient[*b].w)
		{
			(*a)++;
			(*b)++;
		}
		else
			break;
		i++;
	}
}

int					iteration_to_color(double iteration, double iteration_max,
			__global uchar4 *gradient, uint gradient_len)
{
	int			rgb[3];
	uint		a;
	uint		b;
	double		alpha;

	if (iteration > iteration_max)
		return (0);
	iteration = iteration_max - iteration;
	iteration = iteration / iteration_max * 100;
	get_gradient_range(iteration, gradient, gradient_len, &a, &b);
	alpha = (gradient[a].w - iteration) / (gradient[a].w - gradient[b].w);
	rgb[0] = mix((double)gradient[a].x, (double)gradient[b].x, alpha);
	rgb[1] = mix((double)gradient[a].y, (double)gradient[b].y, alpha);
	rgb[2] = mix((double)gradient[a].z, (double)gradient[b].z, alpha);
	return ((((rgb[0] << 8u) + rgb[1]) << 8u) + rgb[2]);
}
