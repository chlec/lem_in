/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecalie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 15:04:49 by clecalie          #+#    #+#             */
/*   Updated: 2018/03/12 15:35:46 by clecalie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H
# include "libft.h"
# include <stdio.h>

enum				e_error
{
	OK,
	NO_PATH,
	NO_END_OR_START,
	INVALID_ANT_NUMBER,
	INVALID_PIPE,
	INVALID_ROOM,
	DOUBLE_PIPE
};

typedef struct		s_ant
{
	int				num;
	char			*position;
}					t_ant;

typedef struct		s_room
{
	char			*name;
	int				x;
	int				y;
	int				ant;
}					t_room;

typedef struct		s_path
{
	t_list			*room;
	int				len;
}					t_path;

typedef struct		s_pipe
{
	t_room	*left;
	t_room	*right;
	int		used;
}					t_pipe;

typedef struct		s_env
{
	t_list			*ant;
	t_room			*start;
	t_room			*end;
	t_list			*head_room;
	t_list			*head_pipe;
	t_list			*head_path;
	t_list			*all_path;
	t_list			*head_ant;
	int				nb_ant;
	enum e_error	error;
	int				lower_size;
}					t_env;

void				ft_list_push_back(t_list **begin_list,
		void *data, size_t len);
void				move_ant(t_env *env);
int					len_double_tab(char **tab);
t_path				*copy_maillon(t_list **p);
int					list_len(t_list **l);
t_room				*get_last_room(t_list **l);
int					room_is_present(t_list	**l, t_room *room);
void				free_double_tab(char **tab);
void				init_room(t_env *env, char *line);
int					check_room(t_env *env, char *str, int x, int y);
int					linked(t_list **p, t_room *left, t_room *right);
int					pipe_exist(t_list *head_pipe, t_room *left, t_room *rigtht);
int					init_pipe(t_env *env, char *line);
void				nb_room_path(t_env *env);
void				init_lowest_path(t_env *env);
void				print_path(t_env *env);
void				create_path(t_env *env, t_path *p);
int					already_found(t_list **l, t_list **p);
int					in_integer(char *argv);
void				del(void *e, size_t size);
void				add_to_head(t_env *env, t_path *path);
void				delete_path(t_path *path);
void				init_lowest_path(t_env *env);
void				print_path(t_env *env);
void				del_ant(t_env *env, t_list *head_temp,
		t_list *head, t_ant *l_ant);
void				free_double_tab(char **tab);
void				del_env(t_env *env);
int					handle_command(t_env *env, char *line);
char				*store_room(t_env *env, char *line);
void				store_pipe(t_env *env);
void				handle_room_error(t_env *env, char *line);
void				display_error(t_env *env);
char				*check_content(void);

#endif
