/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/27 15:21:44 by psebasti          #+#    #+#             */
/*   Updated: 2017/12/12 17:06:44 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void		ft_cdhome(t_sh *sh)
{
	t_list		*tmp;

	if (!(tmp = ft_searchenv(sh->env, "HOME")))
		ft_error(SHELL, "cd :", " HOME doesn't exist", 0);
	else if (ft_checkaccess("cd :", ENVSTRUCT(tmp)->value, 1) != OK)
		ft_error(SHELL, "cd :", " HOME not defined", 0);
	else
	{
		ft_editenv(sh->env, "OLDPWD", \
				ENVSTRUCT(ft_searchenv(sh->env, "PWD"))->value);
		ft_editenv(sh->env, "PWD", \
				ENVSTRUCT(ft_searchenv(sh->env, "HOME"))->value);
		chdir(ENVSTRUCT(tmp)->value);
	}
}

int		ft_islink(const char *path)
{
	struct stat	path_stats;
	int			tmp;

	tmp = 0;
	lstat(path, &path_stats);
	printf("S_ISLNK %d\n", S_ISLNK(path_stats.st_mode));
	if (ft_strcmp(path, "../") == OK || ft_strcmp(path, "./") == OK)
		return (ERROR);
	if (lstat(path, &path_stats) == -1)
		return (ERROR);
	if (!(tmp = S_ISLNK(path_stats.st_mode)))
		return (ERROR);
	else
		return (OK);
}

static char	*ft_cdlink(t_sh *sh, char *path, char *tmp3) // a changer egalement
{
	char 	*tmp;

	if (!(tmp = ft_strsub(path, 0, ft_strlen(path) - ft_strlen(tmp3))))
		tmp = ft_strdup("./");
	chdir(tmp);
	free(tmp);
	tmp = getcwd(sh->buff, BUFF_CWD);
	if (ft_strcmp(tmp, "/") == 0)
	{
		free(tmp);
		tmp = ft_strnew(0);
	}
	chdir(tmp3);
	if (tmp3[0] != '/')
		tmp = ft_strjoinfree(tmp, "/", 1);
	tmp = ft_strjoinfree(tmp, tmp3, 1);
	return (tmp);
}

void		ft_cdprev(t_sh *sh)
{
	t_list	*tmp;

	if (!(tmp = ft_searchenv(sh->env, "OLDPWD")))
		ft_error(SHELL, "cd :", " OLDPWD not defined", 0);
	else if (tmp && !ENVSTRUCT(tmp)->value)
		ft_error(SHELL, "cd :", " OLDPWD not set", 0);
	else if (ft_checkaccess("cd : ", ENVSTRUCT(tmp)->value, 0) == OK)
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
int			ft_cdmove(t_sh *sh, char *path)
{
	char	*tmp;
	char	*tmp3;

	tmp = NULL;
	if (ft_checkaccess("cd : ", path, 0) == OK)
	{
		if (ft_islink(path) != OK)
			chdir(path);
		else
		{
			tmp3 = ft_strrchr(path, '/');
			if (tmp3 == NULL)
				tmp3 = path;
			printf("tmp3 link : %s\n", tmp3);
			tmp = ft_cdlink(sh, path, tmp3);
		}
		return (OK);
	}
	return (ERROR);
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
			ft_editenv(sh->env, "PWD", getcwd(sh->buff, BUFF_CWD));
	}
	if (sh->path)
		free(sh->path);
	sh->path = ft_getpath(sh);
}
