/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynakamot <ynakamot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/29 13:47:56 by ynakamot          #+#    #+#             */
/*   Updated: 2020/12/10 16:41:24 by ynakamot         ###   ########.fr       */
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
//minimapが幅超えるときの処理
int		main(int argc, char *argv[])
{
	t_game	game;
	int		win_width;
	int		win_height;

	init_val(&game);
	init_game(argc, argv, &game);
	print_items(game);
	win_width = game.cub.window_width;
	win_height= game.cub.window_height;
	//is_valid_arg();
	game.mlx = mlx_init();
	game.mlx_win = mlx_new_window(game.mlx, win_width, win_height, "cub3D");
	game.view.img_ptr = mlx_new_image(game.mlx,  win_width, win_height);
	game.view.addr = mlx_get_data_addr(game.view.img_ptr, &game.view.bpp, &game.view.len, &game.view.endian);

	mlx_hook(game.mlx_win, KeyPress, KeyPressMask, keypress_hook, &game);
	mlx_hook(game.mlx_win, KeyRelease, KeyReleaseMask, keyrelease_hook, &game);
	mlx_loop_hook(game.mlx, loop, &game);
	mlx_loop(game.mlx);
	return 0;
}