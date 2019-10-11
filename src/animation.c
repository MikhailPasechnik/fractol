#include "fractol.h"
#include <sys/time.h>

static long long current_timestamp() {
    struct timeval te;
    gettimeofday(&te, NULL);
    return (te.tv_sec * 1000LL + te.tv_usec / 1000);
}

int animation_loop_callback(t_app *app)
{
    if (!app->animation_callback)
        return (1);
    if (!app->time)
    {
        app->time = current_timestamp();
        return (1);
    }
    if (current_timestamp() - app->time < 25)
        return (1);
    app->animation_callback(app);
    return (1);
}

void julia_animation_callback(t_app  *app)
{
    app->ren.mouse_y = (sin((double)app->time / 11000)) * 250;
    app->ren.mouse_x = (cos((double)app->time / 6000)) * 250;
    app->time = current_timestamp();
    app_render(app);
}
