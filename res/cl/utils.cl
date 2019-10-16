#include "utils.hcl"

int	iteration_to_color(double iteration, double iteration_max, __global uchar4 *gradient, uint gradient_len)
{
	int hsv_[3];
    //	hsv_to_rgb(
    //		360 * iteration / iteration_max,
    //		255,
    //		iteration < iteration_max ? (float)iteration / iteration_max + 100: 0,
    //		hsv
    //	);
    if (iteration > iteration_max)
        return (0);

    iteration = iteration_max - iteration;
    uint i;
    uint a;
    uint b;
    double w;

    // Fit in [0, 100]
    w = iteration/iteration_max * 100;

    a = 0;
    b = 1;
    i = 0;
    while (i < gradient_len - 1)
    {
        if (w > gradient[b].w)
        {
            a++;
            b++;
        }
        else
            break;

        i++;
    }

    double alpha = (gradient[a].w - w) / (gradient[a].w - gradient[b].w);

    hsv_[0] = mix((double)gradient[a].x, (double)gradient[b].x, alpha);
    hsv_[1] = mix((double)gradient[a].y, (double)gradient[b].y, alpha);
    hsv_[2] = mix((double)gradient[a].z, (double)gradient[b].z, alpha);

//            printf("alpha: %lf\n", alpha);
    return ((((hsv_[0] << 8u) + hsv_[1]) << 8u) + hsv_[2]);
}
