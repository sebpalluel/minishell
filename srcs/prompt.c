/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 17:32:06 by psebasti          #+#    #+#             */
/*   Updated: 2017/11/16 17:29:58 by psebasti         ###   ########.fr       */
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

int			ft_getbinary(char *path, t_sh *sh)
{
	char	**envi;
	int		exec_ret;
	int		status;
	int		es;

	envi = ft_getenv(sh);
	//printf("pid %d\n", pid);
	if (pid > 0)
	{
		signal(SIGINT, sig_hand);
		printf("wait %d\n",wait(NULL));
		signal(SIGINT, SIG_DFL);
	}
	else if (pid == 0)
	{
		errno = 0;
	printf("cmd %s, commands %s\n", path, sh->commands[0]);
		exec_ret = execv(path, sh->commands);
		printf("execv_ret %d errno %d\n",exec_ret, errno);
		exit(EXIT_FAILURE);
	}
    if ( waitpid(pid, &status, 0) == -1 ) {
        perror("waitpid failed");
       // return EXIT_FAILURE;
    }
    if (WIFEXITED(status) ) {
		es = 0;
        es = WEXITSTATUS(status);
        printf("exit status was %d\n", es);
    }
	pid = -1;
	free(path);
	return (0);
}

//int runcmd(char *cmd, t_sh *sh)
//{
//  pid_t child_pid;
//  pid_t	tpid;
//  int child_status;
//
//  child_pid = fork();
//  if(child_pid == 0) {
//    /* This is done by the child process. */
//
//	printf("cmd %s, commands %s\n", cmd, sh->commands[0]);
//    execv(cmd, sh->commands);
//
//    /* If execv returns, it must have failed. */
//
//    printf("Unknown command\n");
//    exit(0);
//  }
//  else {
//     /* This is run by the parent.  Wait for the child
//        to terminate. */
//
//     do {
//       tpid = wait(&child_status);
//       if(tpid != child_pid) printf("process terminated %d\n",tpid);
//     } while(tpid != child_pid);
//
//     return child_status;
//  }
//	free(cmd);
//}

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
	size_t	had_command;

	i = -1;
	while (sh->bindirs && sh->bindirs[++i])
	{
		if (ft_checkaccess(sh->bindirs[i]))
		{
			pid = fork();
			command = ft_strjoin(sh->bindirs[i], "/");
			command = ft_strjoin(command, sh->commands[0]);
			had_command = ft_getbinary(command, sh);
			if (pid != -1)
			{
				printf("had_command\n");
				return (1);
			}
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
	//wait(&sh->pid);
}
