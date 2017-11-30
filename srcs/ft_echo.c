/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/27 15:20:33 by psebasti          #+#    #+#             */
/*   Updated: 2017/11/30 11:19:46 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	ft_echoenv(char *str, t_list *env, t_bool newline)
{
	char	*tmp;

	tmp = ENVSTRUCT(ft_searchenv(env, str + 1))->value;
	if (newline)
		ft_putstr(tmp);
	else
		ft_putendl(tmp);
}

static void	ft_echoprintcmds(char **cmds, t_sh *sh, t_bool newline)
{
	if (*cmds[0] == '$')
		ft_echoenv(*cmds, sh->env, newline);
	else
	{
		if (!(*(cmds + 1)) && !newline)
			ft_putendl(*cmds);
		else
		{
			ft_putstr(*cmds);
			if (*(cmds + 1))
				ft_putchar(' ');
		}
	}
}

void		ft_echo(void *a)
{
	t_sh	*sh;
	char	**cmds;
	t_bool	newline;

	sh = (t_sh *)a;
	cmds = sh->commands;

	if (*++cmds && !ft_strcmp(*cmds, "-n") && (++cmds || !cmds))
		newline = 1;
	else
		newline = 0;
	if (!*cmds && !newline)
		ft_putchar('\n');
	while (*cmds)
	{
		ft_echoprintcmds(cmds, sh, newline);	
		++cmds;
	}
}
