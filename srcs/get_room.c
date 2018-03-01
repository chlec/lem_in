/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_room.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecalie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/01 14:08:13 by clecalie          #+#    #+#             */
/*   Updated: 2018/03/01 15:45:58 by mdaunois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	init_room(t_env *env, char *line)
{
	t_room 	*room;
	char	**temp;

	if (!(room = (t_room*)malloc(sizeof(t_room))))
		return ;
	temp = ft_strsplit(line, ' ');
	room->name = ft_strdup(temp[0]);
	room->x = ft_atoi(temp[1]);
	room->y = ft_atoi(temp[2]);
	room->ant = 0;
	ft_list_push_back(&(env->head_room), room, sizeof(t_room));
	free(room);
	room = NULL;
	free_double_tab(temp);
}

int		check_room(t_env *env, char *str, int x, int y)
{
	int		check;
	t_list	*head;
	t_room	*room;

	check = 0;
	head = env->head_room;
	while (head)
	{
		room = (t_room*)head->content;
		if (!ft_strcmp(room->name, str))
				return (1);
		head = head->next;
	}
	head = env->head_room;
	while (head)
	{
		room = (t_room*)head->content;
		if (room->x == x && room->y == y)
				return (1);
		head = head->next;
	}
	return (0);
}
