/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynakamot <ynakamot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 22:40:17 by ynakamot          #+#    #+#             */
/*   Updated: 2020/12/05 11:59:53 by ynakamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		is_validmapline(char *line, t_cub *cub)
{
	int			i;
	const char	*mapchar = "012NSEW ";

	i = 0;
	while (line[i])
		if (!ft_strchr(mapchar, line[i++]))
			return (INVALID_FORMAT);
	i = cub->map_maxrow;
	if (!(cub->map[i] = ft_strdup(line)))
		return (MALLOC_ERROR);
	cub->map[i + 1] = NULL;
	cub->map_maxrow++;
	if ((int)ft_strlen(line) > cub->map_maxcol)
		cub->map_maxcol = ft_strlen(line);
	return (MAP);
}

int		perse_map(int fd, t_cub *cub)
{
	int		rc;
	int		ret;
	char	*line;

	ret = 0;
	line = NULL;
	while ((rc = get_next_line(fd, &line)) >= 0)
	{
		ret = is_validmapline(line, cub);
		free(line);
		if (ret != MAP)
			config_error(ret);
		if (rc == 0)
			break ;
	}
	if (rc == -1)
		config_error(READ_ERROR);
	return (SUCCESS);
}

void	store_item_cordinate(t_cub *cub, int x, int y)
{
	//連結リストに入れる。
	cub->map[y][x] = 0;
}

int		is_closed_map(t_cub *cub, int x, int y)
{
	if (y < 0 || x < 0 || cub->map[y] == NULL ||
			cub->map[y][x] == '\0')
		return (0);
	if (cub->map[y][x] == '2')
		store_item_cordinate(cub, x, y);
	if (cub->map[y][x] == '*' || cub->map[y][x] == '1')
		return (0);
	if (y == 0 || x == 0 || cub->map[y + 1] == NULL ||
			cub->map[y][x + 1] == '\0')
		config_error(MAP_ISNT_CLOSED);
	cub->map[y][x] = '*';
	is_closed_map(cub, x + 1, y);
	is_closed_map(cub, x, y + 1);
	is_closed_map(cub, x - 1, y);
	is_closed_map(cub, x, y - 1);
	return (SUCCESS);
}

int		is_valid_map(t_game *game)
{
	int		x;
	int		y;
	bool	p_flag;
	y = 0;
	p_flag = false;
	while (game->cub.map[y] != NULL)
	{
		x = 0;
		while (game->cub.map[y][x] != '\0')
		{
			if (ft_strchr("NSWE", game->cub.map[y][x]))
			{
				if (p_flag == true)
					config_error(MULTIPLE_PLAYER);
				game->player.x = x;
				game->player.y = y;
				game->player.spawn_direction = game->cub.map[y][x];
				p_flag = true;
				game->cub.map[y][x] = '0';
			}
			x++;
		}
		y++;
	}
	return (is_closed_map(&game->cub, game->player.x, game->player.y));
}