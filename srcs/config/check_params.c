/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_params.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynakamot <ynakamot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 11:01:47 by ynakamot          #+#    #+#             */
/*   Updated: 2021/01/11 21:14:57 by ynakamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		is_cub(char *filepath)
{
	size_t len;

	len = ft_strlen(filepath);
	if (len > 4 || ft_strncmp(&filepath[len - 4], ".cub" , 4) == 0)
		return (SUCCESS);
	return (0);
}

void	is_valid_resolution(t_game *game)
{
	int	width;
	int	height;

	mlx_get_screen_size(game->mlx, &width, &height);
	if (game->cub.window_height > width)
		game->cub.window_width = width;
	if (game->cub.window_height > height)
		game->cub.window_height = height;
	printf("%d,%d\n",game->cub.window_width, game->cub.window_height);
}

//void	check_missing_params(t_game *game)
//{
//
//}
//
//void	is_valid_filepath(t_game *game)
//{
//
//}

void	check_valid_params(t_game *game)
{
	is_valid_resolution(game);
	//is_valid_filepath(game);
	//check_missing_params(game);
	//is_valid_texture(game);

}