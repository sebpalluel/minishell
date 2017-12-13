/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 14:10:14 by psebasti          #+#    #+#             */
/*   Updated: 2017/12/13 13:34:07 by psebasti         ###   ########.fr       */
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
		ft_error("unsetenv: ", "Too few arguments", NULL, ERROR);
}

void		ft_env(void *a)
{
	t_sh 	*sh;
	t_list	*tmp;

	sh = (t_sh *)a;
	tmp = sh->env;
	while (tmp->next)
	{
		ft_putendl(ENVSTRUCT(tmp)->env_str);
		tmp = tmp->next;
	}
	ft_putendl(ENVSTRUCT(tmp)->env_str);
}

void	ft_exit(void *a)
{
	t_sh *sh;

	sh = (t_sh *)a;
	//clean func
	exit(EXIT_SUCCESS);
}

void		ft_pwd(void *a)
{
	t_sh 	*sh;
	t_list	*tmp;
	char	**cmds;

	sh = (t_sh *)a;
	cmds = sh->commands;
	if (*++cmds)
		ft_error("pwd: ", "too many arguments", NULL, ERROR);
	else if ((tmp = ft_searchenv(sh->env, "PWD")))
		ft_putendl(ENVSTRUCT(tmp)->value);
}
