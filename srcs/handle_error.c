/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecalie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 15:26:42 by clecalie          #+#    #+#             */
/*   Updated: 2018/03/20 15:34:16 by clecalie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

char	*check_content(void)
{
	int		ret;
	char	*line;

	line = NULL;
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
	return (line);
}

void	handle_room_error(t_env *env, char *line)
{
	if (env->error == OK && !env->head_room)
		env->error = INVALID_ROOM;
	if (env->error == OK && (env->start == NULL || env->end == NULL))
		env->error = NO_END_OR_START;
	if (env->error == OK && init_pipe(env, line) == 0)
		env->error = DOUBLE_PIPE;
}

void	display_error(t_env *env)
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
