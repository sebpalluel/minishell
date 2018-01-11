/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elsefuncs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 12:55:49 by psebasti          #+#    #+#             */
/*   Updated: 2018/01/11 18:27:34 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int		ft_getbinary(char *path, t_sh *sh)
{
	int			status;
	int			es;

	if (g_father == 0)
	{
		es = execve(path, sh->commands, sh->envi);
		exit(es);
	}
	if (g_father > 0)
	{
		signal(SIGINT, ft_handlectrlc);
		if (waitpid(g_father, &status, 0) > 0)
		{
			if (WEXITSTATUS(status) == 127)
				ft_error(SHELL, sh->commands[0], ": execve failed", 0);
			if ((sh->return_col = WEXITSTATUS(status)) != 255)
				return (OK);
		}
		else
			return (ft_error(SHELL, sh->commands[0], ": waitpid failed", OK));
	}
	else
		ft_error(SHELL, sh->commands[0], ": failed to fork", OK);
	return (ERROR);
}

static char		*ft_getcmd(t_sh *sh, int i)
{
	char		*command;

	if (sh->bindirs && ft_strchr(sh->commands[0], '/') == OK)
	{
		command = ft_strjoin(sh->bindirs[i], "/");
		command = ft_strjoinfree(command, sh->commands[0], 1);
	}
	else
		command = ft_strdup(sh->commands[0]);
	return (command);
}

static int		ft_elsefuncscore(t_sh *sh, int i)
{
	char		*command;

	command = ft_getcmd(sh, i);
	if (access(command, F_OK) == 0)
	{
		if ((sh->return_col = access(command, X_OK) != OK))
			return (ft_error(SHELL, command, ": Permission denied", CMD_DEL));
		else
		{
			g_father = fork();
			if (ft_getbinary(command, sh) == OK)
			{
				free(command);
				return (OK);
			}
		}
	}
	free(command);
	return (ERROR);
}

int				ft_elsefuncs(t_sh *sh)
{
	int			i;

	if (ft_elsefuncscore(sh, 0) != ERROR)
		return (OK);
	i = -1;
	while (sh->bindirs && sh->bindirs[++i])
	{
		if (ft_checkaccess(SHELL, sh->bindirs[i], 1, 0) == OK)
			if (ft_elsefuncscore(sh, i) != ERROR)
				return (OK);
	}
	return (ERROR);
}

int				ft_del(t_sh *sh, int ret)
{
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
	return (ret);
}
