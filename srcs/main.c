#include "lem_in.h"

void	handle_command(t_env *env, char *line)
{
	char	**temp;
	
	if (!ft_strcmp(line, "##start"))
	{
		get_next_line(0, &line);
		temp = ft_strsplit(line, ' ');
		env->start = (t_room*)malloc(sizeof(t_room));
		env->start->name = temp[0];
		env->start->x = ft_atoi(temp[1]);
		env->start->y = ft_atoi(temp[2]);
		//	ft_strdel(&temp);	
		ft_strdel(&line);
	}
	else if (!ft_strcmp(line, "##end"))
	{
		get_next_line(0, &line);
		temp = ft_strsplit(line, ' ');
		env->end = (t_room*)malloc(sizeof(t_room));
		env->end->name = temp[0];
		env->end->x = ft_atoi(temp[1]);
		env->end->y = ft_atoi(temp[2]);
		//	ft_strdel(&temp);	
		ft_strdel(&line);
	}

}

int		main(void)
{
	int		ret;
	char	*line;
	t_env	*env;
	t_room	*room;
	char	**temp;
	int		i;

	line = NULL;
	i = 0;
	room = NULL;
	if (!(env = (t_env*)malloc(sizeof(t_env))))
		return (0);
	env->head_room = NULL;
	while ((ret = get_next_line(0, &line)) > 0)
	{
		if (i == 0)
			env->nb_ant = ft_atoi(line);
		//ROOM
		if (ft_strlen(line) > 1 && line[1] == ' ')
		{
			if (!(room = (t_room*)malloc(sizeof(t_room))))
				return (0);
			temp = ft_strsplit(line, ' ');
			room->name = temp[0];
			room->x = ft_atoi(temp[1]);
			room->y = ft_atoi(temp[2]);
			ft_list_push_back(&(env->head_room), room);
			room = NULL;
			//ft_strdel(&temp);
		}
		else if (line[0] == '#')
			handle_command(env, line);
		i++;
		ft_strdel(&line);	
	}
	while (env->head_room)
	{
		room = (t_room*)(env->head_room->content);
		printf("nom de room = %s\n", room->name);
		env->head_room = env->head_room->next;
	}
	printf("nom de start = %s x = %d y = %d\n", env->start->name, env->start->x, env->start->y);
	printf("nom de end = %s x = %d y = %d\n", env->end->name, env->end->x, env->end->y);
	return (0);
}
