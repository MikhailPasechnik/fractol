#include "fractol.h"

int     on_mouse_move(int x, int y, t_app *app)
{
	if (app->animation_callback)
		return (1);
	app->ren.mouse_x = (app->win_w / 2.0 - x);;
	app->ren.mouse_y = (app->win_h / 2.0 - y);;
	app_render(app);
	return (1);
}

int     on_mouse_wheel(int btn, int x, int y, t_app *app)
{
	if (!(btn == 4 || btn == 5))
		return (1);
	app->ren.zoom += (btn == 4 ? 1.0 : -1.0) * 4.0 * app->ren.zoom / 10.0;
	app->ren.zoom = app->ren.zoom > 0 ? app->ren.zoom : 1;
	app_render(app);
	return (1);
}

static int		on_key_press1(int key, t_app *app, int *update)
{
	(void)update;
	if (key == KEY_0)
		app->animation_callback = NULL;
	else if (key == KEY_1)
		app->animation_callback = julia_animation_callback;
	else if (key == KEY_2)
		app->animation_callback = julia_animation_callback1;
	else if (key == KEY_3)
		app->animation_callback = julia_animation_callback2;
	return (1);
}

int     on_key_press(int key, t_app *app)
{
	int update;

	update = 0;
	if (key == KEY_ESC)
		app_finish(app);
	else if (key == KEY_PLUS || (key == KEY_MINUS && app->ren.iterations > 0))
	{
		app->ren.iterations += key == KEY_PLUS ? 1 : -1;
		update = 1;
	}
	else if (key == KEY_LEFT || key == KEY_RIGHT)
	{
		app->ren.offset_x += (key == KEY_RIGHT ? 10.0l : -10.0l) / app->ren.zoom;
		update = 1;
	}
	else if (key == KEY_DOWN || key == KEY_UP)
	{
		app->ren.offset_y += (key == KEY_UP ? 10 : -10.0l) / app->ren.zoom;
		update = 1;
	}
	on_key_press1(key, app, &update);
	if (update)
		app_render(app);
	return (1);
}
