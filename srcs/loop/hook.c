/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynakamot <ynakamot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/05 22:38:51 by ynakamot          #+#    #+#             */
/*   Updated: 2021/01/14 21:57:23 by ynakamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	update_direction(int keycode, t_game *game)
{
	if (keycode == KEY_W)
		game->player.walk_direction = 1;
	if (keycode == KEY_S)
		game->player.walk_direction = -1;
	if (keycode == KEY_D)
		game->player.sidewalk_direction = 1;
	if (keycode == KEY_A)
		game->player.sidewalk_direction = -1;
	if (keycode == KEY_RIGHT)
		game->player.turn_direction = 1;
	if (keycode == KEY_LEFT)
		game->player.turn_direction = -1;
}

void	reset_direction(int keycode, t_game *game)
{
	if (keycode == KEY_W || keycode == KEY_S)
		game->player.walk_direction = 0;
	if (keycode == KEY_A || keycode == KEY_D)
		game->player.sidewalk_direction = 0;
	if (keycode == KEY_RIGHT || keycode == KEY_LEFT)
		game->player.turn_direction = 0;
}

void	toggle_flag(bool *flag)
{
	if (*flag == true)
		*flag = false;
	else
		*flag = true;
}

int		keypress_hook(int keycode, t_game *game)
{
	if (keycode == KEY_W || keycode == KEY_A || keycode == KEY_S ||
	keycode == KEY_D || keycode == KEY_RIGHT || keycode == KEY_LEFT)
		update_direction(keycode, game);
	if (keycode == KEY_ESC)
		quit_game((void *)game);
	if (keycode == KEY_M)
		toggle_flag(&game->map_toggle);
	return (SUCCESS);
}

int		keyrelease_hook(int keycode, t_game *game)
{
	if (keycode == KEY_W || keycode == KEY_A || keycode == KEY_S ||
	keycode == KEY_D || keycode == KEY_RIGHT || keycode == KEY_LEFT)
		reset_direction(keycode, game);
	return (SUCCESS);
}
