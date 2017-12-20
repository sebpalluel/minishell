/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 11:12:09 by psebasti          #+#    #+#             */
/*   Updated: 2017/12/20 16:49:17 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		ft_delenvnode(void *content, size_t size)
{
	(void)size;
	if (((t_env*)(content))->name)
		free(((t_env*)(content))->name);
	if (((t_env*)(content))->value)
		free(((t_env*)(content))->value);
	free(content);
}

int			ft_delcmpr(void *content, void *name)
{
	return (ft_strcmp(((t_env*)(content))->name, name));
}

int			ft_delmatch(void *content, void *name)
{
	int		res;

	res = match(((t_env*)(content))->name, name);
	res = !res;
	return (res);
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

void		ft_handlectrlc(int sig)
{
	if (sig == SIGINT)
	{
		kill(g_father, sig);
		ft_putchar('\n');
	}
}
