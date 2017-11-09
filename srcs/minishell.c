/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/23 16:45:28 by psebasti          #+#    #+#             */
/*   Updated: 2017/11/09 18:40:28 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char		**ft_bindirs(char **envp)
{
	char	**bindirs;
	char	*tmp;
	int		i;

	bindirs = NULL;
	tmp = NULL;
	if (!envp)
		return (NULL);
	i = -1;
	while (envp && envp[++i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 5) && (tmp = ft_strchr(envp[i], '=')))
		{
			tmp = ft_strsub(tmp, 1, ft_strlen(tmp) - 1);
			bindirs = ft_strsplit(tmp, ':');
			free(tmp);
			break ;
		}
	}
	return (bindirs);
}

char		**ft_validfuncs(void)
{
	char	**validfuncs;

	if (!(validfuncs = (char**)malloc(sizeof(char*) * 7)))
		return (NULL);
	validfuncs[0] = ft_strdup("echo");
	validfuncs[1] = ft_strdup("cd");
	validfuncs[2] = ft_strdup("setenv");
	validfuncs[3] = ft_strdup("unsetenv");
	validfuncs[4] = ft_strdup("env");
	validfuncs[5] = ft_strdup("exit");
	validfuncs[6] = NULL;
	return (validfuncs);
}



int			main(int argc, char **argv, char **envp)
{
	t_sh	*sh;

	if (!(sh = (t_sh*)ft_memalloc(sizeof(t_sh))) || \
			!(sh->env = ft_envlist(envp)) || \
			!(sh->bindirs = ft_bindirs(envp)) || \
			!(sh->validfuncs = ft_validfuncs()) || \
			!(sh->path = ft_getpath(sh)))
		return (EXIT_FAILURE);
	argc = 0;
	argv = NULL;
	ft_printprompt(sh);
	while (get_next_line(0, &sh->line) >= 0)
		ft_prompt(sh);
	//if (env->imp_func)
	//	free_env(env->imp_func);
	//if (env->bindirs)
	//	free_env(env->bindirs);
	//free(env);
	//if (argc || argv)
	//	return (1);
	return (0);
}
