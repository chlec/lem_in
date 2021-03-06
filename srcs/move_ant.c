/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_ant.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecalie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 15:53:28 by clecalie          #+#    #+#             */
/*   Updated: 2018/03/20 14:55:58 by clecalie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	init_ant(t_env *env)
{
	t_ant	*l_ant;
	int		i;

	l_ant = NULL;
	i = 0;
	while (i < env->nb_ant)
	{
		if (!(l_ant = (t_ant*)malloc(sizeof(t_ant))))
			exit(0);
		l_ant->num = i + 1;
		l_ant->position = env->start->name;
		l_ant->end = 0;
		ft_list_push_back(&(env->head_ant), l_ant, sizeof(t_ant));
		free(l_ant);
		l_ant = NULL;
		i++;
	}
}

void	find_ant(t_env *env, char *pos_init, char *new_pos)
{
	t_ant	*l_ant;
	t_list	*head_temp;

	head_temp = env->head_ant;
	while (head_temp)
	{
		l_ant = (t_ant*)(head_temp->content);
		if (!ft_strcmp(l_ant->position, pos_init))
		{
			l_ant->position = new_pos;
			return ;
		}
		head_temp = head_temp->next;
	}
}

void	print_ant(t_env *env)
{
	t_ant	*l_ant;
	t_list	*head_temp;
	int		first;

	first = 1;
	head_temp = env->head_ant;
	while (head_temp)
	{
		l_ant = (t_ant*)(head_temp->content);
		if (l_ant->end == 0 && ft_strcmp(l_ant->position, env->start->name))
		{
			if (!first)
				ft_putchar(' ');
			first = 0;
			ft_putchar('L');
			ft_putnbr(l_ant->num);
			ft_putchar('-');
			ft_putstr(l_ant->position);
		}
		if (!ft_strcmp(l_ant->position, env->end->name))
			l_ant->end = 1;
		head_temp = head_temp->next;
	}
	ft_putchar('\n');
}

void	ant_is_moving(t_env *env, int len, t_room *room, t_room *room_after)
{
	if (!ft_strcmp(room_after->name, env->start->name))
	{
		room_after->ant = env->start->ant;
		if (len > env->start->ant + 1)
			return ;
	}
	if (!ft_strcmp(room->name, env->end->name))
		room->ant = env->end->ant;
	if (!ft_strcmp(room->name, env->end->name) && room_after->ant > 0)
	{
		find_ant(env, room_after->name, room->name);
		env->end->ant = env->end->ant + 1;
		room->ant = room->ant + 1;
		room_after->ant = room_after->ant - 1;
		if (!ft_strcmp(room_after->name, env->start->name))
			env->start->ant = env->start->ant - 1;
	}
	else if (room->ant == 0 && room_after->ant > 0)
	{
		find_ant(env, room_after->name, room->name);
		room->ant = room->ant + 1;
		room_after->ant = room_after->ant - 1;
		if (!ft_strcmp(room_after->name, env->start->name))
			env->start->ant = env->start->ant - 1;
	}
}

void	move_ant(t_env *env)
{
	t_list	*head;
	t_list	*head_p;
	t_path	*path;

	path = NULL;
	head = NULL;
	init_ant(env);
	while (env->end->ant < env->nb_ant)
	{
		head_p = env->head_path;
		while (head_p)
		{
			path = (t_path*)(head_p->content);
			head = path->room;
			while (path->room->next)
			{
				ant_is_moving(env, path->len, path->room->content,
	path->room->next->content);
				path->room = path->room->next;
			}
			path->room = head;
			head_p = head_p->next;
		}
		print_ant(env);
	}
}
