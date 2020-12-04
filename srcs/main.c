/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynakamot <ynakamot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/29 13:47:56 by ynakamot          #+#    #+#             */
/*   Updated: 2020/12/04 17:44:00 by ynakamot         ###   ########.fr       */
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

int		main(int argc, char *argv[])
{
	void		*mlx;
	void		*mlx_win;
	t_data		map;
	t_cub		cub;


	//is_valid_arg();
	init_cub(&cub);
	init_game(argc, argv, &cub);
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, cub.map_maxcol * 20, cub.map_maxrow * 20, "2DgridMap");
	map.img = mlx_new_image(mlx, cub.map_maxcol * 20, cub.map_maxrow * 20);
	map.addr = mlx_get_data_addr(map.img, &map.bits_per_pixel, &map.line_length, &map.endian);
	//render_gridline(&map, cub);
	render_map(&map, cub);
	mlx_put_image_to_window(mlx, mlx_win, map.img, 0, 0);
	mlx_loop(mlx);
	return 0;
}

//第一引数がcubファイル。第二引数に--saveがあったらssをbmpへ。
void	test_print_cub(t_cub *cub)
{
	printf("window width: %d\n", cub->window_width);
	printf("window height: %d\n", cub->window_height);
	printf("no_path: %s\n", cub->no_path);
	printf("so_path: %s\n", cub->so_path);
	printf("we_path: %s\n", cub->we_path);
	printf("ea_path: %s\n", cub->ea_path);
	printf("sp_path: %s\n", cub->sp_path);
	printf("fcolor: %d, %d, %d\n", cub->f_color[0],cub->f_color[1],cub->f_color[2]);
	printf("ccolor: %d, %d, %d\n", cub->c_color[0],cub->c_color[1],cub->c_color[2]);
	//print_map();
}

void	print_map(t_cub *cub)
{
	int i;

	i = 0;
	while (cub->map[i] != NULL)
	{
		printf("map[%2d]:%s\n", i, cub->map[i]);
		i++;
	}
}

void	render_gridline(t_data *map, t_cub cub)
{
	int i;
	int j;


	j = 0;
	while (j < cub.map_maxcol)
	{
		i = 0;
		while (i < cub.map_maxrow * 20)
			my_mlx_pixel_put(map, j * 20, i++, 0xB4B4B4);
		j++;
	}
	j = 0;
	while (j < cub.map_maxrow)
	{
		i = 0;
		while (i < cub.map_maxcol * 20)
			my_mlx_pixel_put(map, i++, j * 20, 0xB4B4B4);
		j++;
	}

}