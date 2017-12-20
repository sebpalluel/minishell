/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/27 15:21:44 by psebasti          #+#    #+#             */
/*   Updated: 2017/12/20 15:57:14 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void		ft_cdhome(t_sh *sh)
{
	t_list		*tmp;

	if (!(tmp = ft_searchenv(sh->env, "HOME")))
		sh->return_col = ft_error(SHELL, "cd :", " HOME doesn't exist", ERROR);
	else if (ft_checkaccess("cd :", ENVSTRUCT(tmp)->value, 1, 0) != OK)
		sh->return_col = ft_error(SHELL, "cd :", " HOME not defined", ERROR);
	else
	{
		ft_editenv(sh->env, "OLDPWD", \
				ENVSTRUCT(ft_searchenv(sh->env, "PWD"))->value);
		ft_editenv(sh->env, "PWD", \
				ENVSTRUCT(ft_searchenv(sh->env, "HOME"))->value);
		chdir(ENVSTRUCT(tmp)->value);
	}
}

void			ft_cdprev(t_sh *sh)
{
	t_list		*tmp;

	if (!(tmp = ft_searchenv(sh->env, "OLDPWD")))
		sh->return_col = ft_error(SHELL, "cd :", " OLDPWD not defined", ERROR);
	else if (tmp && !ENVSTRUCT(tmp)->value)
		sh->return_col = ft_error(SHELL, "cd :", " OLDPWD not set", ERROR);
	else if ((sh->return_col = \
				ft_checkaccess("cd : ", ENVSTRUCT(tmp)->value, 0, 0)) == OK)
	{
		chdir(ENVSTRUCT(tmp)->value);
		ft_putendl(ENVSTRUCT(tmp)->value);
		ft_editenv(sh->env, "SWAP", \
				ENVSTRUCT(ft_searchenv(sh->env, "PWD"))->value);
		ft_editenv(sh->env, "PWD", ENVSTRUCT(tmp)->value);
		ft_editenv(sh->env, "OLDPWD", \
				ENVSTRUCT(ft_searchenv(sh->env, "SWAP"))->value);
		ft_delenvelem(&sh->env, "SWAP");
	}
}

static int		ft_cdmove(t_sh *sh, char *path)
{
	char		*tmp;
	int			ret;

	tmp = (path[ft_strlen(path) - 1] != '/' ? ft_strjoin(path, "/") : \
			ft_strdup(path));
	ret = chdir(tmp);
	if (tmp)
		free(tmp);
	if (ret == -1 || !sh->path)
	{
		sh->return_col = ft_checkaccess("cd : ", path, 0, ERROR);
		return (ERROR);
	}
	return (OK);
}

void			ft_cd(void *a)
{
	t_sh		*sh;
	t_list		*tmp;
	char		**cmds;

	sh = (t_sh *)a;
	cmds = sh->commands;
	if (!*++cmds || !ft_strcmp(*cmds, "~"))
		ft_cdhome(sh);
	else if (!ft_strcmp(*cmds, "-"))
		ft_cdprev(sh);
	else if (ft_cdmove(sh, *cmds) == OK)
	{
		if ((tmp = ft_searchenv(sh->env, "PWD")))
			ft_editenv(sh->env, "OLDPWD", ENVSTRUCT(tmp)->value);
		ft_editenv(sh->env, "PWD", getcwd(sh->buff, PATH_MAX));
	}
	if (sh->path)
		free(sh->path);
	sh->path = ft_getpath(sh);
}
