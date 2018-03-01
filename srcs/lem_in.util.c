/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecalie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 15:53:28 by clecalie          #+#    #+#             */
/*   Updated: 2018/03/01 16:12:22 by clecalie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	free_double_tab(char **tab)
{
	int		i;

	i = 0;
	while (tab[i])
	{
		ft_strdel(&tab[i]);
		i++;
	}
	free(tab);
	tab = NULL;
}

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
