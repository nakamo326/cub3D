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

void	render_sprite(t_game *game)
{
	cal_item_info(game->cub.items, game->player);
	sort_items(game->cub.items);


	test_print_items(*game);
}

/*
見える範囲のspriteまでの距離を測る。遠い順に。同時に壁との距離と比較して手前を描画

*/