#include "fractol.h"

int     on_mouse_move(int x, int y, t_app *app)
{
    app->ren.mouse_x = (app->win_w / 2.0 - x);;
    app->ren.mouse_y = (app->win_h / 2.0 - y);;
	app_render(app);
	return (1);
}

int     on_mouse_wheel(int x, int y, t_app *app)
{
    app->ren.zoom += -(float)y * app->ren.zoom / 10.0f;
    app->ren.zoom = app->ren.zoom > 0 ? app->ren.zoom : 1;
    app->changed = 1;
    return (1);
}

int     on_key_press(int key, t_app *app)
{
    int update;

    update = 0;
	if (key == KEY_ESC)
	{
		app_finish(app);
		free(app->mlx);
		exit(0);
	}
	else if (key == KEY_PLUS && (update = 1))
		app->ren.iterations += 1;
	else if (key == KEY_MINUS && app->ren.iterations > 0  && (update = 1))
		app->ren.iterations -= 1;
	else if ((key == KEY_LEFT || key == KEY_RIGHT) && (update = 1))
		app->ren.offset_x += (key == KEY_RIGHT ? 10.0l : -10.0l) / app->ren.zoom;
	else if ((key == KEY_DOWN || key == KEY_UP) && (update = 1))
		app->ren.offset_y += (key == KEY_UP ? 10 : -10.0l) / app->ren.zoom;
    update ? app_render(app) : 0;
    return (1);
}
