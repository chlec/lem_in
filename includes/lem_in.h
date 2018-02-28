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
	INVALID_ROOM
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
	t_list	*ant;
	t_room	*start;
	t_room	*end;
	t_list	*head_room;
	t_list	*head_pipe;
	t_list	*head_path;
	t_list	*head_ant;
	int		nb_ant;
	enum e_error	error;
	int		lower_size;
}					t_env;

void				ft_list_push_back(t_list **begin_list, void *data, size_t len);
void				move_ant(t_env *env);
int 				len_double_tab(char **tab);
t_path				*copy_maillon(t_list **p);
int     			list_len(t_list **l);
t_room				*get_last_room(t_list **l);
int					room_is_present(t_list	**l, t_room *room);
void				free_double_tab(char **tab);

#endif
