/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecalie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 15:53:28 by clecalie          #+#    #+#             */
/*   Updated: 2018/03/01 15:59:54 by clecalie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int        handle_command(t_env *env, char *line)
{
	char    **temp;

	if (!ft_strcmp(line, "##start"))
	{
		ft_strdel(&line);
		if (env->start)
			return (0);
		/*while (line[0] == '#')
		{
			get_next_line(0, &line);
			ft_putendl(line);
		}*/
		while (get_next_line(0, &line))
		{
			if (line[0] != '#' || (line[0] == '#' && line[1] == '#'))
				break;
			else
				ft_putendl(line);
			ft_strdel(&line);
		}
		ft_putendl(line);
		if (len_double_tab((temp = ft_strsplit(line, ' '))) == 3 && !ft_strchr(line, '#') && !ft_strchr(line, 'L'))
		{
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
		ft_strdel(&line);
		if (env->end)
			return (0);
		while (get_next_line(0, &line))
		{
			if (line[0] != '#' || (line[0] == '#' && line[1] == '#'))
				break;
			else
				ft_putendl(line);
			ft_strdel(&line);
		}
		ft_putendl(line);
		if (len_double_tab((temp = ft_strsplit(line, ' '))) == 3 && !ft_strchr(line, '#') && !ft_strchr(line, 'L'))
		{
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
		{
			free_double_tab(temp);
			return (0);
		}
	}
	return (1);
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
	env->error = OK;
	env->lower_size = 1000000;
	return (env);
}

void	del(void *e, size_t size)
{
	(void)size;
	free(e);
	e = NULL;
}

void	del_env(t_env *env)
{
//	t_list	*list;
	t_room	*room;
	t_pipe	*pipe;
	t_list	*tmp;
	t_list	*tmp2;
	t_ant	*ant;
	t_path	*path;

//	ft_strdel(&(env->start->name));
//	free(env->start);
//	ft_strdel(&(env->end->name));
//	free(env->end);
//	list = env->head_room;
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
	while (env->head_ant)
	{
		tmp = env->head_ant->next;
		ant = (t_ant*)env->head_ant->content;
		ft_strdel(&(ant->position));
		free(env->head_ant);
		env->head_ant = NULL;
		free(room);
		room = NULL;
		env->head_ant = tmp;
	}
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
	while (env->head_path)
	{
		tmp = env->head_path->next;
		path = (t_path*)env->head_path->content;
		while (path->room)
		{
			tmp2 = path->room->next;
			room = (t_room*)path->room->content;
		//	ft_strdel(&(room->name));
			free(path->room);
			path->room = NULL;
			free(room);
			room = NULL;
			path->room = tmp2;
		}
		free(env->head_path);
		env->head_path = NULL;
		env->head_path = tmp;
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
/*	if ((ret = get_next_line(0, &line) <= 0))
	{
			ft_strdel(&line);
			ft_putstr_fd("Error: No content\n", 2);
			return (0);	
	}
*/	while ((ret = get_next_line(0, &line)))
	{
		ft_putendl(line);
		if (line[0] != '#')
			break ;
	}
	if ((ret <= 0))
	{
		ft_strdel(&line);
		ft_putstr_fd("Error: No content\n", 2);
		return (0);
	}
	if (in_integer(line) == 0 || ft_atoi(line) <= 0)
		env->error = INVALID_ANT_NUMBER;
	env->nb_ant = ft_atoi(line);
		ft_strdel(&line);
	while ((ret = get_next_line(0, &line)) > 0)
	{
		//ROOM
		ft_putendl(line);
		if (env->error == OK && len_double_tab((split = ft_strsplit(line, ' '))) == 3 && line[0] != '#' && line[0] != 'L')
		{
			if (!in_integer(split[1]) || !in_integer(split[2]))
				env->error = INVALID_ROOM;
			else if (check_room(env, split[0], ft_atoi(split[1]), ft_atoi(split[2])) == 1)
				env->error = INVALID_ROOM;
			else if (env->end && !ft_strcmp(split[0], env->end->name))
				env->error = INVALID_ROOM;
			else if (env->start && !ft_strcmp(split[0], env->start->name))
				env->error = INVALID_ROOM;
			else	
				init_room(env, line);
			free_double_tab(split);
			ft_strdel(&line);
		}
		else if (env->error == OK && line[0] == '#')
		{
			free_double_tab(split);
			if (handle_command(env, line) == 0)
			{
				ft_strdel(&line);
				env->error = INVALID_ROOM;
			}
		}
		else
		{
			free_double_tab(split);
			if (line[0] == 'L')
				env->error = INVALID_ROOM;
			break;
		}
	}
	if (!env->head_room)
		env->error = INVALID_ROOM;
	if (env->start == NULL || env->end == NULL)
		env->error = NO_END_OR_START;
	if (env->error == OK && init_pipe(env, line) == 0)
		env->error = DOUBLE_PIPE;
	ft_strdel(&line);
	while ((ret = get_next_line(0, &line)) > 0)
	{
		ft_putendl(line);
		if (line[0] == '#')
			;
		else if (env->error == OK && len_double_tab((split = ft_strsplit(line, '-'))) == 2)
		{
			//	env->error = INVALID_PIPE;
			if (init_pipe(env, line) == 0)
				env->error = INVALID_PIPE;
		}
		else
			env->error = INVALID_PIPE;
		free_double_tab(split);
		ft_strdel(&line);
	}
	ft_putchar('\n');
	if (env->error == OK || env->error == INVALID_PIPE)
		create_path(env, NULL);
	if ((env->error == OK || env->error == INVALID_PIPE) && env->head_path == NULL)
		env->error = NO_PATH;
	if (env->error == OK || env->error == INVALID_PIPE)
	{
		if (env->error == INVALID_PIPE)
			ft_putstr("Error: Acquisition non completee\n");
		nb_room_path(env);
		init_lowest_path(env);
		print_path(env);
//		printf("taille plus petit chemin = %d\n", env->lower_size);
		move_ant(env);
	}
	else
	{
		if (env->error == NO_END_OR_START)
			ft_putstr_fd("Error: No start or no end\n", 1);
		else if (env->error == INVALID_ANT_NUMBER)
			ft_putstr_fd("Error: Invalid ant number\n", 2);
		else if (env->error == NO_PATH)
			ft_putstr_fd("Error: No path\n", 2);
		else if (env->error == INVALID_PIPE)
			ft_putstr_fd("Error: Invalid pipe\n", 2);
		else if (env->error == INVALID_ROOM)
			ft_putstr_fd("Error: Invalid room\n", 2);
		else if (env->error == DOUBLE_PIPE)
			ft_putstr_fd("Error: Pipe in double\n", 2);
		return (0);
	}
	printf("add de env = %p\n", env->head_room);
	del_env(env);
	while (1);
	return (0);
}
