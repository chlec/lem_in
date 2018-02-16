#include "lem_in.h"

int len_double_tab(char **tab)
{
    int i;
    
    i = 0;
    if (!tab)
        return (0);
    while (tab[i])
    {
        i++;
    }
    return (i);
}

int        handle_command(t_env *env, char *line)
{
    char    **temp;
    
    if (!ft_strcmp(line, "##start"))
    {
        get_next_line(0, &line);
        if (len_double_tab(ft_strsplit(line, ' ')) == 3 && !strchr(line, '#') && !strchr(line, 'L'))
        {
            temp = ft_strsplit(line, ' ');
            env->start = (t_room*)malloc(sizeof(t_room));
            env->start->name = temp[0];
            env->start->x = ft_atoi(temp[1]);
            env->start->y = ft_atoi(temp[2]);
            //    ft_strdel(&temp);
            ft_list_push_back(&(env->head_room), env->start, sizeof(t_room));
            ft_strdel(&line);
        }
        else
            return (0);
    }
    else if (!ft_strcmp(line, "##end"))
    {
        get_next_line(0, &line);
        if (len_double_tab(ft_strsplit(line, ' ')) == 3 && !strchr(line, '#') && !strchr(line, 'L'))
        {
            temp = ft_strsplit(line, ' ');
            env->end = (t_room*)malloc(sizeof(t_room));
            env->end->name = temp[0];
            env->end->x = ft_atoi(temp[1]);
            env->end->y = ft_atoi(temp[2]);
            //    ft_strdel(&temp);
            ft_list_push_back(&(env->head_room), env->end, sizeof(t_room));
            ft_strdel(&line);
        }
        else
            return (0);
    }
    return (1);
}

t_path	*copy_maillon(t_list **p)
{
	t_path	*ret;
	t_list	*list;

	list = *p;
	ret = malloc(sizeof(t_path));
	ret->room = NULL;
	ret->len = 0;
	while (list)
	{
		ft_list_push_back(&(ret->room), list->content, sizeof(t_room));
		ret->len++;
		list = list->next;
	}
	return (ret);	
}

void	cree_path(t_env *env)
{
	t_path	*path;
	t_list	*PIPE;
	t_room	*room1;
	//t_room	*room2;
	t_pipe	*pipe2;
	t_path	*path_temp;

	path = (t_path*)malloc(sizeof(t_path));
	path->room = NULL;
	path->len = 0;
	PIPE = env->head_pipe;
	while (PIPE)
	{
		pipe2 = (t_pipe*)(PIPE->content);
		path_temp = copy_maillon(&(path->room));
		room1 = NULL;
		//Idee: On parcourt path_temp jusquau dernier et apres on check si on a une suite
		while (path_temp->room && !room1)
		{	
			if (path_temp->room->next == NULL)
				room1 = (t_room*)path_temp->room->content;
			path_temp->room = path_temp->room->next;
		}
		if (room1 != NULL)
		{
			printf("dernier elemm %s...\n", room1->name);
			if (ft_strequ(room1->name, pipe2->left->name) || ft_strequ(room1->name, pipe2->right->name))
			{
/*				path_temp = copy_maillon(path);
				while (path_temp->room)
				{
					room2 = (t_room*)(path_temp->room->content);
					if (ft_strequ(room2->name, room1->name))
						break;
					path_temp->room = path_temp->room->next;
				}*/
				//On ajoute la room2 au path
				ft_list_push_back(&(path->room), ft_strequ(room1->name, pipe2->left->name) ? pipe2->right : pipe2->left, sizeof(t_room));
				printf("on ajoute a la suite la room %s\n", ft_strequ(room1->name, pipe2->left->name) ? pipe2->right->name : pipe2->left->name);
				path->len++;
//				break;
			}
		}
		else
		{
			//Il faudrait trouver le 1er et le mettre avec son 1er pipe
			printf("on ajoute %s \n", pipe2->left->name);
			ft_list_push_back(&(path->room), pipe2->left, sizeof(t_room));
			printf("on ajoute %s \n", pipe2->right->name);
			ft_list_push_back(&(path->room), pipe2->right, sizeof(t_room));
			path->len += 2;
		}
		PIPE = PIPE->next;
	}
	while (path->room)
	{
		room1 = (t_room*)path->room->content;
		printf("chemin: %s\n", room1->name);
		path->room = path->room->next;
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
    t_path    *path;
    t_pipe    *pipe;
    
    path = NULL;
    line = NULL;
    head_path = NULL;
    room = NULL;
    if (!(env = (t_env*)malloc(sizeof(t_env))))
        return (0);
    env->head_room = NULL;
    env->head_pipe = NULL;
    pipe = NULL;
    get_next_line(0, &line);
    env->nb_ant = ft_atoi(line);
    while ((ret = get_next_line(0, &line)) > 0)
    {
        //ROOM
        if (len_double_tab(ft_strsplit(line, ' ')) == 3 && !strchr(line, '#') && !strchr(line, 'L'))
        {
            if (!(room = (t_room*)malloc(sizeof(t_room))))
                return (0);
            temp = ft_strsplit(line, ' ');
            room->name = temp[0];
            room->x = ft_atoi(temp[1]);
            room->y = ft_atoi(temp[2]);
            ft_list_push_back(&(env->head_room), room, sizeof(t_room));
            room = NULL;
            //ft_strdel(&temp);
        }
        else if (line[0] == '#')
        {
            if (handle_command(env, line) == 0)
            {
                ft_putstr_fd("Error\n", 2);
                ft_strdel(&line);
                return (0);
            }
        }
        else if (len_double_tab(ft_strsplit(line, '-')) == 2)
        {
            pipe = (t_pipe*)malloc(sizeof(t_pipe));
            temp = ft_strsplit(line, '-');
           // printf("%s     %s\n", temp[0], temp[1]);
            head_temp = env->head_room;
            pipe->left = NULL;
            while (head_temp)
            {
                //room = contenu de head temp == head_room
                room = (t_room*)(head_temp->content);
                if (!ft_strcmp(room->name, temp[0]))
                {
                    pipe->left = room;
             //       printf("room de depart = %s\n", pipe->left->name);
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
             //       printf("room de depart = %s\n", pipe->right->name);
                }
                head_temp = head_temp->next;
            }
            if (pipe->left == NULL || pipe->right == NULL)
            {
                ft_putstr_fd("Error\n", 2);
                ft_strdel(&line);
                return (0);
            }
            ft_list_push_back(&(env->head_pipe), pipe, sizeof(t_pipe));
        }
        else
        {
            ft_putstr_fd("Error\n", 2);
            ft_strdel(&line);
            return (0);
        }
        ft_strdel(&line);
        
    }
    /*    while (env->head_room)
     {
     room = (t_room*)(env->head_room->content);
     printf("nom de room = %s\n", room->name);
     env->head_room = env->head_room->next;
     }
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
     */    cree_path(env);
    /*printf("nom de start = %s x = %d y = %d\n", env->start->name, env->start->x, env->start->y);
     printf("nom de end = %s x = %d y = %d\n", env->end->name, env->end->x, env->end->y);*/
    return (0);
}
