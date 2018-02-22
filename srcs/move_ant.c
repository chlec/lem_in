/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_ant.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecalie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 15:53:28 by clecalie          #+#    #+#             */
/*   Updated: 2018/02/22 13:19:48 by mdaunois         ###   ########.fr       */
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
		printf("L%d-%s\n", l_ant->num, l_ant->position);
		head_temp = head_temp->next;
	}
}

void	move_ant(t_env *env)
{
	init_ant(env);
	print_ant(env);
/*	while (env->end->nb_ant < env->nb_ant)
	{
		
	}*/
}
