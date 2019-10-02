
void hsv_to_rgb(int hue, float sat, float val, int rgb[3])
{
    float x;
    float m;
    float f_rgb[3];
    x = sat * val * (1 - fabs(fmod(hue / 60.0, 2.0) - 1));
    m = val - sat * val;
    if(hue >= 0 && hue < 60) {
        f_rgb[0] = sat * val;
        f_rgb[1] = x;
        f_rgb[2] = 0;
    }
    else if(hue >= 60 && hue < 120) {
        f_rgb[0] = x;
        f_rgb[1] = sat * val;
        f_rgb[2] = 0;
    }
    else if(hue >= 120 && hue < 180) {
        f_rgb[0] = 0;
        f_rgb[1] = sat * val;
        f_rgb[2] = x;
    }
    else if(hue >= 180 && hue < 240) {
        f_rgb[0] = 0;
        f_rgb[1] = x;
        f_rgb[2] = sat * val;
    }
    else if(hue >= 240 && hue < 300) {
        f_rgb[0] = x;
        f_rgb[1] = 0;
        f_rgb[2] = sat * val;
    }
    else {
        f_rgb[0] = sat * val;
        f_rgb[1] = 0;
        f_rgb[2] = x;
    }
    rgb[0] = (f_rgb[0] + m) * 255;
    rgb[1] = (f_rgb[1] + m) * 255;
    rgb[2] = (f_rgb[2] + m) * 255;
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
