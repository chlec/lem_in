/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecalie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 15:53:28 by clecalie          #+#    #+#             */
/*   Updated: 2018/03/12 14:50:59 by clecalie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

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

t_env	*init_env(void)
{
	t_env	*env;

	if (!(env = (t_env*)malloc(sizeof(t_env))))
		return (0);
	env->start = NULL;
	env->end = NULL;
	env->head_room = NULL;
	env->head_pipe = NULL;
	env->head_path = NULL;
	env->all_path = NULL;
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

int		main(void)
{
	int		ret;
	char	*line;
	t_env	*env;
	char	**split;

	line = NULL;
	env = init_env();
	while ((ret = get_next_line(0, &line)))
	{
		ft_putendl(line);
		if (line[0] != '#')
			break ;
		ft_strdel(&line);
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
		ft_putendl(line);
		if (len_double_tab((split = ft_strsplit(line, ' '))) == 3
				&& env->error == OK && line[0] != '#' && line[0] != 'L')
		{
			if (!in_integer(split[1]) || !in_integer(split[2]))
				env->error = INVALID_ROOM;
			else if (check_room(env, split[0], ft_atoi(split[1]),
						ft_atoi(split[2])) == 1)
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
				env->error = INVALID_ROOM;
		}
		else
		{
			free_double_tab(split);
			if (line[0] == 'L')
				env->error = INVALID_ROOM;
			break ;
		}
		line = NULL;
	}
	if (!env->head_room)
		env->error = INVALID_ROOM;
	if (env->error == OK && (env->start == NULL || env->end == NULL))
		env->error = NO_END_OR_START;
	if (env->error == OK && init_pipe(env, line) == 0)
		env->error = DOUBLE_PIPE;
	ft_strdel(&line);
	while ((ret = get_next_line(0, &line)) > 0)
	{
		ft_putendl(line);
		if (line[0] == '#')
			;
		else if (len_double_tab((split = ft_strsplit(line, '-'))) == 2
				&& env->error == OK)
		{
			free_double_tab(split);
			if (init_pipe(env, line) == 0)
				env->error = INVALID_PIPE;
		}
		else
		{
			free_double_tab(split);
			if (env->error == OK)
				env->error = INVALID_PIPE;
		}
		ft_strdel(&line);
	}
	ft_putchar('\n');
	if (env->error == OK || env->error == INVALID_PIPE)
	{
		create_path(env, NULL);
	}
	if ((env->error == OK || env->error == INVALID_PIPE)
			&& env->head_path == NULL)
		env->error = NO_PATH;
	if (env->error == OK || env->error == INVALID_PIPE)
	{
		if (env->error == INVALID_PIPE)
			ft_putstr_fd("Error: Acquisition non completee\n", 2);
		nb_room_path(env);
		init_lowest_path(env);
		print_path(env);
		move_ant(env);
	}
	else
	{
		if (env->error == NO_END_OR_START)
			ft_putstr_fd("Error: No start or no end\n", 2);
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
	}
	del_env(env);
	while (1);
	return (0);
}
