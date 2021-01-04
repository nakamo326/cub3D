/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynakamot <ynakamot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/29 13:47:56 by ynakamot          #+#    #+#             */
/*   Updated: 2021/01/04 12:40:01 by ynakamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		quit_game(void *param)
{
	t_game *game;

	game = (t_game *)param;
	mlx_destroy_image(game->mlx, game->view.img_ptr);
	mlx_destroy_display(game->mlx);
	ft_putstr_fd("The game ended successfully.\n", 1);
	exit(EXIT_SUCCESS);
	return (SUCCESS);
}

void	init_game(int argc ,char *argv[], t_game *game)
{
	int		fd;

	(void)argc;
	if (!is_cub(argv[1]))
		config_error(ISNT_CUBFILE);
	if((fd = open(argv[1],O_RDONLY)) == ERROR)
		exit(EXIT_FAILURE);
	read_cub(fd, &game->cub);
	is_valid_map(game);
	//check_valid_params(game);
	adjust_mapscale(game);
	game->rays = ft_calloc((size_t)game->cub.window_width, sizeof(t_ray));
	//test_print_cub(game->cub);
	//test_print_map(game->cub);
	//test_print_items(game);
}

//第一引数がcubファイル。第二引数に--saveがあったらssをbmpへ。
int		main(int argc, char *argv[])
{
	t_game	game;
	int		win_width;
	int		win_height;

	//is_valid_arg();
	init_val(&game);
	init_game(argc, argv, &game);
	win_width = game.cub.window_width;
	win_height= game.cub.window_height;
	game.mlx = mlx_init();
	game.mlx_win = mlx_new_window(game.mlx, win_width, win_height, "cub3D");
	game.view.img_ptr = mlx_new_image(game.mlx, win_width, win_height);
	game.view.addr = mlx_get_data_addr(game.view.img_ptr, &game.view.bpp, &game.view.len, &game.view.endian);
	open_wall_texture(&game);

	mlx_hook(game.mlx_win, KeyPress, KeyPressMask, keypress_hook, &game);
	mlx_hook(game.mlx_win, KeyRelease, KeyReleaseMask, keyrelease_hook, &game);
	//need more check why 33?
	mlx_hook(game.mlx_win, 33, StructureNotifyMask, quit_game, &game);
	mlx_loop_hook(game.mlx, loop, &game);
	mlx_loop(game.mlx);
	return 0;
}