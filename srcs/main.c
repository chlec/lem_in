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

void	cree_path(t_env *env)
{
	t_path	*path;
	t_list	*PIPE;
	t_list	*PIPE_fix;
	t_room	*room1;
	t_pipe	*pipe2;
	t_path	*path_temp;

	path = (t_path*)malloc(sizeof(t_path));
	path->room = NULL;
	path->len = 0;
	PIPE = env->head_pipe;
	PIPE_fix = PIPE;
	room1 = NULL;
	/*comme ca il s'arret bien quant il faut.
	Par contre je pence qu'il faut suprimer
	les pipe qu'on a deja utiliser sinon il y a des cas
	ou il reprend le meme pipe dans un sens puis dans l'autre
	donc BOUCLE SANS FIN!!!!!!!!*/
	while ((room1 == NULL || ft_strcmp(room1->name, "1")) && PIPE )
	{
        /*
        A FAIRE: Dès qu'on a un pipe, on regarde si il a deja ete traiter.
        Si non, onc ckeck tout les path jusqu'a trouver une room qui est dans le pipe, on le duplique et on lui met un nouveau chemin
        Du coup des que le chemin arrive a END, on fait un path->next.
        Pour le map.txt on veut:
            0 -> 4 -> 3 -> 1
            0 -> 4 -> 2 -> 1
            0 -> 6 -> 7 -> 2 -> 1
            0 -> 6 -> 7 -> 3 -> 1
            0 -> 6 -> 5 -> 2 -> 1

        Je crois que c'est bon après
        */
		pipe2 = (t_pipe*)(PIPE->content);
        printf("ON EST DANS LA BOUCLE. ROOM1: %s - ROOM2: %s\n", pipe2->left->name, pipe2->right->name);
		path_temp = copy_maillon(&(path->room));
		room1 = NULL;
		while (path_temp->room && !room1)
		{	
			if (path_temp->room->next == NULL)
				room1 = (t_room*)path_temp->room->content;
			path_temp->room = path_temp->room->next;
		}
		if (room1 && !pipe2->used)
		{
			//Cette condition verifie si le dernier element du path est dans le pipe
			if (ft_strequ(room1->name, pipe2->left->name) || ft_strequ(room1->name, pipe2->right->name))
			{
				//On check que le pipe n'a pas deja ete traite
                if (!linked(&(path->room), pipe2->left, pipe2->right))
                {
    				ft_list_push_back(&(path->room), ft_strequ(room1->name, pipe2->left->name) ? pipe2->right : pipe2->left, sizeof(t_room));
    				printf("on ajoute a la suite la room %s\n", ft_strequ(room1->name, pipe2->left->name) ? pipe2->right->name : pipe2->left->name);
    				path->len++;
					pipe2->used = 1;
    				PIPE = PIPE_fix;
                }
			}

            if (ft_strequ(room1->name, "1"))
            {
				printf("path complet ajouter!\n");
                ft_list_push_back(&(env->head_path), path, sizeof(t_path));
                /*
                    Ici il faudrait repartir au debut, puis on recrée un chemin et on check a chaque coup qu'il soit bien different
                    du précédent, par contre je sais pas quelle condition d'arret faire
                */
                if (list_len(&(env->head_path)) < 2) //Mettre 2 
                {
                    room1 = NULL;
                    free(path);
                    path = NULL;
                    path = (t_path*)malloc(sizeof(t_path));
                    path->room = NULL;
                    path->len = 0;
                    PIPE = PIPE_fix;
                }
            }
		}
		else if (!room1)
		{
			//Il faudrait trouver le 1er et le mettre avec son 1er pipe
			printf("on ajoute %s \n", pipe2->left->name);
			ft_list_push_back(&(path->room), pipe2->left, sizeof(t_room));
			printf("on ajoute %s \n", pipe2->right->name);
			ft_list_push_back(&(path->room), pipe2->right, sizeof(t_room));
			pipe2->used = 1;
			path->len += 2;
		}
		else if (path->len == 0)
		{
			//ici cest que le pipe est deja utiliser
			pipe2->used = 0;
			printf("on reprend un ancien path, car pipe deja use: %s-%s\n", pipe2->left->name, pipe2->right->name);
			path = get_path_to_pipe(&(env->head_path), pipe2);
		}
		if (path->len > 0)
		PIPE = PIPE->next;
	}
	while (env->head_path)
	{
        path = (t_path*)(env->head_path->content);
        while (path->room)
        {
    		room1 = (t_room*)(path->room->content);
    		printf("chemin: %s\n", room1->name);
            path->room = path->room->next;
        }
        printf("------\n");
		env->head_path = env->head_path->next;
	}
}

void	display_path(t_list **l)
{
	t_list	*list;
	t_room	*room;

	list = *l;
	printf("Le path contient les salles: \n");
	while (list)
	{
		room = (t_room*)list->content;
		ft_putstr(room->name);
		list = list->next;
	}
	ft_putchar('\n');
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

void	create_path(t_env *env, t_path *p)
{
	t_path	*path;
	t_list	*pipe_list;
	t_list	*PIPE_fix;
	t_room	*room1;
	t_pipe	*pipe;
	t_path	*path_temp;

	/*
	 * Faire de la recursive!
	 * En gros si on a 0-4 on fait tout les chemin possible a partir de 0-4 et ainsi de suite
	 * */
	pipe_list = env->head_pipe;
	PIPE_fix = pipe_list;
	room1 = NULL;
	while (pipe_list)
	{
		pipe = (t_pipe*)pipe_list->content;
		if (!p)
		{
			path = (t_path*)malloc(sizeof(t_path));
			path->room = NULL;
			path->len = 0;
			printf("debut: on ajoute %s \n", pipe->left->name);
			ft_list_push_back(&(path->room), pipe->left, sizeof(t_room));
			printf("debut: on ajoute %s \n", pipe->right->name);
			ft_list_push_back(&(path->room), pipe->right, sizeof(t_room));
			path->len += 2;
			return create_path(env, path);
		}
		else
		{
			path_temp = p;
			//the loop behind break the linked list
			room1 = get_last_room(&(p->room));
			display_path(&(p->room));
			if ((ft_strequ(room1->name, pipe->right->name) || ft_strequ(room1->name, pipe->left->name)) && !linked(&(p->room), pipe->left, pipe->right))
			{
				printf("on ajoute %s\n", ft_strequ(room1->name, pipe->left->name) ? pipe->right->name : pipe->left->name);
				usleep(500000);
				ft_list_push_back(&(p->room), ft_strequ(room1->name, pipe->left->name) ? pipe->right : pipe->left, sizeof(t_room));
				p->len++;
				create_path(env, p);
			}
			if (ft_strequ(room1->name, "1"))
				return ;
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
     */    create_path(env, NULL);
	while (env->head_path)
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
	}

    /*printf("nom de start = %s x = %d y = %d\n", env->start->name, env->start->x, env->start->y);
     printf("nom de end = %s x = %d y = %d\n", env->end->name, env->end->x, env->end->y);*/
    return (0);
}
