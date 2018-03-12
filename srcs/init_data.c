/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecalie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 15:09:34 by clecalie          #+#    #+#             */
/*   Updated: 2018/03/12 15:24:56 by clecalie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	detect_room_error(t_env *env, char **split, char *line)
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

char		*store_room(t_env *env, char *line)
{
	int		ret;
	char	**split;

	while ((ret = get_next_line(0, &line)) > 0)
	{
		ft_putendl(line);
		if (len_double_tab((split = ft_strsplit(line, ' '))) == 3
				&& env->error == OK && line[0] != '#' && line[0] != 'L')
			detect_room_error(env, split, line);
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
	return (line);
}

void		store_pipe(t_env *env)
{
	char	*line;
	char	**split;
	int		ret;

	line = NULL;
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
}
