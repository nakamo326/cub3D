/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynakamot <ynakamot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/29 13:47:56 by ynakamot          #+#    #+#             */
/*   Updated: 2020/12/05 10:36:27 by ynakamot         ###   ########.fr       */
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

void	init_game(int argc ,char *argv[], t_cub *cub)
{
	int		fd;

	(void)argc;
	if (!is_cub(argv[1]))
		config_error(ISNT_CUBFILE);
	if((fd = open(argv[1],O_RDONLY)) == ERROR)
		exit(EXIT_FAILURE);
	read_cub(fd, cub);
	test_print_cub(cub);
	is_valid_map(cub);
	print_map(cub);
}

//第一引数がcubファイル。第二引数に--saveがあったらssをbmpへ。
int		main(int argc, char *argv[])
{
	void		*mlx;
	void		*mlx_win;
	t_img		map;
	t_cub		cub;


	//is_valid_arg();
	init_cub(&cub);
	init_game(argc, argv, &cub);
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, cub.map_maxcol * 20, cub.map_maxrow * 20, "2DgridMap");
	map.img_ptr = mlx_new_image(mlx, cub.map_maxcol * 20, cub.map_maxrow * 20);
	map.addr = mlx_get_data_addr(map.img_ptr, &map.bpp, &map.len, &map.endian);
	//render_gridline(&map, cub);
	render_map(&map, &cub);
	mlx_put_image_to_window(mlx, mlx_win, map.img_ptr, 0, 0);
	mlx_loop(mlx);
	return 0;
}
