/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecalie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 12:26:58 by clecalie          #+#    #+#             */
/*   Updated: 2018/02/15 14:18:00 by clecalie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		main(void)
{
	int		ret;
	char	*line;
	t_env	*env;
	int		i;

	line = NULL;
	i = 0;
	if (!(env = (t_env*)malloc(sizeof(env))))
		return (0);
	while ((ret = get_next_line(0, &line)))
	{
		if (i == 0)
			env->nb_ant = ft_atoi(line);
		i++;
		ft_strdel(&line);	
	}
	return (0);
}
