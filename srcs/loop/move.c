/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynakamot <ynakamot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 13:52:52 by ynakamot          #+#    #+#             */
/*   Updated: 2021/01/15 16:17:20 by ynakamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	update_rotation_and_movestep(t_game *game)
{
	double movestep;

	game->player.rotation_angle +=
		game->player.turn_direction * game->player.turn_speed;
	game->player.rotation_angle = normalize_angle(game->player.rotation_angle);
	if (game->player.walk_direction != 0)
		movestep = game->player.walk_direction * game->player.move_speed;
	if (game->player.sidewalk_direction != 0)
		movestep = game->player.sidewalk_direction * game->player.move_speed;
	return (movestep);
}

int		check_collision(t_cub cub, double x, double y)
{
	int map_x;
	int map_y;

	map_x = floor(x / TILE_SIZE);
	map_y = floor(y / TILE_SIZE);
	if (map_y < 0 || map_y >= cub.map_maxrow || map_x < 0 ||
		map_x > (int)ft_strlen(cub.map[map_y]))
		return (INWALL);
	if (cub.map[map_y][map_x] == '1')
		return (INWALL);
	return (ONFLOOR);
}

void	move_player(t_game *game)
{
	double	movestep;
	double	p_angle;
	double	new_x;
	double	new_y;

	movestep = update_rotation_and_movestep(game);
	p_angle = game->player.rotation_angle;
	new_x = game->player.x;
	new_y = game->player.y;
	if (game->player.walk_direction != 0)
	{
		new_x = game->player.x + cos(p_angle) * movestep;
		new_y = game->player.y + sin(p_angle) * movestep;
	}
	if (game->player.sidewalk_direction != 0)
	{
		new_x = game->player.x + cos(p_angle + PI / 2) * movestep;
		new_y = game->player.y + sin(p_angle + PI / 2) * movestep;
	}
	if (!check_collision(game->cub, new_x, game->player.y))
		game->player.x = new_x;
	if (!check_collision(game->cub, game->player.x, new_y))
		game->player.y = new_y;
}
