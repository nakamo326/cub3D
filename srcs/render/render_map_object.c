/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map_object.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynakamot <ynakamot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/05 12:18:39 by ynakamot          #+#    #+#             */
/*   Updated: 2020/12/10 12:44:42 by ynakamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	render_player(t_game *game, int x, int y)
{
	t_line line;

	line.x0 = game->player.x;
	line.y0 = game->player.y;
	line.x1 = game->player.x + cos(game->player.rotation_angle) * 15;
	line.y1 = game->player.y + sin(game->player.rotation_angle) * 15;
	draw_line(game, line, 0xFF0000);
	line.x1 = game->player.x + cos(game->player.rotation_angle + PI / 2) * 10;
	line.y1 = game->player.y + sin(game->player.rotation_angle + PI / 2) * 10;
	draw_line(game, line, 0x00FF00);
	line.x1 = game->player.x + cos(game->player.rotation_angle - PI / 2) * 10;
	line.y1 = game->player.y + sin(game->player.rotation_angle - PI / 2) * 10;
	draw_line(game, line, 0x0000FF);
	//red dot with anti alias
	my_mlx_pixel_put(&game->map, x, y, 0xFF0000);
	my_mlx_pixel_put(&game->map, x + 1, y, 0xFF0000);
	my_mlx_pixel_put(&game->map, x - 1, y, 0xFF0000);
	my_mlx_pixel_put(&game->map, x, y + 1, 0xFF0000);
	my_mlx_pixel_put(&game->map, x, y - 1, 0xFF0000);
	my_mlx_pixel_put(&game->map, x - 1, y - 1, 0x80110B);
	my_mlx_pixel_put(&game->map, x - 1, y + 1, 0x80110B);
	my_mlx_pixel_put(&game->map, x + 1, y - 1, 0x80110B);
	my_mlx_pixel_put(&game->map, x + 1, y + 1, 0x80110B);
}

void	render_ray(t_game *game)
{
	t_line	line;
	int		i;

	i = 0;
	while(i < game->cub.window_width)
	{
		line.x0 = game->player.x;
		line.y0 = game->player.y;
		if (game->rays[i].hwall_hit == true)
		{
			line.x1 = game->rays[i].hwall_x;
			line.y1 = game->rays[i].hwall_y;
			draw_line(game, line, 0x50FFFF00);
		}
		if (game->rays[i].vwall_hit == true)
		{
			line.x1 = game->rays[i].vwall_x;
			line.y1 = game->rays[i].vwall_y;
			draw_line(game, line, 0x50FFFF00);
		}
	i++;
	}
}

void	render_items(t_img *map, int x, int y)
{
	int i;
	int j;

	i = 0;
	x += TILE_SIZE * 3 / 8;
	y += TILE_SIZE * 3 / 8;
	while (i <= TILE_SIZE / 4)
	{
		j = 0;
		while (j <= TILE_SIZE / 4)
		{
			my_mlx_pixel_put(map, x + i, y + j, 0x2DC8FF);
			j++;
		}
		i++;
	}
}

void	render_map_object(t_game *game)
{
	t_list		*lstptr;
	t_sprite	*item_info;

	render_ray(game);
	render_player(game, game->player.x, game->player.y);
	lstptr = game->cub.items;
	while (lstptr != NULL)
	{
		item_info = lstptr->content;
		render_items(&game->map, item_info->x, item_info->y);
		lstptr = lstptr->next;
	}

}