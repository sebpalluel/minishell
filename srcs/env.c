/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 17:33:46 by psebasti          #+#    #+#             */
/*   Updated: 2017/12/10 17:23:41 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_list			*ft_searchenv(t_list *env, char *name)
{
	t_list		*list;

	list = env;
	while (list)
	{
		if (ft_strcmp(name, ENVSTRUCT(list)->name) == OK)
			return (list);
		list = list->next;
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
	free(home);
	return (tmp);
}

char			*ft_getpath(t_sh *sh)
{
	char		*cwd;
	char		*path;
	char		*home;

	path = NULL;
	home = NULL;
	if (!(cwd = getcwd(sh->buff, BUFF_CWD)))
		return(NULL);
	if (!(home = ENVSTRUCT(ft_searchenv(sh->env, "HOME"))->value))
	{
		free(cwd);
		return(ft_strdup(cwd));
	}
	path = ft_pathfromhome(cwd, home);
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

char			**ft_getenv(t_sh *sh)
{
	char		**envtab;
	char		*str;
	int			i;
	t_list		*tmp;

	if (sh->envi)
		ft_tabfree((void **)sh->envi);
	if (!(envtab = (char **)malloc(sizeof(char*) * ft_lstlen(sh->env))))
		return (NULL);
	tmp = sh->env;
	i = -1;
	while (tmp)
	{
		str = ft_strdup(ENVSTRUCT(tmp)->name);
		str = ft_strjoinfree(str, "=", 1);
		str = ft_strjoinfree(str, ENVSTRUCT(tmp)->value, 1);
		envtab[++i] = ft_strdup(str);
		free(str);
		tmp = tmp->next;
	}
	envtab[i] = NULL;
	return (envtab);
}

void			ft_editenv(t_list *env, char *name, char *value)
{
	char		*tmp;
	t_list		*list;

	list = ft_searchenv(env, name);
	tmp = NULL;
	if (list == NULL)
	{
		tmp = ft_strjoin(name, "=");
		tmp = ft_strjoinfree(tmp, value, 1);
		ft_lstaddend(&env, ft_newenv(tmp));
		free(tmp);
	}
	else
	{
		free(ENVSTRUCT(list)->value);
		ENVSTRUCT(list)->value = ft_strdup(value);
	}
}
