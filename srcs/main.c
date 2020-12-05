/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynakamot <ynakamot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/29 13:47:56 by ynakamot          #+#    #+#             */
/*   Updated: 2020/12/05 15:13:41 by ynakamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		is_cub(char *filepath)
{
	size_t len;

	len = ft_strlen(filepath);
	if (ft_strncmp(&filepath[len - 4], ".cub" , 4) == 0)
		return (SUCCESS);
	return (0);
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
	test_print_cub(game->cub);
	is_valid_map(game);
	print_map(game->cub);
}

//第一引数がcubファイル。第二引数に--saveがあったらssをbmpへ。
int		main(int argc, char *argv[])
{
	//void		*mlx;
	//void		*mlx_win;
	t_game		game;


	//is_valid_arg();
	init_val(&game);
	init_game(argc, argv, &game);
	game.mlx = mlx_init();
	game.mlx_win = mlx_new_window(game.mlx, game.cub.map_maxcol * 20, game.cub.map_maxrow * 20, "2DgridMap");
	game.map.img_ptr = mlx_new_image(game.mlx, game.cub.map_maxcol * 20, game.cub.map_maxrow * 20);
	game.map.addr = mlx_get_data_addr(game.map.img_ptr, &game.map.bpp, &game.map.len, &game.map.endian);
	mlx_loop_hook(game.mlx, loop, &game);
	mlx_loop(game.mlx);
	return 0;
}
