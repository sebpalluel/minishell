/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 11:12:09 by psebasti          #+#    #+#             */
/*   Updated: 2017/12/01 16:23:59 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		ft_delenvnode(void *content, size_t size)
{
	(void)size;
	printf("delenvnode %s\n", ((t_env *)(content))->name);
	free(((t_env*)(content))->name);
	free(((t_env*)(content))->value);
	free(((t_env*)(content))->env_str);
	printf("delnode end\n");
}

int			ft_delcmpr(void *content, void *name)
{
	printf("delcmpr %s, %s\n", ((t_env *)(content))->name, name);
	return(ft_strcmp(((t_env*)(content))->name, name));
}

void		ft_delenvelem(t_list *env, char *name)
{
	t_list	*tmp;
	t_list	*tmp2;

	tmp2 = NULL;
	if (!(tmp = ft_searchenv(env, name)))
		ft_error("minishell: the variable ", name, " doesn't exist", 0);
	else
		ft_lstdelif(&env, name, ft_delcmpr, ft_delenvnode);
	printf("tmp %p\n", tmp);
	return ;
}
