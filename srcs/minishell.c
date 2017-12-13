/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/23 16:45:28 by psebasti          #+#    #+#             */
/*   Updated: 2017/12/13 18:14:21 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/minishell.h"

char		**ft_bindirs(t_sh *sh)
{
	char	**bindirs;
	t_list	*tmp;

	if (sh->bindirs)
		ft_tabfree((void *)sh->bindirs);
	bindirs = NULL;
	if (!(tmp = ft_searchenv(sh->env, "PATH")))
		return (NULL);
	bindirs = ft_strsplit(ENVSTRUCT(tmp)->value, ':');
	return (bindirs);
}

char		**ft_validfuncs(void)
{
	char	**validfuncs;

	if (!(validfuncs = (char**)malloc(sizeof(char*) * NUMBUILTIN)))
		return (NULL);
	validfuncs[0] = ft_strdup("echo");
	validfuncs[1] = ft_strdup("cd");
	validfuncs[2] = ft_strdup("setenv");
	validfuncs[3] = ft_strdup("unsetenv");
	validfuncs[4] = ft_strdup("env");
	validfuncs[5] = ft_strdup("exit");
	validfuncs[6] = ft_strdup("pwd");
	validfuncs[7] = NULL;
	return (validfuncs);
}

builtinfunc		*ft_validfuncsptr(void)
{
	builtinfunc	*builtins;

	if (!(builtins = malloc(sizeof(builtinfunc) * NUMBUILTIN)))
		return (NULL);
	builtins[0] = ft_echo;
	builtins[1] = ft_cd;
	builtins[2] = ft_setenv;
	builtins[3] = ft_unsetenv;
	builtins[4] = ft_env;
	builtins[5] = ft_exit;
	builtins[6] = ft_pwd;
	builtins[7] = NULL;
	return (builtins);
}

int				ft_error(char *shell, char *command, \
		const char *error, int r_val)
{
	ft_putstr_fd(shell, 2);
	ft_putstr_fd(command, 2);
	ft_putendl_fd(error, 2);
	if (r_val == CMD_DEL)
		free(command);
	return(r_val);
}

int			main(int argc, char **argv, char **envp)
{
	t_sh	*sh;

	if (!(sh = (t_sh*)ft_memalloc(sizeof(t_sh))) || \
			!(sh->env = ft_envlist(envp)) || \
			!(sh->bindirs = ft_bindirs(sh)) || \
			!(sh->validfuncs = ft_validfuncs()) || \
			!(sh->builtins = ft_validfuncsptr()) || \
			!(sh->path = ft_getpath(sh)))
		return (EXIT_FAILURE);
	argc = 0;
	argv = NULL;
	sh->return_col = OK;
	ft_printprompt(sh);
	while (get_next_line(0, &sh->line) >= 0)
		if (ft_prompt(sh) != OK)
			return (EXIT_FAILURE);
	//if (env->imp_func)
	//	free_env(env->imp_func);
	//if (env->bindirs)
	//	free_env(env->bindirs);
	//free(env);
	//if (argc || argv)
	//	return (1);
	return (EXIT_SUCCESS);
}
