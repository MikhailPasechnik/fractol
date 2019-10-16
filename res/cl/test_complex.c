#include "complex.hcl"

__kernel void	test_complex(void)
{
	t_complex a;
	t_complex b;
	t_complex c;
	a = (t_complex) {10, 2};
	b = (t_complex) {-3, -10};

	c = c_add(a, b);
	printf("(%f %f) + (%f %f) = (%f %f)\n",
		   a.r, a.i, b.r, b.i, c.r, c.i);


	printf("abs((%f %f)) = (%f %f)\n", c.r, c.i, c_abs(c).r, c_abs(c).i);
	c = c_sub(a, b);
	printf("(%f %f) - (%f %f) = (%f %f)\n",
		   a.r, a.i, b.r, b.i, c.r, c.i);

	c = c_div(a, b);
	printf("(%f %f) / (%f %f) = (%f %f)\n",
		   a.r, a.i, b.r, b.i, c.r, c.i);

	c = c_mul(a, b);
	printf("(%f %f) * (%f %f) = (%f %f)\n",
		   a.r, a.i, b.r, b.i, c.r, c.i);
}