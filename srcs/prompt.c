/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 17:32:06 by psebasti          #+#    #+#             */
/*   Updated: 2017/12/18 18:44:26 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_printprompt(t_sh *sh)
{
	ft_putstr(ANSI_RESET);
	ft_putstr(ANSI_BOLD);
	ft_putstr(ANSI_RED);
	ft_putstr("minishell:");
	ft_putstr(ANSI_RESET);
	ft_putstr(ANSI_GREEN);
	ft_putstr(sh->path);
	if (sh->return_col != OK)
		ft_putstr(ANSI_RED);
	else
		ft_putstr(ANSI_GREEN);
	ft_putstr(ANSI_BLINK);
	ft_putstr(" $> ");
	ft_putstr(ANSI_RESET);
	ft_putstr(ANSI_BLINK);
}

static int	ft_builtinfuncs(t_sh *sh)
{
	int		i;

	i = -1;
	if (sh->commands[0])
	{
		while (++i < NUMBUILTIN - 1)
		{
			if (ft_strcmp(sh->commands[0], sh->validfuncs[i]) == 0)
			{
				sh->builtins[i]((void *)sh);
				return (OK);
			}
		}
	}
	return (ERROR);
}

static int		ft_readline(t_sh *sh)
{
	char		**cmds_semi;
	int			i;

	cmds_semi = ft_strsplit(sh->line, ';');
	i = -1;
	while (cmds_semi[++i])
	{
		if (!(sh->envi = ft_getenv(sh)) ||\
				!(sh->commands = ft_strsplitequ(cmds_semi[i], " \t")))
			return (ERROR);
		sh->bindirs = ft_bindirs(sh);
		if (ft_builtinfuncs(sh) == OK)
			;
		else if (ft_elsefuncs(sh) == ERROR)
			sh->return_col = ft_error(SHELL, sh->commands[0], \
					": command not found", ERROR);
		if (sh->commands)
			ft_tabfree((void **)sh->commands);
		if (sh->envi && sh->envi[0])
			ft_tabfree((void **)sh->envi);
	}
	ft_tabfree((void **)cmds_semi);
	return(OK);
}

int			ft_prompt(t_sh *sh)
{
	if (sh->line)
	{
		sh->return_col = OK;
		if (ft_readline(sh) != OK)
		{
			ft_memdel((void **)&sh->line);
			return (ERROR);
		}
	}
	ft_printprompt(sh);
	return(OK);
}
