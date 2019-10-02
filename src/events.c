#include "fractol.h"

void	on_mouse_move(SDL_Event *event, t_app *app, int *changed)
{
    app->ren.mouse_x = (app->win_w / 2.0 - event->motion.x) / 200.0;
    app->ren.mouse_y = (app->win_h / 2.0 - event->motion.y) / 200.0;
    *changed = 1;
}

void	on_window_size_change(SDL_Event *event, t_app *app, int *changed)
{
	ft_putendl("on_window_size_change");
	SDL_GetWindowSize(app->win, &app->win_w, &app->win_h);
	*changed = 1;
}

void	on_mouse_wheel(SDL_Event *event, t_app *app, int *changed)
{
    app->ren.zoom += event->wheel.y;
    *changed = 1;
}
