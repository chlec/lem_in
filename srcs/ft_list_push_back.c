#include "lem_in.h"

void	ft_list_push_back(t_list **begin_list, void *data)
{
	t_list	*list;

	list = *begin_list;
	if (list)
	{
		while (list->next)
			list = list->next;
		list->next = ft_lstnew(data, sizeof(data));
	}
	else
		*begin_list = ft_lstnew(data, sizeof(data));
}
