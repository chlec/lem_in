/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecalie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 14:06:56 by clecalie          #+#    #+#             */
/*   Updated: 2018/03/20 15:03:36 by clecalie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	add_to_head(t_env *env, t_path *path)
{
	ft_list_push_back(&(env->head_path), path, sizeof(t_path));
	free(path);
	path = NULL;
	return (create_path(env, NULL));
}

void	delete_path(t_path *path)
{
	ft_lstdel(&path->room, del);
	free(path->room);
	path->room = NULL;
	free(path);
	path = NULL;
}

void	init_lowest_path(t_env *env)
{
	t_path	*path;
	t_list	*head_p;

	head_p = env->head_path;
	while (head_p)
	{
		path = (t_path*)(head_p->content);
		if (path->len == env->lower_size)
			path->len = 0;
		head_p = head_p->next;
	}
}

void	print_path(t_env *env, int i)
{
	t_path	*path;
	t_room	*room;
	t_list	*head_p;
	t_list	*head_r;

	head_p = env->head_path;
	head_r = head_p->content;
	while (head_p)
	{
		path = (t_path*)(head_p->content);
		head_r = path->room;
		ft_putstr("path nº");
		ft_putnbr(++i);
		ft_putstr("\n");
		while (head_r)
		{
			room = (t_room*)(head_r->content);
			ft_putstr(room->name);
			if (head_r->next)
				ft_putstr(" -> ");
			head_r = head_r->next;
		}
		ft_putstr("\n");
		head_p = head_p->next;
	}
}
