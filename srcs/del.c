/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 11:12:09 by psebasti          #+#    #+#             */
/*   Updated: 2017/12/13 17:49:30 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		ft_delenvnode(void *content, size_t size)
{
	(void)size;
	free(((t_env*)(content))->name);
	free(((t_env*)(content))->value);
	free(((t_env*)(content))->env_str);
	free(content);
}

int			ft_delcmpr(void *content, void *name)
{
	return(ft_strcmp(((t_env*)(content))->name, name));
}

void		ft_delenvelem(t_list **env, char *name)
{
	t_list	*tmp;
	t_list	*tmp2;

	tmp2 = NULL;
	if (!(tmp = ft_searchenv(*env, name)))
		ft_error("minishell: the variable ", name, " doesn't exist", 0);
	else
		ft_lstdelif(env, name, ft_delcmpr, ft_delenvnode);
	return ;
}
