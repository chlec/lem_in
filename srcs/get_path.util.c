/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecalie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 14:06:56 by clecalie          #+#    #+#             */
/*   Updated: 2018/03/12 14:19:55 by clecalie         ###   ########.fr       */
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

void	print_path(t_env *env)
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
		printf("nombre de room = %d\n", path->len);
		while (head_r)
		{
			room = (t_room*)(head_r->content);
			printf("chemin: %s nb_ant = %d \n", room->name, room->ant);
			head_r = head_r->next;
		}
		printf("------\n");
		head_p = head_p->next;
	}
}
