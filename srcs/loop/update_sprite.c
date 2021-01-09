#include "cub3d.h"

void	cal_item_info(t_list *items, t_pl player)
{
	t_sprite	*info;

	while(items)
	{
		info = (t_sprite *)items->content;
		info->distance = get_distance(player.x, player.y, info->x, info->y);
		info->angle = normalize_angle(atan2(info->y - player.y, info->x - player.x));
		info->rightend_cor[0] = info->x + cos(info->angle + PI / 2) * TILE_SIZE / 2;
		info->rightend_cor[1] = info->y + sin(info->angle + PI / 2) * TILE_SIZE / 2;
		info->right_angle = normalize_angle(
			atan2(info->rightend_cor[1] - player.y, info->rightend_cor[0] - player.x));
		info->leftend_cor[0] = info->x + cos(info->angle - PI / 2) * TILE_SIZE / 2;
		info->leftend_cor[1] = info->y + sin(info->angle - PI / 2) * TILE_SIZE / 2;
		info->left_angle = normalize_angle(
			atan2(info->leftend_cor[1] - player.y, info->leftend_cor[0] - player.x));
		items = items->next;
	}
}

void	is_visible_sprite(t_game *game)
{
	t_list		*lst_p;
	t_sprite	*tmp;
	double		start_angle;

	lst_p = game->cub.items;
	start_angle = game->player.rotation_angle - FOV / 2;
	while (lst_p != NULL)
	{
		tmp = lst_p->content;
		if (tmp->left_angle >= start_angle && tmp->left_angle <= start_angle + FOV)
			tmp->visible = true;
		else if (tmp->right_angle >= start_angle && tmp->right_angle <= start_angle + FOV)
			tmp->visible = true;
		else if (tmp->left_angle <= start_angle && tmp->right_angle >= start_angle + FOV)
			tmp->visible = true;
		else
			tmp->visible = false;
		lst_p = lst_p->next;
	}
}
