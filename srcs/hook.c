/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynakamot <ynakamot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/05 22:38:51 by ynakamot          #+#    #+#             */
/*   Updated: 2020/12/05 22:53:14 by ynakamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		keypress_hook(int keycode, t_game *game)
{
	printf("The key you pressed is \"%d\"\n", keycode);
	if (keycode == 119)
		game->player.y -= 1;
	if (keycode == 115)
		game->player.y += 1;
	if (keycode == 97)
		game->player.x -= 1;
	if (keycode == 100)
		game->player.x += 1;
	printf("(%6f,%6f)\n", game->player.x, game->player.y);
	return (SUCCESS);
}
