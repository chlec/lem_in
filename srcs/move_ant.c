/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_ant.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecalie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 15:53:28 by clecalie          #+#    #+#             */
/*   Updated: 2018/03/01 15:43:15 by mdaunois         ###   ########.fr       */
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

void	print_antv2(t_env *env)
{
	t_ant	*l_ant;
	t_list	*head_temp;
	t_list	*head;

	head = NULL;
	head_temp = env->head_ant;
	while (head_temp)
	{
		l_ant = (t_ant*)(head_temp->content);
		if (ft_strcmp(l_ant->position, env->start->name))// && ft_strcmp(l_ant->position, env->end->name))
			printf("L%d-%s ", l_ant->num, l_ant->position);
		//En gros si une fourmi arrive a 0, on la supprime de la chaine
		if (!ft_strcmp(l_ant->position, env->end->name))
		{
		//	printf("la fourmie %d et arriver  ||  ", l_ant->num);
			if (head == NULL || env->head_ant == head_temp)
			{
				env->head_ant = head_temp->next;
			//	free(l_ant);
			}
			else
			{
				head->next = head_temp->next;	
			//	free(l_ant);
			}
		}
		head = head_temp;
	//	head = NULL;
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

void	ant_is_moving(t_env *env, int len, t_room *room, t_room *room_after)
{
//	printf("room %s a %d,room %s a %d\n",room->name, room->ant,room_after->name, room_after->ant);
	if (!ft_strcmp(room_after->name, env->start->name))
	{
		room_after->ant = env->start->ant;
		if (len > env->start->ant + 1)
			return ;
	}
	if (!ft_strcmp(room->name, env->end->name))
	{
		room->ant = env->end->ant; 	
	}
	if (!ft_strcmp(room->name, env->end->name) && room_after->ant > 0)
	{
		//printf("fourmis qui viens de la room %s\n %d\n", room_after->name, room_after->ant);
		find_ant(env, room_after->name, room->name);
		env->end->ant = env->end->ant + 1; 
		room->ant = room->ant + 1;
		room_after->ant = room_after->ant - 1;
		if (!ft_strcmp(room_after->name, env->start->name))
		{
			env->start->ant = env->start->ant - 1; 	
		}
	}
	else if (room->ant == 0 && room_after->ant > 0)
	{
		find_ant(env, room_after->name, room->name);
		room->ant = room->ant + 1;
		room_after->ant = room_after->ant - 1;
		if (!ft_strcmp(room_after->name, env->start->name))
		{
			env->start->ant = env->start->ant - 1; 	
		}
	}
//	printf("room %s a %d,room %s a %d\n",room->name, room->ant, room_after->name, room_after->ant);
//	printf("\n");
}

/*il faut faire touts les chemins possible quant il faut, et afficher la fourmie qui est a la room end*/
void	move_ant(t_env *env)
{
	t_list	*head;
	t_list	*head_p;
	t_path	*path;

	path = NULL;
	head = NULL;
	head_p = NULL;
	init_ant(env);
//	print_ant(env);
	while (env->end->ant < env->nb_ant)
	{
		head_p = env->head_path;
		while (head_p)
		{
			path = (t_path*)(head_p->content);
			head = path->room;
			while (path->room->next)
			{
				ant_is_moving(env, path->len,  path->room->content, path->room->next->content);
				path->room = path->room->next;
			}
			path->room = head;
//			usleep(10000);
//			print_antv2(env);
			head_p = head_p->next;
		}
		print_antv2(env);
//		printf("fourmis fini = %d fourmis total = %d\n", env->end->ant, env->nb_ant);
	}
}





