/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynakamot <ynakamot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/29 13:47:56 by ynakamot          #+#    #+#             */
/*   Updated: 2020/12/01 09:38:49 by ynakamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_cub cub_info;

void	init_cub()
{
	cub_info.window_width = 640;
	cub_info.window_height= 480;
	cub_info.no_path = NULL;
	cub_info.so_path = NULL;
	cub_info.we_path = NULL;
	cub_info.ea_path = NULL;
	cub_info.sp_path = NULL;
	cub_info.f_color[0] = 0xFF;
	cub_info.f_color[1] = 0xFF;
	cub_info.f_color[2] = 0xFF;
	cub_info.c_color[0] = 0x11;
	cub_info.c_color[1] = 0x11;
	cub_info.c_color[2] = 0x11;
	cub_info.map = NULL;
	cub_info.win_f = false;
	cub_info.no_path_f = false;
	cub_info.so_path_f = false;
	cub_info.we_path_f = false;
	cub_info.ea_path_f = false;
	cub_info.sp_path_f = false;
	cub_info.f_color_f = false;
	cub_info.c_color_f = false;
}

void	init_game(int argc ,char **argv)
{
	int		fd;

	if((fd = open(argv[1],O_RDONLY)) == ERROR)
		exit(EXIT_FAILURE);
	read_cub(fd);

}

int		main(int argc, char  **argv)
{
	void	*mlx;
	void	*mlx_win;
	//t_data	map;

	//is_valid_arg();
	init_cub();
	init_game(argc, argv);
	//mlx = mlx_init();
	//mlx_win = mlx_new_window(mlx, 640, 480, "2DgridMap");
	//map.img = mlx_new_image(mlx, 640, 480);
	//map.addr = mlx_get_data_addr(map.img, &map.bits_per_pixel, &map.line_length, &map.endian);
	//my_mlx_pixel_put(&map, 5,5, 0x00FF0000);
	//mlx_put_image_to_window(mlx, mlx_win, map.img, 0, 0);
	//mlx_loop(mlx);

	test_cub();
	return 0;
}


//第一引数がcubファイル。第二引数に--saveがあったらssをbmpへ。
//まずcubファイルの読み込み。gnlで一行ずつ解釈して構造体に格納？
//cubファイルに不備があった場合、""Error\n"出力後エラーメッセージ
//ゲームループへ