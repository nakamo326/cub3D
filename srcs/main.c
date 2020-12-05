/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynakamot <ynakamot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/29 13:47:56 by ynakamot          #+#    #+#             */
/*   Updated: 2020/12/05 11:14:22 by ynakamot         ###   ########.fr       */
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
	read_cub(fd, game);
	test_print_cub(game->cub);
	is_valid_map(game);
	print_map(game->cub);
}

//第一引数がcubファイル。第二引数に--saveがあったらssをbmpへ。
int		main(int argc, char *argv[])
{
	void		*mlx;
	void		*mlx_win;
	//t_img		map;
	//t_cub		cub;
	t_game		game;


	//is_valid_arg();
	init_val(&game);
	init_game(argc, argv, &game);
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, game.cub.map_maxcol * 20, game.cub.map_maxrow * 20, "2DgridMap");
	game.map.img_ptr = mlx_new_image(mlx, game.cub.map_maxcol * 20, game.cub.map_maxrow * 20);
	game.map.addr = mlx_get_data_addr(game.map.img_ptr, &game.map.bpp, &game.map.len, &game.map.endian);
	//render_gridline(&map, cub);
	render_map(&game.map, &game.cub , game.player);
	mlx_put_image_to_window(mlx, mlx_win, game.map.img_ptr, 0, 0);
	mlx_loop(mlx);
	return 0;
}
