#include "cub3d.h"

void	projection_sprite(t_game *game, t_sprite *sprite)
{
	(void)game;
	(void)sprite;

}

void	render_sprite(t_game *game)
{
	t_list *lst_p;
	t_sprite *sprite;

	sort_items(game->cub.items);
	lst_p = game->cub.items;
	while (lst_p != NULL)
	{
		sprite = lst_p->content;
		projection_sprite(game, sprite);
		lst_p = lst_p->next;
	}


	test_print_items(*game);
}
