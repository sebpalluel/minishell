/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 14:10:14 by psebasti          #+#    #+#             */
/*   Updated: 2017/12/20 17:03:22 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		ft_setenv(void *a)
{
	t_sh	*sh;
	char	**cmds;
	char	*name;
	char	*value;

	sh = (t_sh *)a;
	cmds = sh->commands;
	if (*++cmds)
	{
		name = *cmds++;
		value = *cmds;
		if (ft_checkalnum(name) == OK)
			ft_editenv(sh->env, name, value);
		else
			ft_error("setenv: ", \
				"Variable name must contain alphanumeric characters.", NULL, 1);
	}
	else
		ft_env((void *)sh);
}

void		ft_unsetenv(void *a)
{
	t_sh	*sh;
	char	**cmds;

	sh = (t_sh *)a;
	cmds = sh->commands;
	if (*++cmds)
	{
		if (!ft_strchr(*cmds, '*'))
			ft_delenvelem(&sh->env, *cmds);
		else
			ft_lstdelif(&sh->env, *cmds, ft_delmatch, ft_delenvnode);
	}
	else
		sh->return_col = \
				ft_error("unsetenv: ", "Too few arguments", NULL, ERROR);
}

void		ft_env(void *a)
{
	t_sh	*sh;
	t_list	*tmp;
	char	**cmds;

	sh = (t_sh *)a;
	tmp = sh->env;
	cmds = sh->commands;
	++cmds;
	if (*cmds)
		sh->return_col = ft_checkaccess("env : ", *cmds, 0, 1) != OK \
						? ERROR : OK;
	while (sh->return_col == OK && tmp->next)
	{
		ft_putstr(ENVSTRUCT(tmp)->name);
		ft_putchar('=');
		ft_putendl(ENVSTRUCT(tmp)->value);
		tmp = tmp->next;
		if (!tmp->next)
		{
			ft_putstr(ENVSTRUCT(tmp)->name);
			ft_putchar('=');
			ft_putendl(ENVSTRUCT(tmp)->value);
		}
	}
}

void		ft_exit(void *a)
{
	t_sh	*sh;

	sh = (t_sh *)a;
	ft_lstdel(&sh->env, ft_delenvnode);
	if (sh->bindirs)
		ft_tabfree((void **)sh->bindirs);
	if (sh->envi)
		ft_tabfree((void **)sh->envi);
	if (sh->commands)
		ft_tabfree((void **)sh->commands);
	if (sh->validfuncs)
		ft_tabfree((void **)sh->validfuncs);
	if (sh->line)
		free(sh->line);
	if (sh->builtins)
		free(sh->builtins);
	if (sh->path)
		free(sh->path);
	free(sh);
	ft_error("minishell: ", NULL, "exited normally", 0);
	exit(EXIT_SUCCESS);
}

void		ft_pwd(void *a)
{
	t_sh	*sh;
	char	**cmds;

	sh = (t_sh *)a;
	cmds = sh->commands;
	if (*++cmds)
		sh->return_col = ft_error("pwd: ", "too many arguments", NULL, ERROR);
	else
		ft_putendl(getcwd(sh->buff, PATH_MAX));
}
