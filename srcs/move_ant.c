/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_ant.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecalie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 15:53:28 by clecalie          #+#    #+#             */
/*   Updated: 2018/02/22 16:43:01 by mdaunois         ###   ########.fr       */
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
		if(!(l_ant = (t_ant*)malloc(sizeof(t_ant))))
			return ;
		l_ant->num = i + 1;
		//l_ant->position = env->start->name;
		l_ant->position = env->start->name;
		ft_list_push_back(&(env->head_ant), l_ant, sizeof(t_ant));
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
	//		printf("L%d-%s va dans %s\n", l_ant->num, l_ant->position, new_pos);
			l_ant->position = new_pos;
			return ;
		}
		head_temp = head_temp->next;
	}
}

void	print_antv2(t_env *env)
{
	t_ant	*l_ant;
	t_list	*head_temp;

	head_temp = env->head_ant;

	while (head_temp)
	{
		l_ant = (t_ant*)(head_temp->content);
		if (ft_strcmp(l_ant->position, env->start->name) && ft_strcmp(l_ant->position, env->end->name))
			printf("L%d-%s ", l_ant->num, l_ant->position);
		head_temp = head_temp->next;
	}
	printf("\n");
}

void	print_ant(t_env *env)
{
	t_ant	*l_ant;
	t_list	*head_temp;

	head_temp = env->head_ant;

	while (head_temp)
	{
		l_ant = (t_ant*)(head_temp->content);
		printf("L%d-%s ", l_ant->num, l_ant->position);
		head_temp = head_temp->next;
	}
	printf("\n");
}

void	move_ant(t_env *env)
{
	t_list	*head;
	t_path	*path;
	t_room	*room;
	t_room	*room_after;

	path = NULL;
	room = NULL;
	head = NULL;
	init_ant(env);
	print_antv2(env);
	path = (t_path*)(env->head_path->content);
	head = path->room;
	while (env->end->ant != env->nb_ant)
	{
		path = (t_path*)(env->head_path->content);
		path->room = head;
		while (path->room->next)
		{
			room = (t_room*)(path->room->content);
			room_after = (t_room*)(path->room->next->content);
			if (!ft_strcmp(room->name, env->end->name) && room_after->ant > 0)
			{
				find_ant(env, room_after->name, room->name);
				env->end->ant = env->end->ant + 1; 
				room->ant = room->ant + 1;
				room_after->ant = room_after->ant - 1;
			}
			else if (room->ant == 0 && room_after->ant > 0)
			{
				find_ant(env, room_after->name, room->name);
				room->ant = room->ant + 1;
				room_after->ant = room_after->ant - 1;
			}
			path->room = path->room->next;
		}
	print_antv2(env);
	}

/*	while (env->end->nb_ant < env->nb_ant)
	{
		
	}*/
}
