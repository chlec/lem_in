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
			env->start->ant = env->nb_ant;
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
			env->end->ant = 0;
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

t_path	*copy_maillon_n(t_list **p, int n)
{
	t_path	*ret;
	t_list	*list;

	list = *p;
	ret = malloc(sizeof(t_path));
	ret->room = NULL;
	ret->len = 0;
	while (list && ret->len < n)
	{
		ft_list_push_back(&(ret->room), list->content, sizeof(t_room));
		ret->len++;
		list = list->next;
	}
	return (ret);	
}

int     list_len(t_list **l)
{
    t_list  *list;
    int     len;

    len = 0;
    list = *l;
    while (list)
    {
        len++;
        list = list->next;
    }
    return (len);
}

int     linked(t_list **p, t_room *left, t_room *right)
{
    t_list  *path;
    t_room  *room;
    t_room  *next;

    path = *p;
    /*
        Ici on check tout le path et on regarde si les 2 arguments passé ne sont pas deja collé.
        On regarde le path jusqu'a trouver l'une des room left ou right. Apres on la compare avec la next,
        Si elle sont bien coller ou renvoi 1 sinon 0
    */
    while (path)
    {
        room = (t_room*)(path->content);
		if (path->next && (ft_strequ(room->name, left->name) || ft_strequ(room->name, right->name)))
        {
            next = (t_room*)(path->next->content);
            if (ft_strequ(next->name, ft_strequ(room->name, left->name) ? right->name : left->name))
                return (1);
        }
        path = path->next;
    }
    return (0);
}

t_path	*get_path_to_pipe(t_list **p, t_pipe *pipe)
{
	t_path	*path;
	t_room	*room;
	t_list	*list;
	int		len;

	list = *p;
	while (list)
	{
		path = (t_path*)list->content;
		len = 0;
		while (path->room)
		{
			room = (t_room*)path->room->content;
			if (ft_strequ(room->name, pipe->left->name) || ft_strequ(room->name, pipe->right->name))
				return (copy_maillon_n(&(path->room), len));
			len++;
			path->room = path->room->next;
		}
	}
	return (0);
}

t_room	*get_last_room(t_list **l)
{
	t_list	*list;
	t_room	*room;

	list = *l;
	room = NULL;
	while (list && !room)
	{	
		if (list->next == NULL)
			room = (t_room*)list->content;
		list = list->next;
	}
	return (room);
}

int		room_is_present(t_list	**l, t_room *room)
{
	t_list	*list;
	t_room	*room2;

	list = *l;
	list = list->next;
	while (list->next)
	{
		room2 = (t_room*)list->content;
		if (ft_strequ(room->name, room2->name))
			return (1);	
		list = list->next;
	}
	return (0);
}

int		already_found(t_list **l, t_list **p)
{
	t_list	*all_path;
	t_path	*path;
	t_list	*new_path;
	t_room	*room1;
//	t_room	*room2;

	all_path = *l;

	while (all_path)
	{
		path = (t_path*)all_path->content;
		new_path = *p;
		while (new_path)
		{
			room1 = (t_room*)new_path->content;
//			room2 = (t_room*)new_path->next->content;
			if (room_is_present((&path->room), room1))
				return (1);
			new_path = new_path->next;
		}
		all_path = all_path->next;
	}
	return (0);
}

