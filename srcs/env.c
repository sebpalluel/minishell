/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 17:33:46 by psebasti          #+#    #+#             */
/*   Updated: 2017/11/15 19:47:36 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char			*ft_findenv(t_list *env, char *name)
{
	while (env)
	{
		if (!ft_strcmp(ENVSTRUCT(env)->name, name))
			return (ENVSTRUCT(env)->value);
		env = env->next;
	}
	return (NULL);
}

static char		*ft_pathfromhome(char *cwd, char *home)
{
	char		*tmp;
	int			i;

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

char			*ft_getpath(t_sh *sh)
{
	char		*cwd;
	char		*path;
	char		*home;
	char		buff[2048];

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

static t_list	*ft_newenv(char *str)
{
	t_list		*env;
	char		*tmp;

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

t_list			*ft_envlist(char **envp)
{
	int			env_num;
	t_list		*env;

	env = NULL;
	env_num = -1;
	while(envp[++env_num])
		ft_lstaddend(&env, ft_newenv(envp[env_num]));
	return(env);
}

char		**ft_getenv(t_sh *sh)
{
	char	**envtab;
	char	*str;
	int		i;
	t_list	*tmp;

	envtab = (char **)malloc(sizeof(char*) * ft_lstlen(sh->env));
	tmp = sh->env;
	i = -1;
	while (tmp)
	{
		str = ft_strnew(0);
		str = ft_strjoinfree(str, ENVSTRUCT(tmp)->name, 1);
		str = ft_strjoinfree(str, "=", 1);
		str = ft_strjoinfree(str, ENVSTRUCT(tmp)->value, 1);
		envtab[++i] = ft_strdup(str);
		free(str);
		tmp = tmp->next;
	}
	envtab[i] = NULL;
	return (envtab);
}
