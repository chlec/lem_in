/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecalie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 15:53:28 by clecalie          #+#    #+#             */
/*   Updated: 2018/03/20 15:25:19 by mdaunois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			in_integer(char *argv)
{
	int		nb;
	char	*str_nbr;
	int		i;

	i = 0;
	nb = ft_atoi(argv);
	str_nbr = ft_itoa(nb);
	while ((argv[i] == '0' || argv[i] == '+') && argv[i + 1])
		i++;
	if (argv[i] == str_nbr[0])
	{
		while(argv[++i])
		{
			if (!ft_isdigit(argv[i]))
			{
				ft_strdel(&str_nbr);
				return (0);
			}
		}
		ft_strdel(&str_nbr);
		return (1);
	}
	ft_strdel(&str_nbr);
	return (0);
}

t_env		*init_env(void)
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

void		del(void *e, size_t size)
{
	(void)size;
	free(e);
	e = NULL;
}

static void	resolve(t_env *env, int argc, char **argv)
{
	if (env->error == OK || env->error == INVALID_PIPE)
		create_path(env, NULL);
	if ((env->error == OK || env->error == INVALID_PIPE)
			&& env->head_path == NULL)
		env->error = NO_PATH;
	if (env->error == OK || env->error == INVALID_PIPE)
	{
		if (env->error == INVALID_PIPE)
			ft_putstr_fd("Error: Parsing stopped before the end\n", 2);
		nb_room_path(env);
		init_lowest_path(env);
		if (argc == 2 && ft_strequ(argv[1], "-p"))
		{
			print_path(env, 0);
			ft_putchar('\n');
		}
		move_ant(env);
	}
	else
		display_error(env);
}

int			main(int argc, char **argv)
{
	char	*line;
	t_env	*env;

	line = NULL;
	if (!(line = check_content()))
		return (0);
	env = init_env();
	if (in_integer(line) == 0 || ft_atoi(line) <= 0)
		env->error = INVALID_ANT_NUMBER;
	env->nb_ant = ft_atoi(line);
	ft_strdel(&line);
	line = store_room(env, line);
	handle_room_error(env, line);
	ft_strdel(&line);
	store_pipe(env);
	ft_putchar('\n');
	resolve(env, argc, argv);
	del_env(env);
	return (0);
}
