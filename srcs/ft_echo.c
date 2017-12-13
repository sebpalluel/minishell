/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/27 15:20:33 by psebasti          #+#    #+#             */
/*   Updated: 2017/12/13 16:17:45 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	ft_echoenv(char *str, t_list *env, t_bool newline)
{
	t_list	*tmp;

	tmp = ft_searchenv(env, str + 1);
	if (tmp)
	{
		if (newline)
			ft_putstr(ENVSTRUCT(tmp)->value);
		else
			ft_putendl(ENVSTRUCT(tmp)->value);
	}
	else
		ft_putendl("");
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
