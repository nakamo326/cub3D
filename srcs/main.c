/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynakamot <ynakamot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/29 13:47:56 by ynakamot          #+#    #+#             */
/*   Updated: 2021/01/16 18:14:43 by ynakamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		quit_game(void *param)
{
	t_game *game;

	game = (t_game *)param;
	mlx_destroy_image(game->mlx, game->view.img_ptr);
	mlx_destroy_display(game->mlx);
	ft_putstr_fd("The game ended successfully!\n", 1);
	exit(EXIT_SUCCESS);
	return (SUCCESS);
}

void	init_game(int argc, char *argv[], t_game *game)
{
	int		fd;

	is_valid_args(argc, argv, game);
	if ((fd = open(argv[1], O_RDONLY)) == ERROR)
		config_error(OPEN_ERROR);
	read_cub(fd, &game->cub);
	is_valid_map(game);
	check_valid_params(game);
	game->rays = ft_calloc((size_t)game->cub.window_width, sizeof(t_ray));
	game->zbuffer = ft_calloc((size_t)game->cub.window_width, sizeof(double));
	game->dist_plane = (game->cub.window_width / 2) / tan(FOV / 2);
	open_all_texture(game);
}

int		main(int argc, char *argv[])
{
	t_game	game;

	init_val(&game);
	game.mlx = mlx_init();
	init_game(argc, argv, &game);
	game.view.w = game.cub.window_width;
	game.view.h = game.cub.window_height;
	if (game.save_flag == false)
		game.mlx_win = mlx_new_window(
			game.mlx, game.view.w, game.view.h, "cub3D");
	game.view.img_ptr = mlx_new_image(game.mlx, game.view.w, game.view.h);
	game.view.addr = mlx_get_data_addr(game.view.img_ptr,
		&game.view.bpp, &game.view.len, &game.view.endian);
	if (game.save_flag == true)
		export_bmp(&game);
	mlx_hook(game.mlx_win, KeyPress, KeyPressMask, keypress_hook, &game);
	mlx_hook(game.mlx_win, KeyRelease, KeyReleaseMask, keyrelease_hook, &game);
	mlx_hook(game.mlx_win, 33, StructureNotifyMask, quit_game, &game);
	mlx_loop_hook(game.mlx, loop, &game);
	mlx_loop(game.mlx);
	return (0);
}
