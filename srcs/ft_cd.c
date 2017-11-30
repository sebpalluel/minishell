/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/27 15:21:44 by psebasti          #+#    #+#             */
/*   Updated: 2017/11/30 17:01:26 by psebasti         ###   ########.fr       */
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

//int			ft_cdmove(t_sh *sh, char *path, char **cmds)
//{
//	char	*tmp;
//	char	*tmp3;
//
//	tmp = NULL;
//	//if (ft_spe_cd(&tpath[1], cmds) == 1)
//	//	return (1);
//	//if (ft_islink(path) == 0)
//	//	return (0);
//	tmp3 = ft_strrchr(path, '/');
//	if (tmp3 == NULL)
//		tmp3 = path;
//	//tmp = ft_cd_lien2(tmp, path, tmp3);
//	ft_editenv(sh->env, "$OLDPWD",\
//			ENVSTRUCT(ft_searchenv(sh->env, "$PWD"))->value);
//	ft_editenv(sh->env, "$PWD", tmp);
//	return (1);
//}

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
		ft_editenv(sh->env, "SWAP", \
				ENVSTRUCT(ft_searchenv(sh->env, "PWD"))->value);
		ft_editenv(sh->env, "PWD", \
				ENVSTRUCT(ft_searchenv(sh->env, "OLDPWD"))->value);
		ft_editenv(sh->env, "OLDPWD", \
				ENVSTRUCT(ft_searchenv(sh->env, "SWAP"))->value);
		ft_delenvelem(sh->env, "SWAP");
	}
}

void			ft_cd(void *a)
{
	t_sh		*sh;
	char		**cmds;

	sh = (t_sh *)a;
	cmds = sh->commands;
	if (!*++cmds || !ft_strcmp(*cmds, "~"))
		ft_cdhome(sh);
	else if (!ft_strcmp(*cmds, "-"))
		ft_cdprev(sh);
	//else if (!(ft_strcmp(*cmds, "-") && ft_findenv(sh->env, "$OLDPWD")))
	//	ft_cdmove(sh, *cmds, sh->commands);
	if (a)
		printf("cd\n");
}

