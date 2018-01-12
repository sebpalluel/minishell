/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 17:32:06 by psebasti          #+#    #+#             */
/*   Updated: 2018/01/12 15:02:01 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		ft_printprompt(t_sh *sh)
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
				sh->builtins[i].builtinfunc((void *)sh);
				return (OK);
			}
		}
	}
	return (ERROR);
}

int			ft_readline(t_sh *sh)
{
	char	**cmds_semi;
	int		i;

	cmds_semi = ft_strsplit(sh->line, ';');
	i = -1;
	while (cmds_semi[++i])
	{
		if (!(sh->envi = ft_getenv(sh)) ||\
				!(sh->commands = ft_strsplitequ(cmds_semi[i], " \t")) ||\
				sh->commands[0] == NULL)
			return (ft_delcmds(sh, cmds_semi, ERROR));
		sh->bindirs = ft_bindirs(sh);
		if (ft_builtinfuncs(sh) == OK)
			;
		else if (ft_elsefuncs(sh) == ERROR)
			sh->return_col = ft_error(SHELL, sh->commands[0], \
					": command not found", ERROR);
		ft_delcmds(sh, cmds_semi, OK);
	}
	ft_tabnullfree((void ***)&cmds_semi);
	return (OK);
}

int			ft_prompt(t_sh *sh)
{
	if (sh->line)
	{
		sh->return_col = OK;
		if (ft_readline(sh) != OK)
		{
			ft_memdel((void **)&sh->line);
			ft_printprompt(sh);
			return (ERROR);
		}
	}
	ft_printprompt(sh);
	return (OK);
}

int			ft_externcmd(t_sh *sh, char **argv)
{
	char	**cmds;
	char	*line;

	if ((line = ft_tabtostr(argv)))
	{
		if ((cmds = ft_strsplitequ(line, " \t")) && \
				ft_strcmp(cmds[1], "-c") == OK)
		{
			argv += 2;
			if ((sh->line = (*argv != NULL ? ft_tabtostr(argv) : NULL)))
				ft_readline(sh);
			ft_tabfree((void **)cmds);
			free(line);
			if (*argv)
				return (ft_del(sh, EXIT_SUCCESS));
			return (ft_error(SHELL, "-c:", " option requires an argument",\
						ft_del(sh, EXIT_FAILURE)));
		}
		free(line);
	}
	return (ft_error(SHELL, argv[1], ": invalid option", \
				ft_del(sh, EXIT_FAILURE)));
}
