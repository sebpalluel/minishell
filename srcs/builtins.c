/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 14:10:14 by psebasti          #+#    #+#             */
/*   Updated: 2017/12/14 12:57:03 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		ft_setenv(void *a)
{
	t_sh 	*sh;
	char	**cmds;
	char	*name;
	char	*value;

	sh = (t_sh *)a;
	cmds = sh->commands;
	if (*++cmds)
	{
		name = *cmds++;
		value = *cmds;
		ft_editenv(sh->env, name, value);
	}
	else
		ft_env((void *)sh);
}

void		ft_unsetenv(void *a)
{
	t_sh 	*sh;
	char	**cmds;

	sh = (t_sh *)a;
	cmds = sh->commands;
	if (*++cmds)
		ft_delenvelem(&sh->env, *cmds);
	else
		sh->return_col = \
				ft_error("unsetenv: ", "Too few arguments", NULL, ERROR);
}

void		ft_env(void *a)
{
	t_sh 	*sh;
	t_list	*tmp;
	char	**cmds;
	t_bool	flag;

	sh = (t_sh *)a;
	tmp = sh->env;
	cmds = sh->commands;
	flag = OK;
	++cmds;
	if (*cmds)
		if (ft_checkaccess("env : ", *cmds, 0, 1) != OK)
			flag = ERROR;
	while (flag == OK && tmp->next)
	{
		ft_putendl(ENVSTRUCT(tmp)->env_str);
		tmp = tmp->next;
		if (!tmp->next)
			ft_putendl(ENVSTRUCT(tmp)->env_str);
	}
	sh->return_col = flag;
}

void	ft_exit(void *a)
{
	t_sh *sh;

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
	exit(EXIT_SUCCESS);
}

void		ft_pwd(void *a)
{
	t_sh 	*sh;
	char	**cmds;

	sh = (t_sh *)a;
	cmds = sh->commands;
	if (*++cmds)
		sh->return_col = ft_error("pwd: ", "too many arguments", NULL, ERROR);
	else
		ft_putendl(getcwd(sh->buff, PATH_MAX));
}
