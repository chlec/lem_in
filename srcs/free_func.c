/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecalie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 14:31:03 by clecalie          #+#    #+#             */
/*   Updated: 2018/03/20 14:31:26 by clecalie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

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

static void	del_all_ant(t_env *env)
{
	t_list	*tmp;
	t_ant	*ant;

	while (env->head_ant)
	{
		tmp = env->head_ant->next;
		ant = (t_ant*)env->head_ant->content;
		free(ant);
		ant = NULL;
		free(env->head_ant);
		env->head_ant = NULL;
		env->head_ant = tmp;
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
	del_all_ant(env);
	free(env);
	env = NULL;
}
