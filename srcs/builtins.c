/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 14:10:14 by psebasti          #+#    #+#             */
/*   Updated: 2017/12/12 14:16:07 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_setenv(void *a)
{
	if (a)
		printf("setenv\n");
}

void	ft_unsetenv(void *a)
{
	if (a)
		printf("unsetenv\n");
}

void	ft_env(void *a)
{
	if (a)
		printf("env\n");
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
