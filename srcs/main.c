/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynakamot <ynakamot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/29 13:47:56 by ynakamot          #+#    #+#             */
/*   Updated: 2020/11/29 21:03:55 by ynakamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include <stdio.h>

extern t_cub cub_info;

int read_cub(int fd)
{
	char *line;
	int rc;

	line = NULL;
	while((rc = get_next_line(fd, &line)))
	{

	}
}

void init_game(int argc ,char **argv)
{
	int		fd;

	if((fd = open(argv[1],O_RDONLY)) == ERROR)
		exit(EXIT_FAILURE);
	read_cub(fd);

}

int main(int argc, char  **argv)
{
	void	*mlx;
	void	*mlx_win;
	t_data	map;

	init_game(argc, argv);
	//mlx = mlx_init();
	//mlx_win = mlx_new_window(mlx, 640, 480, "2DgridMap");
	//map.img = mlx_new_image(mlx, 640, 480);
	//map.addr = mlx_get_data_addr(map.img, &map.bits_per_pixel, &map.line_length, &map.endian);
	//my_mlx_pixel_put(&map, 5,5, 0x00FF0000);
	//mlx_put_image_to_window(mlx, mlx_win, map.img, 0, 0);
	//mlx_loop(mlx);

	return 0;
}


//第一引数がcubファイル。第二引数に--saveがあったらssをbmpへ。
//まずcubファイルの読み込み。gnlで一行ずつ解釈して構造体に格納？
//cubファイルに不備があった場合、""Error\n"出力後エラーメッセージ
//ゲームループへ