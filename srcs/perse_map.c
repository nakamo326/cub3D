/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynakamot <ynakamot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 22:40:17 by ynakamot          #+#    #+#             */
/*   Updated: 2020/12/03 22:09:43 by ynakamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		is_validmapline(char *line)
{
	int			i;
	const char	*mapchar = "012NSEW ";

	i = 0;
	while (line[i])
		if (!ft_strchr(mapchar, line[i++]))
			return (INVALID_FORMAT);
	i = cub.map_maxrow;
	if (!(cub.map[i] = ft_strdup(line)))
		return (MALLOC_ERROR);
	cub.map[i + 1] = NULL;
	cub.map_maxrow++;
	if ((int)ft_strlen(line) > cub.map_maxcol)
		cub.map_maxcol = ft_strlen(line);
	return (MAP);
}

int		perse_map(int fd)
{
	int		rc;
	int		ret;
	char	*line;

	ret = 0;
	line = NULL;
	while ((rc = get_next_line(fd, &line)) >= 0)
	{
		ret = is_validmapline(line);
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

int		is_valid_map(void)
{
	int		x;
	int		y;
	bool	p_flag;

	y = 0;
	p_flag = false;
	while (cub.map[y] != NULL)
	{
		x = 0;
		while (cub.map[y][x] != '\0')
		{
			if (ft_strchr("NSWE", cub.map[y][x]))
			{
				if (p_flag == true)
					config_error(MULTIPLE_PLAYER);
				pl_info.x = x;
				pl_info.y = y;
				p_flag = true;
				cub.map[y][x] = '0';
			}
			x++;
		}
		y++;
	}
	return (is_closed_map(pl_info.x, pl_info.y));
}

void	store_item_cordinate(int x, int y)
{
	//連結リストに入れる。
	cub.map[y][x] = 0;
}

int		is_closed_map(int x, int y)
{
	if (y < 0 || x < 0 || cub.map[y] == NULL ||
			cub.map[y][x] == '\0')
		return (0);
	if (cub.map[y][x] == '2')
		store_item_cordinate(x, y);
	if (cub.map[y][x] == '*' || cub.map[y][x] == '1')
		return (0);
	if (y == 0 || x == 0 || cub.map[y + 1] == NULL ||
			cub.map[y][x + 1] == '\0')
		config_error(MAP_ISNT_CLOSED);
	cub.map[y][x] = '*';
	is_closed_map(x + 1, y);
	is_closed_map(x, y + 1);
	is_closed_map(x - 1, y);
	is_closed_map(x, y - 1);
	return (SUCCESS);
}
