#include "lem_in.h"

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
	if (!(room = (t_room*)malloc(sizeof(room))))
		return (0);
	if (!(env = (t_env*)malloc(sizeof(env))))
		return (0);
	while ((ret = get_next_line(0, &line)))
	{
		if (i == 0)
			env->nb_ant = ft_atoi(line);
		if (line[1] == ' ')
		{
			temp = ft_strsplit(line, ' ');
			ft_strcpy(room->name, temp[0]);
			room->x = ft_atoi(temp[1]);
			room->y = ft_atoi(temp[2]);
			//ft_strdel(&temp);	
		}
		if (!ft_strcmp(line, "##start"))
		{
			get_next_line(0, &line);
			temp = ft_strsplit(line, ' ');
			ft_strcpy(env->start->name, temp[0]);
			env->start->x = ft_atoi(temp[1]);
			env->start->y = ft_atoi(temp[2]);
		//	ft_strdel(&temp);	
		}
		if (!ft_strcmp(line, "##end"))
		{
			get_next_line(0, &line);
			temp = ft_strsplit(line, ' ');
			ft_strcpy(env->end->name, temp[0]);
			env->end->y = ft_atoi(temp[1]);
			env->end->y = ft_atoi(temp[2]);
			env->end->next = NULL;
		//	ft_strdel(&temp);	
		}
		i++;
		ft_strdel(&line);	
	}
	return (0);
}
