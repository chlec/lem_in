/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecalie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 15:53:28 by clecalie          #+#    #+#             */
/*   Updated: 2018/02/28 10:56:42 by clecalie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int        handle_command(t_env *env, char *line)
{
	char    **temp;

	if (!ft_strcmp(line, "##start"))
	{
		if (env->start)
			return (0);
		//	while (line[0] == '#')
		//	{
		get_next_line(0, &line);
		ft_putendl(line);
		//	}
		//    	ft_putendl(line);
		if (len_double_tab(ft_strsplit(line, ' ')) == 3 && !ft_strchr(line, '#') && !ft_strchr(line, 'L'))
		{
			temp = ft_strsplit(line, ' ');
			env->start = (t_room*)malloc(sizeof(t_room));
			env->start->name = ft_strdup(temp[0]);
			env->start->x = ft_atoi(temp[1]);
			env->start->y = ft_atoi(temp[2]);
			env->start->ant = env->nb_ant;
			//    ft_strdel(&temp);
			ft_list_push_back(&(env->head_room), env->start, sizeof(t_room));
			ft_strdel(&line);
			free_double_tab(temp);
		}
		else
			return (0);
	}
	else if (!ft_strcmp(line, "##end"))
	{
		if (env->end)
			return (0);
		//	while (line[0] == '#')
		//	{
		get_next_line(0, &line);
		ft_putendl(line);
		//	}
		//      	ft_putendl(line);
		//get_next_line(0, &line);
		//ft_putendl(line);
		if (len_double_tab(ft_strsplit(line, ' ')) == 3 && !ft_strchr(line, '#') && !ft_strchr(line, 'L'))
		{
			temp = ft_strsplit(line, ' ');
			env->end = (t_room*)malloc(sizeof(t_room));
			env->end->name = ft_strdup(temp[0]);
			env->end->x = ft_atoi(temp[1]);
			env->end->y = ft_atoi(temp[2]);
			env->end->ant = 0;
			//    ft_strdel(&temp);
			ft_list_push_back(&(env->head_room), env->end, sizeof(t_room));
			ft_strdel(&line);
			free_double_tab(temp);
		}
		else
			return (0);
	}
	return (1);
}

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

int		already_found(t_list **l, t_list **p)
{
	t_list	*all_path;
	t_path	*path;
	t_list	*new_path;
	t_room	*room1;
	//	t_room	*room2;

	all_path = *l;

	while (all_path)
	{
		path = (t_path*)all_path->content;
		new_path = *p;
		while (new_path)
		{
			room1 = (t_room*)new_path->content;
			//			room2 = (t_room*)new_path->next->content;
			if (room_is_present((&path->room), room1))
				return (1);
			new_path = new_path->next;
		}
		all_path = all_path->next;
	}
	return (0);
}

void	create_path(t_env *env, t_path *p)
{
	t_path	*path;
	t_list	*pipe_list;
	t_room	*room1;
	t_pipe	*pipe;
	t_list	*all_path;

	/*
	 * Faire de la recursive!
	 * En gros si on a 0-4 on fait tout les chemin possible a partir de 0-4 et ainsi de suite
	 * */
	pipe_list = env->head_pipe;
	room1 = NULL;
	all_path = NULL;
	while (pipe_list)
	{
		pipe = (t_pipe*)pipe_list->content;
		if (!p && !pipe->used && (ft_strequ(pipe->left->name, env->end->name) || ft_strequ(pipe->right->name, env->end->name)))
		{
			path = (t_path*)malloc(sizeof(t_path));
			path->room = NULL;
			path->len = 0;
			//On met toujours le ##end en 1er sur le path
			//	printf("Debut de path, on met %s et %s\n", pipe->left->name, pipe->right->name);
			ft_list_push_back(&(path->room), ft_strequ(pipe->left->name, env->end->name) ? pipe->left : pipe->right, sizeof(t_room));
			ft_list_push_back(&(path->room), ft_strequ(pipe->left->name, env->end->name) ? pipe->right : pipe->left, sizeof(t_room));
			path->len += 2;
			pipe->used = 1;
			if (ft_strequ(get_last_room(&(path->room))->name, env->start->name) && !already_found(&(env->head_path), &(path->room)))
			{
				//printf("Ajout du path au head\n");
				ft_list_push_back(&(env->head_path), path, sizeof(t_path));
				return create_path(env, NULL);
			}
			return create_path(env, path);
		}
		else if (p && !pipe->used)
		{
			path = copy_maillon(&(p->room));
			//the loop behind break the linked list
			room1 = get_last_room(&(p->room));
			if ((ft_strequ(room1->name, pipe->right->name) || ft_strequ(room1->name, pipe->left->name)))
			{
				//printf("on ajoute %s\n", ft_strequ(room1->name, pipe->left->name) ? pipe->right->name : pipe->left->name);
				//	usleep(500000);
				if (ft_strequ(room1->name, env->end->name) || ft_strequ(room1->name, env->start->name))
					return create_path(env, NULL);
				ft_list_push_back(&(path->room), ft_strequ(room1->name, pipe->left->name) ? pipe->right : pipe->left, sizeof(t_room));
				p->len++;
				//Supprimer la ligne du dessous?
				pipe->used = 1;
				create_path(env, path);
			}
			if (ft_strequ(get_last_room(&(path->room))->name, env->start->name) && !already_found(&(env->head_path), &(path->room)))
			{
				//printf("Ajout du path au head\n");
				ft_list_push_back(&(env->head_path), path, sizeof(t_path));
				return create_path(env, NULL);
			}
		}
		pipe_list = pipe_list->next;
	}
}

