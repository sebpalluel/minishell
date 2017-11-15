/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 17:32:06 by psebasti          #+#    #+#             */
/*   Updated: 2017/11/15 20:07:03 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

pid_t	pid;

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


void		sig_hand(int sig)
{
	if (sig == SIGINT)
	{
		kill(pid, sig);
		ft_putchar('\n');
	}
}

void	ft_getbinary(char *path, t_sh *sh)
{
	char	**envi;

	envi = ft_getenv(sh);
	pid = fork();
	if (pid > 0)
	{
		signal(SIGINT, sig_hand);
		wait(NULL);
		signal(SIGINT, SIG_DFL);
	}
	else if (pid == 0)
	{
		execve(path, sh->commands, envi);
		exit(EXIT_SUCCESS);
	}
	pid = -1;
	free(path);
}

int			ft_checkaccess(char *path)
{
	struct stat statpath;

	lstat(path, &statpath);
	if (access(path, F_OK) != 0)
		return (0);
	else if (access(path, X_OK) != 0 || !S_ISDIR(statpath.st_mode))
		return (0);
	else if (!S_ISDIR(statpath.st_mode))
		return (0);
	return (1);
}

static int	ft_elsefuncs(t_sh *sh)
{
	char	*command;
	int		i;

	//if (is_absolute(sh))
	//	return (1);
	//if (!(content = find_env(sh, "PATH")))
	//	return (0);
	//tmp = ft_strsplit(content, ':');
	//content = sh->commands[0];
	//if (ft_strrchr(content, '/'))
	//	content = ft_strrchr(content, '/') + 1;
	//i = -1;
	//while (tmp[++i])
	//{
	//	if (check_path(content, tmp[i]))
	//	{
	//		return (1);
	//	}
	//}
	i = -1;
	while (sh->bindirs && sh->bindirs[++i])
	{
		if (ft_checkaccess(sh->bindirs[i]))
		{
			command = ft_strjoin(sh->bindirs[i], "/");
			command = ft_strjoin(command, sh->commands[0]);
			ft_getbinary(command, sh);
			if (pid != -1)
				return (1);
		}
	}
	return (0);
}

void		ft_readline(t_sh *sh)
{
	char	**cmds_semi;
	int		i;

	cmds_semi = ft_strsplit(sh->line, ';');
	i = -1;
	while (cmds_semi[++i])
	{
		sh->commands = ft_strsplitequ(cmds_semi[i], " \t");
		if (ft_builtinfuncs(sh) == OK)
			;
		else if (ft_elsefuncs(sh))
			;
		else
		{
			ft_putstr_fd(sh->commands[0], 2);
			ft_putendl_fd(": Command not found.", 2);
		}
		if (sh->commands)
			ft_tabfree((void **)sh->commands);
	}
	ft_tabfree((void **)cmds_semi);
}

void		ft_prompt(t_sh *sh)
{
	if (sh->line > 0)
		ft_readline(sh);
	ft_printprompt(sh);
	free(sh->line);
	wait(&sh->pid);
}
