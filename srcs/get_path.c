/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecalie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/01 14:13:24 by clecalie          #+#    #+#             */
/*   Updated: 2018/03/12 14:16:30 by clecalie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		already_found(t_list **l, t_list **p)
{
	t_list	*all_path;
	t_path	*path;
	t_list	*new_path;
	t_room	*room1;

	all_path = *l;
	while (all_path)
	{
		path = (t_path*)all_path->content;
		new_path = *p;
		while (new_path)
		{
			room1 = (t_room*)new_path->content;
			if (room_is_present((&path->room), room1))
				return (1);
			new_path = new_path->next;
		}
		all_path = all_path->next;
	}
	return (0);
}

void	nb_room_path(t_env *env)
{
	t_path	*path;
	t_room	*room;
	t_list	*head_p;
	t_list	*head_r;
	int		len;

	len = 0;
	head_p = env->head_path;
	head_r = head_p->content;
	while (head_p)
	{
		len = 0;
		path = (t_path*)(head_p->content);
		head_r = path->room;
		while (head_r)
		{
			room = (t_room*)(head_r->content);
			head_r = head_r->next;
			len++;
		}
		path->len = len;
		if (len < env->lower_size)
			env->lower_size = len;
		head_p = head_p->next;
	}
}

void	create_non_existant_path(t_env *env, t_pipe *pipe)
{
	t_path	*path;

	if (!(path = (t_path*)malloc(sizeof(t_path))))
		exit(0);
	path->room = NULL;
	path->len = 0;
	ft_list_push_back(&(path->room), ft_strequ(pipe->left->name, env->end->name)
			? pipe->left : pipe->right, sizeof(t_room));
	ft_list_push_back(&(path->room), ft_strequ(pipe->left->name, env->end->name)
			? pipe->right : pipe->left, sizeof(t_room));
	path->len += 2;
	pipe->used = 1;
	if (ft_strequ(get_last_room(&(path->room))->name, env->start->name)
			&& !already_found(&(env->head_path), &(path->room)))
		return (add_to_head(env, path));
	else if (already_found(&(env->head_path), &(path->room)))
	{
		ft_lstdel(&path->room, del);
		free(path);
		path = NULL;
	}
	create_path(env, path);
	delete_path(path);
	return ;
}

void	create_existant_path(t_env *env, t_pipe *pipe, t_path *p)
{
	t_path	*path;
	t_room	*room1;

	path = copy_maillon(&(p->room));
	room1 = get_last_room(&(p->room));
	if ((ft_strequ(room1->name, pipe->right->name)
				|| ft_strequ(room1->name, pipe->left->name)))
	{
		if (ft_strequ(room1->name, env->end->name)
				|| ft_strequ(room1->name, env->start->name))
		{
			delete_path(path);
			return (create_path(env, NULL));
		}
		ft_list_push_back(&(path->room),
				ft_strequ(room1->name, pipe->left->name)
				? pipe->right : pipe->left, sizeof(t_room));
		p->len++;
		pipe->used = 1;
		create_path(env, path);
	}
	if (ft_strequ(get_last_room(&(path->room))->name, env->start->name)
			&& !already_found(&(env->head_path), &(path->room)))
		return (add_to_head(env, path));
	delete_path(path);
}

void	create_path(t_env *env, t_path *p)
{
	t_list	*pipe_list;
	t_pipe	*pipe;

	pipe_list = env->head_pipe;
	while (pipe_list)
	{
		pipe = (t_pipe*)pipe_list->content;
		if (!p
				&& !pipe->used
				&& (ft_strequ(pipe->left->name, env->end->name) ||
					ft_strequ(pipe->right->name, env->end->name)))
			return (create_non_existant_path(env, pipe));
		else if (p && !pipe->used)
			create_existant_path(env, pipe, p);
		pipe_list = pipe_list->next;
	}
}
