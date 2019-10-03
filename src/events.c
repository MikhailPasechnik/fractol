#include "fractol.h"

void	on_mouse_move(SDL_MouseMotionEvent *event, t_app *app, int *changed)
{
    app->ren.mouse_x = (app->win_w / 2.0 - event->x);
    app->ren.mouse_y = (app->win_h / 2.0 - event->y) ;
	*changed = 1;
}

void	on_window_size_change(SDL_WindowEvent *event, t_app *app, int *changed)
{
	(void)event;
	SDL_GetWindowSize(app->win, &app->win_w, &app->win_h);
	*changed = 1;
}

void	on_mouse_wheel(SDL_MouseWheelEvent *event, t_app *app, int *changed)
{
    app->ren.zoom += event->y;
    *changed = 1;
}

void	on_key_press(SDL_KeyboardEvent *event, t_app *app, int *changed)
{
	(void)changed;
	if (event->keysym.sym == SDLK_ESCAPE)
		app->quit = 1;
}
