#include "fractol.h"

void	on_mouse_move(SDL_MouseMotionEvent *event, t_app *app, int *changed)
{
    app->ren.mouse_x = (app->win_w / 2.0 - event->x);;
    app->ren.mouse_y = (app->win_h / 2.0 - event->y);;
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
    app->ren.zoom += -(float)event->y * app->ren.zoom / 10;
    app->ren.zoom = app->ren.zoom > 0 ? app->ren.zoom : 1;
    *changed = 1;
}

void	on_key_press(SDL_KeyboardEvent *event, t_app *app, int *changed)
{
	if (event->keysym.sym == SDLK_ESCAPE)
	{
		app->quit = 1;
		return ;
	}
	else if (event->keysym.sym == SDLK_1)
		app->ren.iterations += 1;
	else if (event->keysym.sym == SDLK_0 && app->ren.iterations > 100)
		app->ren.iterations -= 1;
	else if (event->keysym.sym == SDLK_LEFT || event->keysym.sym == SDLK_RIGHT)
		app->ren.offset_x += (double)(event->keysym.sym == SDLK_RIGHT ? 10 : -10)
		        / app->ren.zoom;
	else if (event->keysym.sym == SDLK_DOWN || event->keysym.sym == SDLK_UP)
		app->ren.offset_y += (double)(event->keysym.sym == SDLK_DOWN ? 10 : -10)
		        / app->ren.zoom;
	*changed = 1;
}
