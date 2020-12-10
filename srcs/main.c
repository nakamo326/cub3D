/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynakamot <ynakamot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/29 13:47:56 by ynakamot          #+#    #+#             */
/*   Updated: 2020/12/10 13:11:52 by ynakamot         ###   ########.fr       */
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

void	print_items(t_game game)
{
	t_list *ptr;
	t_sprite *item_info;

	ptr = game.cub.items;
	while(ptr != NULL)
	{
		item_info = ptr->content;
		printf("item number: %d : %f , %f\n",item_info->number, item_info->x, item_info->y);
		ptr = ptr->next;
	}
}

//第一引数がcubファイル。第二引数に--saveがあったらssをbmpへ。
int		main(int argc, char *argv[])
{
	t_game	game;
	int		map_width;
	int		map_height;

	init_val(&game);
	init_game(argc, argv, &game);
	map_width = game.cub.map_maxcol * TILE_SIZE;
	map_height = game.cub.map_maxrow * TILE_SIZE;
	print_items(game);
	//is_valid_arg();
	game.mlx = mlx_init();
	game.mlx_win = mlx_new_window(game.mlx, map_width, map_height, "2DgridMap");
	printf("initialized %d x %d window.\n", map_width, map_height);
	game.map.img_ptr = mlx_new_image(game.mlx, map_width, map_height);
	game.map.addr = mlx_get_data_addr(game.map.img_ptr, &game.map.bpp, &game.map.len, &game.map.endian);

	mlx_hook(game.mlx_win, KeyPress, KeyPressMask, keypress_hook, &game);
	mlx_hook(game.mlx_win, KeyRelease, KeyReleaseMask, keyrelease_hook, &game);
	mlx_loop_hook(game.mlx, loop, &game);
	mlx_loop(game.mlx);
	return 0;
}