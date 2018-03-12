/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecalie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 14:50:37 by clecalie          #+#    #+#             */
/*   Updated: 2018/03/12 15:02:58 by clecalie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static char	*pass_comment(void)
{
	char	*line;

	line = NULL;
	while (get_next_line(0, &line))
	{
		if (line[0] != '#' || (line[0] != '#' && line[1] != '#'))
			break ;
		else
			ft_putendl(line);
		ft_strdel(&line);
	}
	ft_putendl(line);
	return (line);
}

static int	init_start(t_env *env, char *line)
{
	char	**temp;

	ft_strdel(&line);
	if (env->start)
		return (0);
	line = pass_comment();
	if (len_double_tab((temp = ft_strsplit(line, ' '))) == 3
			&& !ft_strchr(line, '#') && !ft_strchr(line, 'L'))
	{
		env->start = (t_room*)malloc(sizeof(t_room));
		env->start->name = ft_strdup(temp[0]);
		env->start->x = ft_atoi(temp[1]);
		env->start->y = ft_atoi(temp[2]);
		env->start->ant = env->nb_ant;
		ft_list_push_back(&(env->head_room), env->start, sizeof(t_room));
		ft_strdel(&line);
		free_double_tab(temp);
		return (1);
	}
	else
	{
		free_double_tab(temp);
		ft_strdel(&line);
		return (0);
	}
}

static int	init_end(t_env *env, char *line)
{
	char	**temp;

	ft_strdel(&line);
	if (env->end)
		return (0);
	line = pass_comment();
	if (len_double_tab((temp = ft_strsplit(line, ' '))) == 3
			&& !ft_strchr(line, '#') && !ft_strchr(line, 'L'))
	{
		env->end = (t_room*)malloc(sizeof(t_room));
		env->end->name = ft_strdup(temp[0]);
		env->end->x = ft_atoi(temp[1]);
		env->end->y = ft_atoi(temp[2]);
		env->end->ant = 0;
		ft_list_push_back(&(env->head_room), env->end, sizeof(t_room));
		ft_strdel(&line);
		free_double_tab(temp);
		return (1);
	}
	else
	{
		free_double_tab(temp);
		ft_strdel(&line);
		return (0);
	}
}

int			handle_command(t_env *env, char *line)
{
	if (!ft_strcmp(line, "##start"))
		return (init_start(env, line));
	else if (!ft_strcmp(line, "##end"))
		return (init_end(env, line));
	else
		ft_strdel(&line);
	return (1);
}
