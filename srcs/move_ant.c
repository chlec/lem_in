/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_ant.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecalie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 15:53:28 by clecalie          #+#    #+#             */
/*   Updated: 2018/02/22 12:04:57 by mdaunois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	init_ant(t_env *env)
{
	t_ant	*l_ant;
	t_list	*save_head;
	int		i;

	i = 0;
	save_head = env->head_ant;
	while (i < env->nb_ant)
	{
		l_ant = (t_ant*)malloc(sizeof(t_ant));
		l_ant->num = i + 1;
		l_ant->position = env->start->name;
		ft_list_push_back(&(env->head_ant), l_ant, sizeof(t_ant));
		printf("L%d-%s\n", l_ant->num, l_ant->position);
		l_ant = NULL;
		i++;
		env->head_ant = env->head_ant->next;
	}
	env->head_ant = save_head;
}


void	print_ant(t_env *env)
{
	t_ant	*l_ant;

	while (env->head_ant)
	{
		l_ant = (t_ant*)env->head_ant;
//		printf("L%d-%s\n", l_ant->num, l_ant->position);
		env->head_ant = env->head_ant->next;
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
