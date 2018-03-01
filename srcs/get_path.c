/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecalie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/01 14:13:24 by clecalie          #+#    #+#             */
/*   Updated: 2018/03/01 14:17:02 by clecalie         ###   ########.fr       */
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

void		nb_room_path(t_env *env)
{	
	t_path	*path;
	t_room	*room;
	t_list	*head_p;
	t_list	*head_r;
	int 	len;

	len = 0;
	head_p = env->head_path;
	head_r = head_p->content;;
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

void		init_lowest_path(t_env *env)
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

void		print_path(t_env *env)
{	
	t_path	*path;
	t_room	*room;
	t_list	*head_p;
	t_list	*head_r;

	head_p = env->head_path;
	head_r = head_p->content;;
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
void	create_path(t_env *env, t_path *p)
{
	t_path	*path;
	t_list	*pipe_list;
	t_room	*room1;
	t_pipe	*pipe;
	t_list	*all_path;

	/*
	 * Faire de la recursive!
	 * En gros si on a 0-4 on fait tout les chemin possible a partir de 0-4 et ainsi de suite
	 * */
	pipe_list = env->head_pipe;
	room1 = NULL;
	all_path = NULL;
	while (pipe_list)
	{
		pipe = (t_pipe*)pipe_list->content;
		if (!p && !pipe->used && (ft_strequ(pipe->left->name, env->end->name) || ft_strequ(pipe->right->name, env->end->name)))
		{
			path = (t_path*)malloc(sizeof(t_path));
			path->room = NULL;
			path->len = 0;
			//On met toujours le ##end en 1er sur le path
			//	printf("Debut de path, on met %s et %s\n", pipe->left->name, pipe->right->name);
			ft_list_push_back(&(path->room), ft_strequ(pipe->left->name, env->end->name) ? pipe->left : pipe->right, sizeof(t_room));
			ft_list_push_back(&(path->room), ft_strequ(pipe->left->name, env->end->name) ? pipe->right : pipe->left, sizeof(t_room));
			path->len += 2;
			pipe->used = 1;
			if (ft_strequ(get_last_room(&(path->room))->name, env->start->name) && !already_found(&(env->head_path), &(path->room)))
			{
				//printf("Ajout du path au head\n");
				ft_list_push_back(&(env->head_path), path, sizeof(t_path));
				return create_path(env, NULL);
			}
			return create_path(env, path);
		}
		else if (p && !pipe->used)
		{
			path = copy_maillon(&(p->room));
			//the loop behind break the linked list
			room1 = get_last_room(&(p->room));
			if ((ft_strequ(room1->name, pipe->right->name) || ft_strequ(room1->name, pipe->left->name)))
			{
				//printf("on ajoute %s\n", ft_strequ(room1->name, pipe->left->name) ? pipe->right->name : pipe->left->name);
				//	usleep(500000);
				if (ft_strequ(room1->name, env->end->name) || ft_strequ(room1->name, env->start->name))
					return create_path(env, NULL);
				ft_list_push_back(&(path->room), ft_strequ(room1->name, pipe->left->name) ? pipe->right : pipe->left, sizeof(t_room));
				p->len++;
				//Supprimer la ligne du dessous?
				pipe->used = 1;
				create_path(env, path);
			}
			if (ft_strequ(get_last_room(&(path->room))->name, env->start->name) && !already_found(&(env->head_path), &(path->room)))
			{
				//printf("Ajout du path au head\n");
				ft_list_push_back(&(env->head_path), path, sizeof(t_path));
				return create_path(env, NULL);
			}
		}
		pipe_list = pipe_list->next;
	}
}
