/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynakamot <ynakamot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 22:40:17 by ynakamot          #+#    #+#             */
/*   Updated: 2020/12/06 11:09:28 by ynakamot         ###   ########.fr       */
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
	t_list		*new;
	t_sprite	*item_info;
	static int	num = 0;
	item_info = malloc(sizeof(t_sprite));
	item_info->x = x;
	item_info->y = y;
	item_info->number = num++;
	if (!(new = ft_lstnew(item_info)))
		config_error(MALLOC_ERROR);
	ft_lstadd_back(&cub->items, new);
	cub->map[y][x] = '0';
}

int		is_closed_map(t_cub *cub, int x, int y)
{
	if (y < 0 || x < 0 || cub->map[y] == NULL ||
			cub->map[y][x] == '\0')
		return (0);
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

void	store_pl_info(t_game *game, int x, int y)
{
	game->player.x = x * TILE_SIZE + TILE_SIZE /2;
	game->player.y = y * TILE_SIZE + TILE_SIZE /2;
	if (game->cub.map[y][x] == 'N')
		game->player.rotation_angle = 270 * PI / 180;
	if (game->cub.map[y][x] == 'S')
		game->player.rotation_angle = 90 * PI / 180;
	if (game->cub.map[y][x] == 'W')
		game->player.rotation_angle = 0 * PI / 180;
	if (game->cub.map[y][x] == 'E')
		game->player.rotation_angle = 180 * PI / 180;
	game->cub.map[y][x] = '0';
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
			if (game->cub.map[y][x] == '2')
				store_item_cordinate(&game->cub, x, y);
			if (ft_strchr("NSWE", game->cub.map[y][x]))
			{
				if (p_flag == true)
					config_error(MULTIPLE_PLAYER);
				store_pl_info(game, x, y);
				p_flag = true;
			}
			x++;
		}
		y++;
	}
	x = game->player.x / TILE_SIZE;
	y = game->player.y / TILE_SIZE;
	return (is_closed_map(&game->cub, x, y));
}