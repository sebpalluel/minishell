/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/27 15:21:44 by psebasti          #+#    #+#             */
/*   Updated: 2017/12/10 17:36:07 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void		ft_cdhome(t_sh *sh)
{
	if (chdir(ENVSTRUCT(ft_searchenv(sh->env, "HOME"))->value) == -1)
		ft_error(SHELL, "cd :", " HOME not defined", 0);
	else
	{
		ft_editenv(sh->env, "OLDPWD", \
				ENVSTRUCT(ft_searchenv(sh->env, "PWD"))->value);
		ft_editenv(sh->env, "PWD", \
				ENVSTRUCT(ft_searchenv(sh->env, "HOME"))->value);
	}

}

int		ft_islink(const char *path)
{
	struct stat	stats;
	int			tmp;

	tmp = 0;
	if (ft_strcmp(path, "../") == OK || ft_strcmp(path, "./") == OK)
		return (ERROR);
	if (lstat(path, &stats) == -1)
		return (ERROR);
	if (!(tmp = S_ISLNK(stats.st_mode)))
		return (ERROR);
	else
		return (OK);
}

static void	ft_cderror(char *path, int mode) // a changer en plus clean
{
	if (mode == 0)
	{
		if (access(path, F_OK) == 0)
			ft_putstr("\033[01mcd:\033[31m Chemin interdit : \033[00m");
		else
			ft_putstr("\033[01mcd:\033[31m Chemin inexistant : \033[00m");
		ft_putstr(path);
	}
	else
	{
		ft_putstr("\033[31mCommande invalide\033[00m: cd [-L|-P] [\033[01mdo");
		ft_putstr("ssier\033[00m | \033[01m..\033[00m | \033[01m/\033[00m ");
		ft_putstr("| \033[01m-\033[00m | \033[01m~\033[00m |  ]");
	}
}

static char	*ft_cdlink(t_sh *sh, char *path, char *tmp3)
{
	char 	*tmp;

	if (!(tmp = ft_strsub(path, 0, ft_strlen(path) - ft_strlen(tmp3))))
		tmp = ft_strdup("./");
	chdir(tmp);
	free(tmp);
	if (getcwd(sh->buff, BUFF_CWD) == NULL)
		ft_cderror("Récuperation de PWD", 0);
	if (ft_strcmp(sh->buff, "/") == 0)
	{
		free(sh->buff);
		sh->buff = ft_strnew(0);
	}
	chdir(tmp3);
	if (tmp3[0] != '/')
		tmp = ft_strjoinfree(tmp, "/", 1);
	tmp = ft_strjoinfree(tmp, tmp3, 1);
	return (tmp);
}

void		ft_cdmove(t_sh *sh, char *path)
{
	char	*tmp;
	char	*tmp3;

	tmp = NULL;
	if (ft_islink(path) != OK)
	{
		if (chdir(path) == -1)
			ft_cderror(path, 0);
		tmp = ft_getpath(sh);
	}
	else
	{
		tmp3 = ft_strrchr(path, '/');
		if (tmp3 == NULL)
			tmp3 = path;
		tmp = ft_cdlink(sh, path, tmp3);
	}
	ft_editenv(sh->env, "$OLDPWD",\
			ENVSTRUCT(ft_searchenv(sh->env, "$PWD"))->value);
	ft_editenv(sh->env, "$PWD", tmp);
}

void		ft_cdprev(t_sh *sh)
{
	t_list	*tmp;

	tmp = ft_searchenv(sh->env, "OLDPWD");
	if (!tmp)
		ft_error(SHELL, "cd :", " OLDPWD not defined", 0);
	else if (tmp && chdir(ENVSTRUCT(tmp)->value) == -1)
		ft_error(SHELL, "cd :", " OLDPWD not set", 0);
	else
	{
		ft_putendl(ENVSTRUCT(tmp)->value);
		ft_editenv(sh->env, "SWAP", \
				ENVSTRUCT(ft_searchenv(sh->env, "PWD"))->value);
		ft_editenv(sh->env, "PWD", \
				ENVSTRUCT(ft_searchenv(sh->env, "OLDPWD"))->value);
		ft_editenv(sh->env, "OLDPWD", \
				ENVSTRUCT(ft_searchenv(sh->env, "SWAP"))->value);
		ft_delenvelem(&sh->env, "SWAP");
	}
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
	else if (ft_checkaccess("cd :", *cmds, 1) == OK)
		ft_cdmove(sh, *cmds);
	if ((tmp = ft_searchenv(sh->env, "PWD")))
	{
		free(sh->path);
		sh->path = ft_getpath(sh);
	}
}

