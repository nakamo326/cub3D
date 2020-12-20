/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynakamot <ynakamot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/05 22:38:51 by ynakamot          #+#    #+#             */
/*   Updated: 2020/12/20 15:14:32 by ynakamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	update_direction(int keycode, t_game *game)
{
	if (keycode == 119)
		game->player.walk_direction = 1;
	if (keycode == 115)
		game->player.walk_direction = -1;
	if (keycode == 100)
		game->player.sidewalk_direction = 1;
	if (keycode == 97)
		game->player.sidewalk_direction = -1;
	if (keycode == 65363)
		game->player.turn_direction = 1;
	if (keycode == 65361)
		game->player.turn_direction = -1;
}

void	reset_direction(int keycode, t_game *game)
{
	if (keycode == 119)
		game->player.walk_direction = 0;
	if (keycode == 115)
		game->player.walk_direction = 0;
	if (keycode == 100)
		game->player.sidewalk_direction = 0;
	if (keycode == 97)
		game->player.sidewalk_direction = 0;
	if (keycode == 65363)
		game->player.turn_direction = 0;
	if (keycode == 65361)
		game->player.turn_direction = 0;
}

int		keypress_hook(int keycode, t_game *game)
{
	//printf("The key you pressed is \"%d\"\n", keycode);
	if (keycode == 119 || keycode == 115 || keycode == 97 || keycode == 100 ||
		keycode == 65361 || keycode == 65363)
		update_direction(keycode, game);
	if (keycode == 65307)
		quit_game((void *)game);
	return (SUCCESS);
}

int		keyrelease_hook(int keycode, t_game *game)
{
	//printf("The key you released is \"%d\"\n", keycode);
	if (keycode == 119 || keycode == 115 || keycode == 97 || keycode == 100 ||
		keycode == 65361 || keycode == 65363)
		reset_direction(keycode, game);

	return (SUCCESS);
}
