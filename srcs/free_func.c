/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecalie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 14:31:03 by clecalie          #+#    #+#             */
/*   Updated: 2018/03/16 13:24:55 by clecalie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		del_ant(t_env *env, t_list *head_temp, t_list *head, t_ant *l_ant)
{
	//on va jamais dans le else
	if (head == NULL)
	{
		free(l_ant);
		l_ant = NULL;
		free(env->head_ant);
		// Le soucis est a la ligne ci-dessous
		// car env->head_ant = head_temp donc le next existe pas vu qu'on free
		env->head_ant = head_temp->next;
	}
	else
	{
		free(l_ant);
		l_ant = NULL;
		head->next = head_temp->next;
		free(head_temp);
		head_temp = head;
	}
}

void		free_double_tab(char **tab)
{
	int		i;

	if (tab)
	{
		i = 0;
		while (tab[i])
		{
			ft_strdel(&tab[i]);
			i++;
		}
		free(tab);
		tab = NULL;
	}
}

static void	del_all_pipe(t_env *env)
{
	t_list	*tmp;
	t_pipe	*pipe;

	while (env->head_pipe)
	{
		tmp = env->head_pipe->next;
		pipe = (t_pipe*)env->head_pipe->content;
		free(pipe);
		pipe = NULL;
		free(env->head_pipe);
		env->head_pipe = NULL;
		env->head_pipe = tmp;
	}
}

static void	del_all_path(t_env *env)
{
	t_list	*tmp;
	t_path	*path;
	t_list	*tmp2;
	t_room	*room;

	while (env->head_path)
	{
		tmp = env->head_path->next;
		path = (t_path*)env->head_path->content;
		while (path->room)
		{
			tmp2 = path->room->next;
			room = (t_room*)path->room->content;
			free(path->room);
			path->room = NULL;
			free(room);
			room = NULL;
			path->room = tmp2;
		}
		free(path);
		path = NULL;
		free(env->head_path);
		env->head_path = NULL;
		env->head_path = tmp;
	}
}

void		del_env(t_env *env)
{
	t_room	*room;
	t_list	*tmp;

	free(env->start);
	env->start = NULL;
	free(env->end);
	env->end = NULL;
	while (env->head_room)
	{
		tmp = env->head_room->next;
		room = (t_room*)env->head_room->content;
		ft_strdel(&(room->name));
		free(env->head_room);
		env->head_room = NULL;
		free(room);
		room = NULL;
		env->head_room = tmp;
	}
	del_all_pipe(env);
	del_all_path(env);
	free(env);
	env = NULL;
}
