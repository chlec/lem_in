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
		ft_list_push_back(&(env->head_room), env->start);
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
		ft_list_push_back(&(env->head_room), env->end);
		ft_strdel(&line);
	}

}

int		main(void)
{
    int        ret;
    char    *line;
    t_env    *env;
    t_list    *head_temp;
    t_list    *head_path;
    t_room    *room;
    char    **temp;
	t_path	*path;
	t_pipe	*pipe;
   
   	path = NULL;	
    line = NULL;
    head_path = NULL;
    room = NULL;
    if (!(env = (t_env*)malloc(sizeof(t_env))))
        return (0);
	env->head_room = NULL;
	env->head_pipe = NULL;
	get_next_line(0, &line);
    env->nb_ant = ft_atoi(line);
    while ((ret = get_next_line(0, &line)) > 0)
    {
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
        else if (line[1] == '-')
        {
			pipe = (t_pipe*)malloc(sizeof(t_pipe));
            temp = ft_strsplit(line, '-');
            printf("%s     %s\n", temp[0], temp[1]);
            head_temp = env->head_room;
            while (head_temp)
            {
				//room = contenu de head temp == head_room
                room = (t_room*)(head_temp->content);
                if (!ft_strcmp(room->name, temp[0]))
                {
                    pipe->left = room;
                    printf("room de depart = %s\n", pipe->left->name);
                }
                head_temp = head_temp->next;
            }
            head_temp = env->head_room;
            while (head_temp)
            {
				//room = contenu de head temp == head_room
                room = (t_room*)(head_temp->content);
                if (!ft_strcmp(room->name, temp[1]))
                {
                    pipe->right = room;
                    printf("room de depart = %s\n", pipe->right->name);
                }
                head_temp = head_temp->next;
            }
			ft_list_push_back(&(env->head_pipe), pipe);
        }
        ft_strdel(&line);

    }
    /*while (env->head_room)
    {
        room = (t_room*)(env->head_room->content);
        printf("nom de room = %s\n", room->name);
        env->head_room = env->head_room->next;
    }*/
	while (env->head_pipe)
	{
		pipe = (t_pipe*)(env->head_pipe->content);
		if (pipe->left && pipe->right)
		{
       		 printf("nom de path left = %s\t", pipe->left->name);
       	 	printf("nom de path right = %s\n", pipe->right->name);
		}
		env->head_pipe = env->head_pipe->next;
	}
    /*printf("nom de start = %s x = %d y = %d\n", env->start->name, env->start->x, env->start->y);
    printf("nom de end = %s x = %d y = %d\n", env->end->name, env->end->x, env->end->y);*/
    return (0);
}
