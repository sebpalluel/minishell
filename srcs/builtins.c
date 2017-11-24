/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 14:10:14 by psebasti          #+#    #+#             */
/*   Updated: 2017/11/24 19:22:14 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	echo_env(char *str, t_list *env, char nflag)
{
	char	*tmp;

	tmp = ft_findenv(env, str + 1);
	if (nflag)
		ft_putstr(tmp);
	else
		ft_putendl(tmp);
}

void	ft_echo(void *a)
{
	t_sh	*sh;
	char	**cmds;
	int		nflag;

	sh = (t_sh *)a;
	cmds = sh->commands;

	if (*++cmds && !ft_strcmp(*cmds, "-n") && (++cmds || !cmds))
		nflag = 1;
	else
		nflag = 0;
	if (!*cmds && !nflag)
		ft_putchar('\n');
	while (*cmds)
	{
		if (*cmds[0] == '$')
			echo_env(*cmds, sh->env, nflag);
		else
		{
			if (!(*(cmds + 1)) && !nflag)
				ft_putendl(*cmds);
			else
			{
				ft_putstr(*cmds);
				if (*(cmds + 1))
					ft_putchar(' ');
			}
		}
		++cmds;
	}
}

void	ft_cd(void *a)
{
	if (a)
		printf("cd\n");
}

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