void	create_path(t_env *env, t_path *p)
{
	t_path	*path;
	t_list	*pipe_list;
	t_list	*PIPE_fix;
	t_room	*room1;
	t_pipe	*pipe;
	t_list	*all_path;
	t_path	*current_path;

	/*
	 * Faire de la recursive!
	 * En gros si on a 0-4 on fait tout les chemin possible a partir de 0-4 et ainsi de suite
	 * */
	pipe_list = env->head_pipe;
	PIPE_fix = pipe_list;
	room1 = NULL;
	all_path = NULL;
	current_path = NULL;
	while (pipe_list)
	{
		pipe = (t_pipe*)pipe_list->content;
		if (!p && !pipe->used && (ft_strequ(pipe->left->name, env->end->name) || ft_strequ(pipe->right->name, env->end->name)))
		{
			path = (t_path*)malloc(sizeof(t_path));
			path->room = NULL;
			path->len = 0;
			//On met toujours le ##end en 1er sur le path
			printf("Debut de path, on met %s et %s\n", pipe->left->name, pipe->right->name);
			ft_list_push_back(&(path->room), ft_strequ(pipe->left->name, env->end->name) ? pipe->left : pipe->right, sizeof(t_room));
			ft_list_push_back(&(path->room), ft_strequ(pipe->left->name, env->end->name) ? pipe->right : pipe->left, sizeof(t_room));
			path->len += 2;
			pipe->used = 1;
			if (ft_strequ(get_last_room(&(path->room))->name, env->start->name) && !already_found(&(env->head_path), &(path->room)))
			{
				printf("Ajout du path au head\n");
                ft_list_push_back(&(env->head_path), path, sizeof(t_path));
				return create_path(env, NULL);
			}
			return create_path(env, path);
		}
		else if (p && !pipe->used)
		{
			path = copy_maillon(&(p->room));
			//the loop behind break the linked list
			room1 = get_last_room(&(p->room));
			if ((ft_strequ(room1->name, pipe->right->name) || ft_strequ(room1->name, pipe->left->name)))
			{
				printf("on ajoute %s\n", ft_strequ(room1->name, pipe->left->name) ? pipe->right->name : pipe->left->name);
			//	usleep(500000);
				if (ft_strequ(room1->name, env->end->name) || ft_strequ(room1->name, env->start->name))
					return create_path(env, NULL);
				ft_list_push_back(&(path->room), ft_strequ(room1->name, pipe->left->name) ? pipe->right : pipe->left, sizeof(t_room));
				p->len++;
				//Supprimer la ligne du dessous?
				pipe->used = 1;
				create_path(env, path);
			}
			if (ft_strequ(get_last_room(&(path->room))->name, env->start->name) && !already_found(&(env->head_path), &(path->room)))
			{
				printf("Ajout du path au head\n");
                ft_list_push_back(&(env->head_path), path, sizeof(t_path));
				return create_path(env, NULL);
			}
		}
		pipe_list = pipe_list->next;
	}
}

int		main(void)
{
    int        ret;
    char    *line;
    t_env    *env;
    t_list    *head_temp;
    t_room    *room;
    char    **temp;
    t_path    *path;
    t_pipe    *pipe;
    
    path = NULL;
    line = NULL;
    room = NULL;
    if (!(env = (t_env*)malloc(sizeof(t_env))))
        return (0);
    env->head_room = NULL;
    env->head_pipe = NULL;
    env->head_path = NULL;
	env->head_ant = NULL;
    pipe = NULL;
    get_next_line(0, &line);
    env->nb_ant = ft_atoi(line);
    while ((ret = get_next_line(0, &line)) > 0)
    {
        //ROOM
        if (len_double_tab(ft_strsplit(line, ' ')) == 3 && line[0] != '#' && line[0] != 'L')
        {
            if (!(room = (t_room*)malloc(sizeof(t_room))))
                return (0);
            temp = ft_strsplit(line, ' ');
            room->name = temp[0];
            room->x = ft_atoi(temp[1]);
            room->y = ft_atoi(temp[2]);
			room->ant = 0;
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
			pipe->used = 0;
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
    create_path(env, NULL);
	move_ant(env);
   /*while (env->head_path)
    {
        path = (t_path*)(env->head_path->content);
        while (path->room)
        {
            room = (t_room*)(path->room->content);
            printf("chemin: %s\n", room->name);
            path->room = path->room->next;
        }
        printf("------\n");
        env->head_path = env->head_path->next;
    }*/
    return (0);
}
