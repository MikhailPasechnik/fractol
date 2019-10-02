#include "fractol.h"

void	on_mouse_move(SDL_Event *event, t_app *app, int *changed)
{
	ft_putendl("on_mouse_move");
}

void	on_window_size_change(SDL_Event *event, t_app *app, int *changed)
{
	ft_putendl("on_window_size_change");
	SDL_GetWindowSize(app->win, &app->win_w, &app->win_w);
	*changed = 1;
}

void	on_mouse_wheel(SDL_Event *event, t_app *app, int *changed)
{
	ft_putendl("on_mouse_wheel");
}
