/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_ant.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecalie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 15:53:28 by clecalie          #+#    #+#             */
/*   Updated: 2018/02/22 15:50:31 by mdaunois         ###   ########.fr       */
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
		l_ant->position = env->start->name;
		ft_list_push_back(&(env->head_ant), l_ant, sizeof(t_ant));
		l_ant = NULL;
		i++;
	}
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
	t_path *path;
	t_list	*head_temp;
	t_room *room;
	t_list *head;
	t_room *room_after;
	int i;

	i = 0;
	head_temp = env->head_path;
	path = NULL;
	room = NULL;
	head = NULL;
	init_ant(env);
	print_ant(env);
	path = (t_path*)(head_temp->content);
	head = path->room;
//	printf("%d\n", env->nb_ant);
	while (env->end->ant != env->nb_ant)
//	while (i < 5)
	{
		path = (t_path*)(head_temp->content);
		path->room = head;
		while (path->room->next)
		{
			room = (t_room*)(path->room->content);
			room_after = (t_room*)(path->room->next->content);
			if (!ft_strcmp(room->name, env->end->name) && room_after->ant > 0)
			{
				printf("une fourmie sauver\n");
				env->end->ant = env->end->ant + 1; 
				room->ant = room->ant + 1;
				room_after->ant = room_after->ant - 1;
			}
			else if (room->ant == 0 && room_after->ant > 0)
			{
				printf("une fourmie bouge\n");
				room->ant = room->ant + 1;
				room_after->ant = room_after->ant - 1;
			}
//			printf("fourmise dans END = %d", env->end->ant);
			printf("dans la room %s, il y a %d fourmis  ", room->name, room->ant);
			printf("et la suivant  %s, il y a %d fourmis\n", room_after->name, room_after->ant);
			path->room = path->room->next;
		}
		printf("------------------\n");
		i++;
	}

/*	while (env->end->nb_ant < env->nb_ant)
	{
		
	}*/
}