int		in_integer(char *argv)
{
	int		nb;
	char	*str_nbr;
	int		i;

	i = 0;
	nb = ft_atoi(argv);
	str_nbr = ft_itoa(nb);
	while ((argv[i] == '0' || argv[i] == '+') && argv[i + 1])
	{
		i++;
	}
	if (argv[i] == str_nbr[0])
	{
		ft_strdel(&str_nbr);
		return (1);
	}
	ft_strdel(&str_nbr);
	return (0);
}

void	init_room(t_env *env, char *line)
{
	t_room 	*room;
	char	**temp;

	if (!(room = (t_room*)malloc(sizeof(t_room))))
		return ;
	temp = ft_strsplit(line, ' ');
	room->name = temp[0];
	room->x = ft_atoi(temp[1]);
	room->y = ft_atoi(temp[2]);
	room->ant = 0;
	ft_list_push_back(&(env->head_room), room, sizeof(t_room));
	room = NULL;
}

int		init_pipe(t_env *env, char *line)
{
	t_pipe *pipe;
	t_room *room;
	char	**temp;
	t_list	*head_temp;

	pipe = (t_pipe*)malloc(sizeof(t_pipe));
	temp = ft_strsplit(line, '-');
	head_temp = env->head_room;
	pipe->used = 0;
	pipe->left = NULL;
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
		room = (t_room*)(head_temp->content);
		if (!ft_strcmp(room->name, temp[1]))
			pipe->right = room;
		head_temp = head_temp->next;
	}
	if (pipe->left == NULL || pipe->right == NULL)
	{
		ft_strdel(&line);
		return (0);
	}
	ft_list_push_back(&(env->head_pipe), pipe, sizeof(t_pipe));
	return (1);
}


t_env	*init_env()
{
	t_env	*env;

	if (!(env = (t_env*)malloc(sizeof(t_env))))
		return (0);
	env->start = NULL;
	env->end = NULL;
	env->head_room = NULL;
	env->head_pipe = NULL;
	env->head_path = NULL;
	env->head_ant = NULL;
	return (env);
}

void	del(void *e, size_t size)
{
	(void)size;
	free(e);
	e = NULL;
}

