/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecalie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/01 14:10:47 by clecalie          #+#    #+#             */
/*   Updated: 2018/03/12 14:26:45 by clecalie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		linked(t_list **p, t_room *left, t_room *right)
{
	t_list	*path;
	t_room	*room;
	t_room	*next;

	path = *p;
	while (path)
	{
		room = (t_room*)(path->content);
		if (path->next && (ft_strequ(room->name, left->name)
					|| ft_strequ(room->name, right->name)))
		{
			next = (t_room*)(path->next->content);
			if (ft_strequ(next->name,
						ft_strequ(room->name, left->name)
						? right->name : left->name))
				return (1);
		}
		path = path->next;
	}
	return (0);
}

int		pipe_exist(t_list *head_pipe, t_room *left, t_room *right)
{
	t_list	*list;
	t_pipe	*pipe;

	list = head_pipe;
	while (list)
	{
		pipe = (t_pipe*)list->content;
		if ((!ft_strcmp(pipe->right->name, right->name)
			&& !ft_strcmp(pipe->left->name, left->name))
				||
			(!ft_strcmp(pipe->right->name, left->name)
				&& !ft_strcmp(pipe->left->name, right->name)))
		{
			pipe->used = 1;
			return (0);
		}
		list = list->next;
	}
	return (0);
}

void	store_room_in_pipe(t_env *env, t_pipe *pipe, char **temp)
{
	t_room	*room;
	t_room	*room2;
	t_list	*head_temp;

	head_temp = env->head_room;
	while (head_temp)
	{
		room = (t_room*)(head_temp->content);
		if (!ft_strcmp(room->name, temp[0]))
			pipe->left = room;
		head_temp = head_temp->next;
	}
	head_temp = env->head_room;
	while (head_temp)
	{
		room2 = (t_room*)(head_temp->content);
		if (!ft_strcmp(room2->name, temp[1]))
			pipe->right = room2;
		head_temp = head_temp->next;
	}
}

int		init_pipe(t_env *env, char *line)
{
	t_pipe	*pipe;
	char	**temp;

	if (!line || (line && line[0] == '\0'))
		return (0);
	pipe = (t_pipe*)malloc(sizeof(t_pipe));
	temp = ft_strsplit(line, '-');
	pipe->used = 0;
	pipe->left = NULL;
	pipe->right = NULL;
	store_room_in_pipe(env, pipe, temp);
	free_double_tab(temp);
	if (pipe->left == NULL || pipe->right == NULL)
	{
		free(pipe);
		return (0);
	}
	if (pipe_exist(env->head_pipe, pipe->left, pipe->right))
	{
		free(pipe);
		return (0);
	}
	ft_list_push_back(&(env->head_pipe), pipe, sizeof(t_pipe));
	free(pipe);
	return (1);
}
