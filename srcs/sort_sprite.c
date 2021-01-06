/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynakamot <ynakamot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 20:08:16 by ynakamot          #+#    #+#             */
/*   Updated: 2021/01/06 20:08:25 by ynakamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_list	*search_far_item(t_list *lst_index)
{
	double		dist;
	t_list		*res;
	t_sprite	*tmp;

	dist = -1000;
	res = lst_index;
	while (lst_index != NULL)
	{
		tmp = lst_index->content;
		if (tmp->distance > dist)
			dist = tmp->distance;
		lst_index = lst_index->next;
	}
	while (res != NULL)
	{
		tmp = res->content;
		if (tmp->distance == dist)
			return (res);
		res = res->next;
	}
	return (NULL);
}

void	sort_items(t_list *items)
{
	t_list		*lst_p;
	t_sprite	*tmp;

	while (items != NULL)
	{
		lst_p = search_far_item(items);
		tmp = items->content;
		items->content = lst_p->content;
		lst_p->content = tmp;
		items = items->next;
	}
}