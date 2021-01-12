/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_bmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynakamot <ynakamot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 13:31:14 by ynakamot          #+#    #+#             */
/*   Updated: 2021/01/12 13:32:33 by ynakamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	write_binary(int size, long n, int fd)
{
	int i;

	i = 0;
	while (i < size)
	{
		ft_putchar_fd(n % 256, fd);
		n = n / 256;
		i++;
	}
}

void	write_bmp(int fd, int pad, t_img img)
{
	int		x;
	int		y;
	int		color;
	char	*addr;

	y = 1;
	while (y <= img.h)
	{
		x = 0;
		while (x < img.w)
		{
			addr = (char *)img.addr;
			color = *(int *)(addr + (img.h - y) * img.len + x * (img.bpp / 8));
			write_binary(3, color, fd);
			x++;
		}
		write_binary(pad, 0, fd);
		y++;
	}
}

void	write_header(int fd, int pad, t_img img)
{
	int filesize;

	filesize = 54 + (((24 * img.w) + pad * 8) * img.h) / 8;
	write_binary(1, 'B', fd);
	write_binary(1, 'M', fd);
	write_binary(4, filesize, fd);
	write_binary(2, 0, fd);
	write_binary(2, 0, fd);
	write_binary(4, 54, fd);
	write_binary(4, 40, fd);
	write_binary(4, img.w, fd);
	write_binary(4, img.h, fd);
	write_binary(2, 1, fd);
	write_binary(2, 24, fd);
	write_binary(4, 0, fd);
	write_binary(4, img.w * 3 * img.h, fd);
	write_binary(4, 0, fd);
	write_binary(4, 0, fd);
	write_binary(4, 0, fd);
	write_binary(4, 0, fd);
}

void	export_bmp(t_game *game)
{
	int	fd;
	int	pad;

	cal_item_info(game->cub.items, game->player);
	cast_all_rays(game);
	render_projected_wall(game);
	render_sprite(game);
	mlx_do_sync(game->mlx);
	fd = open("./ss.bmp", O_CREAT | O_WRONLY, S_IRWXU);
	if (fd == ERROR)
		exit(EXIT_FAILURE);
	pad = 0;
	if (game->cub.window_width * 3 % 4 != 0)
		pad = 4 - game->cub.window_width * 3 % 4;
	write_header(fd, pad, game->view);
	write_bmp(fd, pad, game->view);
	close(fd);
	quit_game(game);
}
