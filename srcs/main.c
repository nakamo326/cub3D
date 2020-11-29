/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynakamot <ynakamot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/29 13:47:56 by ynakamot          #+#    #+#             */
/*   Updated: 2020/11/29 23:43:33 by ynakamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

extern t_cub cub_info;

void	init_cub()
{
	cub_info.window_width = 0;
	cub_info.window_height= 0;
	cub_info.no_path = NULL;
	cub_info.so_path = NULL;
	cub_info.we_path = NULL;
	cub_info.ea_path = NULL;
	cub_info.sp_path = NULL;
	cub_info.f_color = 0;
	cub_info.c_color = 0;
	cub_info.map = NULL;
}

int read_cub(int fd)
{
	char *line;
	int rc;
	int ret;

	errno = 0;
	line = NULL;
	while((rc = get_next_line(fd, &line)) >= 0)
	{
		ret = perse_cub(line);
		free(line);
		if (ret != 1)
			return (output_errmsg(ret));
		if (rc == 0)
			break;
	}
	if (rc == -1)
	{
		ft_putstr_fd("Error\n", 2);
		ft_putstr_fd(errno, 2);
		exit (EXIT_FAILURE);
	}
	return (1);
}

int		perse_cub(char *line)
{
	const char id[][3] = {{"R"},{"NO"},{"SO"},{"WE"},{"EA"},{"S"},{"F"},{"C"}};
	//一文字ちゃんと比較できるか怪しい
	char *ptr;
	int		i;

	i = 0;
	while (id[i] != NULL)
	{
		ptr = ft_strnstr(line, id[i], 2);
		if (!ptr)
			continue;
		if (i == 0)
			return (input_res(ptr));
		if (i >= 1 && i <= 5)
			return (input_path(ptr));
		if (i >= 6)
			return (input_color(ptr));
	}
	return ();
}

output_errmsg(int ret)
{

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