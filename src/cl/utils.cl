#include "utils.h"

void hsv_to_rgb(int hue, float sat, float val, int rgb[3])
{
	float   x;
	float   m;
	t_frgb  frgb;

	x = sat * val * (1 - fabs(fmod(hue / 60.0, 2.0) - 1));
	m = val - sat * val;
	if(hue >= 0 && hue < 60)
		frgb = (t_frgb){sat * val, x, 0};
	else if(hue >= 60 && hue < 120)
		frgb = (t_frgb){x, sat * val, 0};
	else if(hue >= 120 && hue < 180)
		frgb = (t_frgb){0, sat * val, x};
	else if(hue >= 180 && hue < 240)
		frgb = (t_frgb){0, x, sat * val};
	else if(hue >= 240 && hue < 300)
		frgb = (t_frgb){x, 0, sat * val};
	else
		frgb = (t_frgb){sat * val, 0, x};
	rgb[0] = (frgb.r + m) * 255;
	rgb[1] = (frgb.g + m) * 255;
	rgb[2] = (frgb.b + m) * 255;
}


int	iteration_to_color(int iteration, int iteration_max)
{
	int hsv[3];
	hsv_to_rgb(
		255 * iteration / iteration_max,
		255,
		iteration < iteration_max ? 255 : 0,
		hsv
	);
	return ((((hsv[2] << 8u) + hsv[1]) << 8u) + hsv[0]);
}
