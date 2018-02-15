/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecalie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 12:27:33 by clecalie          #+#    #+#             */
/*   Updated: 2018/02/15 13:26:30 by clecalie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H
# include "libft.h"
# include <stdio.h>

typedef struct		s_room
{
	char			*name;
	int				x;
	int				y;
	struct s_room	*next;
}					t_room;

typedef struct		s_path
{
	t_room			*room;
	int				len;
	struct s_path	*next;
}					t_path;

typedef struct		s_ant
{
	int				num;
	int				room;
	struct s_ant	*next;
}					t_ant;

typedef struct		s_env
{
	t_ant	*ant;
	t_path	*path;
	int		nb_ant;
}					t_env;

#endif
