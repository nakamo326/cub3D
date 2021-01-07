#include "cub3d.h"

void	cal_item_info(t_list *items, t_pl player)
{
	t_sprite	*info;

	while(items)
	{
		info = (t_sprite *)items->content;
		info->distance = get_distance(player.x, player.y, info->x, info->y);
		info->angle = atan2(info->y - player.y, info->x - player.x);
		items = items->next;
	}
}

void	projection_sprite(t_game *game, t_sprite *sprite)
{
	(void)game;
	(void)sprite;

}

void	render_sprite(t_game *game)
{
	t_list *lst_p;
	t_sprite *sprite;

	cal_item_info(game->cub.items, game->player);
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
