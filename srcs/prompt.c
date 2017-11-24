/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 17:32:06 by psebasti          #+#    #+#             */
/*   Updated: 2017/11/24 17:42:54 by psebasti         ###   ########.fr       */
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
	ft_putstr(ANSI_RED);
	ft_putstr(ANSI_BLINK);
	ft_putstr(" $> ");
	ft_putstr(ANSI_RESET);
	ft_putstr(ANSI_BLINK);
}

static int	ft_builtinfuncs(t_sh *sh)
{
	int		i;

	i = -1;
	while (++i < NUMBUILTIN - 1)
	{
		if (ft_strcmp(sh->commands[0], sh->validfuncs[i]) == 0)
		{
			sh->builtins[i]((void *)sh);
			return (OK);
		}
	}
	return (ERROR);
}

int			ft_getbinary(char *path, t_sh *sh)
{
	int		status;
	int		es;

	if (sh->father == 0)
	{
		es = execve(path, sh->commands, sh->envi);
		exit(es);
	}
	if (sh->father > 0) 
	{
		if (waitpid(sh->father, &status, 0) > 0) 
		{
			if (WEXITSTATUS(status) == 127)
				ft_error(sh->commands[0], ": execve failed", 0);
			if (WEXITSTATUS(status) != 255)
				return (OK);
		}
		else
			ft_error(sh->commands[0], ": waitpid failed", 0);
	}
	else
		ft_error(sh->commands[0], ": failed to fork", 0);
	free(path);
	return (ERROR);
}

int			ft_checkaccess(char *path)
{
	struct stat path_stat;

	lstat(path, &path_stat);
	if (access(path, F_OK) != 0)
		return (0);
	else if (access(path, X_OK) != 0 || !S_ISDIR(path_stat.st_mode))
		return (0);
	return (1);
}

static int	ft_elsefuncs(t_sh *sh)
{
	char	*command;
	int		i;

	i = -1;
	while (sh->bindirs && sh->bindirs[++i])
	{
		if (ft_checkaccess(sh->bindirs[i]))
		{
			command = ft_strjoin(sh->bindirs[i], "/");
			command = ft_strjoin(command, sh->commands[0]);
			if (access(command, F_OK) == 0)
			{
				if (access(command, X_OK) != 0)
					return (ft_error(command, ": Permission denied", OK));
				else
				{
					sh->father = fork();
					if (ft_getbinary(command, sh) == OK)
						return (OK);
				}
			}
		}
	}
	return (ERROR);
}

static int	ft_readline(t_sh *sh)
{
	char	**cmds_semi;
	int		i;

	cmds_semi = ft_strsplit(sh->line, ';');
	i = -1;
	while (cmds_semi[++i])
	{
		if(!(sh->envi = ft_getenv(sh)))
			return (ERROR);
		sh->commands = ft_strsplitequ(cmds_semi[i], " \t");
		if (ft_builtinfuncs(sh) == OK)
			;
		else if (ft_elsefuncs(sh) != OK)
			ft_error(sh->commands[0], ": command not found", 0);
		if (sh->commands)
			ft_tabfree((void **)sh->commands);
	}
	ft_tabfree((void **)cmds_semi);
	return(OK);
}

int		ft_prompt(t_sh *sh)
{
	if (sh->line > 0)
		if (ft_readline(sh) != OK)
		{
			free(sh->line);
			return (ERROR);
		}
	ft_printprompt(sh);
	free(sh->line);
	return(OK);
}
