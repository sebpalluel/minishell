/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/27 15:21:44 by psebasti          #+#    #+#             */
/*   Updated: 2017/11/27 18:12:01 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void		ft_cdhome(t_sh *sh)
{
	if (chdir(ft_findenv(sh->env, "HOME")) == -1)
			ft_error("cd :", sh->commands[0], ": $HOME not defined", 0);
	else
	{
		ft_editenv(sh->env, "$OLDPWD", \
				ENVSTRUCT(ft_searchenv(sh->env, "$PWD"))->value);
		ft_editenv(sh->env, "$PWD", \
				ENVSTRUCT(ft_searchenv(sh->env, "$HOME"))->value);
	}

}

void			ft_cd(void *a)
{
	t_sh		*sh;
	char		**cmds;

	sh = (t_sh *)a;
	cmds = sh->commands;
	if (!*++cmds || *cmds[0] == '~')
		ft_cdhome(sh);
	else if (ft_strcmp(*cmds, "-P"))
	if (a)
		printf("cd\n");
}

