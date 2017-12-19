/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 12:56:51 by psebasti          #+#    #+#             */
/*   Updated: 2017/12/19 12:05:00 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int				ft_checkaccess(char *shell, char *path, int mode, int env_mode)
{
	struct stat path_stat;
	int			ret;

	lstat(path, &path_stat);
	if (access(path, F_OK) != OK)
		return (ret = mode ? ERROR : \
				ft_error(shell, path, ": No such file or directory", ERROR));
	else if (!env_mode)
	{
		if (!S_ISDIR(path_stat.st_mode))
			return (ret = mode ? ERROR : \
					ft_error(shell, path, ": Not a directory", ERROR));
	}
	else if (access(path, X_OK) != OK)
		return (ret = mode ? ERROR : \
				ft_error(shell, path, ": Permission denied", ERROR));
		return (OK);
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
	t_list		*tmp;

	path = NULL;
	home = NULL;
	cwd = getcwd(sh->buff, PATH_MAX);
	tmp = ft_searchenv(sh->env, "HOME");
	if (!cwd || !tmp)
		return (NULL);
	if (!(home = ENVSTRUCT(ft_searchenv(sh->env, "HOME"))->value))
	{
		free(cwd);
		return (ft_strdup(cwd));
	}
	path = ft_pathfromhome(cwd, home);
	return (path);
}
