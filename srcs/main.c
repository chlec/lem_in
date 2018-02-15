#include "lem_in.h"

int		main(void)
{
	int		ret;
	char	*line;
	t_env	*env;
	char	**temp;
	int		i;

	line = NULL;
	i = 0;
	if (!(env = (t_env*)malloc(sizeof(env))))
		return (0);
	while ((ret = get_next_line(0, &line)))
	{
		if (i == 0)
			env->nb_ant = ft_atoi(line);
		if (!ft_strcmp(line, ##start))
		{
			get_next_line(0, &line);
			temp = ft_strsplit(line, ' ');
			ft_strcpy(env->start->name, temp[0]);
			env->start.x = ft_atoi(temp[1]);
			env->start.x = ft_atoi(temp[2]);
		}
		if (!ft_strcmp(line, ##end))
		{
			get_next_line(0, &line);
			temp = ft_strsplit(line, ' ');
			ft_strcpy(env->end->name, temp[0]);
			env->end.y = ft_atoi(temp[1]);
			env->end.y = ft_atoi(temp[2]);
			env->end->next = NULL;
		}
		i++;
		ft_strdel(&line);	
	}
	return (0);
}