void	del_env(t_env **environment)
{
	t_env	*env;
	t_list	*list;
	t_room	*room;
	t_pipe	*pipe;
	t_list	*tmp;

	env = *environment;
	ft_strdel(&(env->start->name));
	free(env->start);
	ft_strdel(&(env->end->name));
	free(env->end);
	list = env->head_room;
	while (list)
	{
		tmp = list->next;
		room = (t_room*)list->content;
		//ft_strdel(&(room->name));
		free(list);
		list = NULL;
		free(room);
		room = NULL;
		list = tmp;
	}
//	ft_lstdel(&(env->head_room), del);
	list = env->head_pipe;
	while (list)
	{
		tmp = list->next;
		pipe = (t_pipe*)list->content;
		//ft_strdel(&(room->name));
		free(list);
		if (pipe->left)
		{
	//	free(pipe->left);
		pipe->left = NULL;
		}
		if (pipe->right)
		{
	//	free(pipe->right);
		pipe->right = NULL;
		}
		free(pipe);
		pipe = NULL;
		list = tmp;
	}
//	ft_lstdel(&(env->head_pipe), del);
	ft_lstdel(&(env->head_path), del);
	ft_lstdel(&(env->head_ant), del);
}

void		nb_room_path(t_env *env)
{	
	t_path	*path;
	t_room	*room;
	t_list	*head_p;
	t_list	*head_r;
	int 	len;

	len = 0;
	head_p = env->head_path;
	head_r = head_p->content;;
	while (head_p)
	{
		len = 0;
		path = (t_path*)(head_p->content);
		head_r = path->room;
		while (head_r)
		{
			room = (t_room*)(head_r->content);
			head_r = head_r->next;
			len++;
		}
		path->len = len;
		head_p = head_p->next;
	}
}

void		print_path(t_env *env)
{	
	t_path	*path;
	t_room	*room;
	t_list	*head_p;
	t_list	*head_r;

	head_p = env->head_path;
	head_r = head_p->content;;
	while (head_p)
	{
		path = (t_path*)(head_p->content);
		head_r = path->room;
		printf("nombre de room = %d\n", path->len);
		while (head_r)
		{
			room = (t_room*)(head_r->content);
			printf("chemin: %s nb_ant = %d \n", room->name, room->ant);
			head_r = head_r->next;
		}
		printf("------\n");
		head_p = head_p->next;
	}
}

int		main(void)
{
	int		ret;
	char	*line;
	t_env	*env;
	char	**split;

	line = NULL;
	env = init_env();
//	if (!(env = (t_env*)malloc(sizeof(t_env))))
//		return (0);
/*	env->start = NULL;
	env->end = NULL;
	env->head_room = NULL;
	env->head_pipe = NULL;
	env->head_path = NULL;
	env->head_ant = NULL;*/
	if (get_next_line(0, &line) <= 0)
	{
		ft_putstr_fd("Error\n", 2);
//		ft_strdel(&line);
		return (0);
	}
	//    get_next_line(0, &line);
	if (in_integer(line) == 0)
	{
		ft_putstr_fd("Error\n", 2);
		ft_strdel(&line);
		return (0);
	}
	env->nb_ant = ft_atoi(line);
	ft_putnbr(env->nb_ant);
	ft_putchar('\n');
	while ((ret = get_next_line(0, &line)) > 0)
	{
		//ROOM
		ft_putendl(line);
		if (len_double_tab((split = ft_strsplit(line, ' '))) == 3 && line[0] != '#' && line[0] != 'L')
		{
			init_room(env, line);
			free_double_tab(split);
		}
		else if (line[0] == '#')
		{
			if (handle_command(env, line) == 0)
			{
				ft_strdel(&line);
				break;
			}
		}
		else if (len_double_tab((split = ft_strsplit(line, '-'))) == 2)
		{
			free_double_tab(split);
			if (init_pipe(env, line) == 0)
				break;
		}
		else
		{
			ft_strdel(&line);
			break;
		}
		ft_strdel(&line);
	}
	ft_putchar('\n');
	if (env->start == NULL || env->end == NULL)
	{
		ft_putstr_fd("Error\nno start or no end\n", 2);
		return (0);
	}
	create_path(env, NULL);
	if (env->head_path == NULL)
	{
		ft_putstr_fd("Error\nno path\n", 2);
		return (0);
	}
	nb_room_path(env);
	print_path(env);
	move_ant(env);
	del_env(&env);
//	while (1);
	return (0);
}
