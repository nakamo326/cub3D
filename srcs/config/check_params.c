/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_params.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynakamot <ynakamot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 11:01:47 by ynakamot          #+#    #+#             */
/*   Updated: 2021/01/16 17:31:07 by ynakamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		is_cub(char *filepath)
{
	size_t	len;
	char	*ptr;

	if ((ptr = ft_strrchr(filepath, '/')) == NULL)
		ptr = filepath;
	len = ft_strlen(ptr);
	if (len > 5 && ft_strncmp(&ptr[len - 4], ".cub", 4) == 0)
		return (SUCCESS);
	return (0);
}

void	is_valid_resolution(t_game *game)
{
	int	width;
	int	height;

	mlx_get_screen_size(game->mlx, &width, &height);
	printf("Max window size is %d,%d\n", width, height);
	if (game->cub.window_height > width)
		game->cub.window_width = width;
	if (game->cub.window_height > height)
		game->cub.window_height = height;
}

void	check_missing_params(t_game *game)
{
	if (game->cub.win_f == false)
		config_error(MISSING_PARAMS);
	if (game->cub.no_path_f == false)
		config_error(MISSING_PARAMS);
	if (game->cub.so_path_f == false)
		config_error(MISSING_PARAMS);
	if (game->cub.we_path_f == false)
		config_error(MISSING_PARAMS);
	if (game->cub.ea_path_f == false)
		config_error(MISSING_PARAMS);
	if (game->cub.sp_path_f == false)
		config_error(MISSING_PARAMS);
	if (game->cub.f_color_f == false)
		config_error(MISSING_PARAMS);
	if (game->cub.c_color_f == false)
		config_error(MISSING_PARAMS);
}

void	is_valid_filepath(t_game *game)
{
	int		fd;
	int		i;
	char	*pathes[5];

	pathes[0] = game->cub.no_path;
	pathes[1] = game->cub.so_path;
	pathes[2] = game->cub.we_path;
	pathes[3] = game->cub.ea_path;
	pathes[4] = game->cub.sp_path;
	i = 0;
	while (i < 5)
	{
		if (((fd = open(pathes[i], O_RDONLY)) == -1))
		{
			close(fd);
			config_error(INVALID_FILEPATH);
		}
		close(fd);
		i++;
	}
	ft_putendl_fd("Texture file path is confirmed!", 0);
}

void	check_valid_params(t_game *game)
{
	is_valid_resolution(game);
	adjust_mapscale(game);
	check_missing_params(game);
	is_valid_filepath(game);
}
