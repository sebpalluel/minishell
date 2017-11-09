/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/23 16:45:28 by psebasti          #+#    #+#             */
/*   Updated: 2017/11/09 17:16:01 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_list		*ft_newenv(char *str)
{
	t_list	*env;
	char	*tmp;

	if (!(env = (t_list*)malloc(sizeof(t_env))) || \
			!(env->content = (t_env*)ft_memalloc(sizeof(t_env))))
		exit(EXIT_FAILURE);
	ENVSTRUCT(env)->env_str = ft_strdup(str);
	ENVSTRUCT(env)->name = ft_strsub(str, 0, ft_strchr(str, '=') - str);
	tmp = ft_strchr(str, '=') + 1;
	if (!*tmp)
		ENVSTRUCT(env)->value = ft_strdup("");
	else
		ENVSTRUCT(env)->value = ft_strdup(tmp);
	env->next = NULL;
	return (env);
}

t_list		*ft_envlist(char **envp)
{
	int		env_num;
	t_list	*env;

	env = NULL;
	env_num = -1;
	while(envp[++env_num])
		ft_lstaddend(&env, ft_newenv(envp[env_num]));
	return(env);
}

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

//int			verif_implements(t_sh *sh)
//{
//	FT_INIT(char**, functions, env->imp_func);
//	FT_INIT(int, i, 0);
//	while (functions[i])
//	{
//		if (ft_strlen(cmd) == 0)
//			return (0);
//		if (!ft_strcmp(cmd, functions[i]))
//			return (1);
//		i++;
//	}
//	return (0);
//}
//
//void		ft_prompt(t_sh *sh)
//{
//	int		ret;
//	int		pid;
//
//	sh->line = NULL;
//	sh->commands = NULL;
//	while (42)
//	{
//		ft_putstr("$> ");
//		if ((ret = get_next_line(0, &sh->line)) >= 0)
//		{
//			if (sh->line > 0)
//			ft_read_line(sh);
//			if (verif_implements(commands[0], env))
//				distrib_functions(commands, env);
//			else
//			{
//				pid = fork();
//				if (pid == 0)
//				{
//					lsh_launch(commands, env, 0);
//					exit(0);
//				}
//			}
//			free_env(commands);
//		}
//		free(sh->line);
//		wait(&pid);
//		ft_putstr("\n$> ");
//	}
//}

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

char	*ft_findenv(t_list *env, char *name)
{
	while (env)
	{
		if (!ft_strcmp(ENVSTRUCT(env)->name, name))
			return (ENVSTRUCT(env)->value);
		env = env->next;
	}
	return (NULL);
}

char	*ft_pathfromhome(char *cwd, char *home)
{
	char	*tmp;
	int		i;

	i = -1;
	while (*home && cwd[++i] && (cwd[i] == *home))
		++home;
	if (*home)
		return (ft_strdup(cwd));
	if (!cwd[i + 1])
		return (ft_strdup("~"));
	home = ft_strsub(cwd + i + 1, 0, ft_strlen(cwd) - i - 1);
	tmp = ft_strjoin("~", home);
	return (tmp);
}

char		*ft_getpath(t_sh *sh)
{
	char	*cwd;
	char	*path;
	char	*home;
	char	buff[2048];

	path = NULL;
	home = NULL;
	if (!(cwd = getcwd(buff, 2048)))
		return(NULL);
	if (!(home = ft_findenv(sh->env, "HOME")))
	{
		free(cwd);
		return(ft_strdup(cwd));
	}
	path = ft_pathfromhome(cwd, home);
	free(home);
	return(path);
}

void		ft_printprompt(t_sh *sh)
{
	ft_putstr("[minishell:");
	ft_putstr(sh->path);
	ft_putstr("] $> ");
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
	//init_implement_functions(env->content);
	argc = 0;
	argv = NULL;
	ft_printprompt(sh);
	//ft_prompt(sh);
	//if (env->imp_func)
	//	free_env(env->imp_func);
	//if (env->bindirs)
	//	free_env(env->bindirs);
	//free(env);
	//if (argc || argv)
	//	return (1);
	return (0);
}
