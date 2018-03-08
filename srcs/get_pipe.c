/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecalie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/01 14:10:47 by clecalie          #+#    #+#             */
/*   Updated: 2018/03/08 15:39:56 by mdaunois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int     linked(t_list **p, t_room *left, t_room *right)
{
	t_list  *path;
	t_room  *room;
	t_room  *next;

	path = *p;
	while (path)
	{
		room = (t_room*)(path->content);
		if (path->next && (ft_strequ(room->name, left->name) || ft_strequ(room->name, right->name)))
		{
			next = (t_room*)(path->next->content);
			if (ft_strequ(next->name, ft_strequ(room->name, left->name) ? right->name : left->name))
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
//			printf("ICI\n");
			return (0);
		}
		list = list->next;
	}
	return (0);
}

int		init_pipe(t_env *env, char *line)
{
	t_pipe *pipe;
	t_room *room;
	t_room *room2;
	char	**temp;
	t_list	*head_temp;

	pipe = (t_pipe*)malloc(sizeof(t_pipe));
	if (!line)
		return (0);
	temp = ft_strsplit(line, '-');
	head_temp = env->head_room;
	pipe->used = 0;
	pipe->left = NULL;
	while (head_temp)
	{
		room = (t_room*)(head_temp->content);
		if (!ft_strcmp(room->name, temp[0]))
			pipe->left = room;
		else 
			return (0);
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
	free_double_tab(temp);
	if (pipe->left == NULL || pipe->right == NULL)
	{
		free(pipe);
//		ft_strdel(&line);
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
