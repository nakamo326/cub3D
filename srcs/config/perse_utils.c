/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynakamot <ynakamot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 21:22:25 by ynakamot          #+#    #+#             */
/*   Updated: 2021/01/16 18:14:31 by ynakamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	is_all_digit(char *str)
{
	while (*str != '\0')
	{
		if (!ft_isdigit(*str))
			return (false);
		str++;
	}
	return (true);
}

int		check_str_num(char **strs)
{
	int i;

	i = 0;
	while (strs[i] != NULL)
		i++;
	return (i);
}

int		free_ret(char **strs, int ret)
{
	ft_free_split(strs);
	return (ret);
}
