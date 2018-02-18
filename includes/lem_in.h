#ifndef LEM_IN_H
# define LEM_IN_H
# include "libft.h"
# include <stdio.h>

typedef struct		s_room
{
	char			*name;
	int				x;
	int				y;
}					t_room;

typedef struct		s_path
{
	t_list			*room;
	int				len;
}					t_path;

typedef struct		s_ant
{
	int				num;
	int				room;
}					t_ant;

typedef struct		s_pipe
{
	t_room	*left;
	t_room	*right;
}					t_pipe;

typedef struct		s_env
{
	t_ant	*ant;
	t_room	*start;
	t_room	*end;
	t_list	*head_room;
	t_list	*head_pipe;
	t_list	*head_path;
	int		nb_ant;
}					t_env;

void				ft_list_push_back(t_list **begin_list, void *data, size_t len);

#endif
