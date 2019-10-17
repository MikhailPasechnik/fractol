#include "fractol.h"

void	gradient_list_reverse(t_gradient **list)
{
	t_gradient	*third;
	t_gradient	*second;
	t_gradient	*first;

	if (!list || !(first = *list) || !(first->next))
		return ;
	second = first->next;
	third = second->next;
	first->next = 0;
	second->next = first;
	while (third)
	{
		first = second;
		second = third;
		third = third->next;
		second->next = first;
	}
	*list = second;
}

void	*free_gradient(t_gradient **g)
{
	if (!g)
		return (NULL);
	free((*g)->data);
	free(*g);
	*g = NULL;
	return (NULL);
}

void	*free_gradient_list(t_gradient **list)
{
	t_gradient	*next;

	while (*list)
	{
		next = (*list)->next;
		free_gradient(list);
		*list = next;
	}
	return (NULL);
}
