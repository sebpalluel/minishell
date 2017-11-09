/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/23 16:45:28 by psebasti          #+#    #+#             */
/*   Updated: 2017/11/09 15:19:16 by psebasti         ###   ########.fr       */
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
	ENV(env)->env_str = ft_strdup(str);
	ENV(env)->name = ft_strsub(str, 0, ft_strchr(str, '=') - str);
	tmp = ft_strchr(str, '=') + 1;
	if (!*tmp)
		ENV(env)->value = ft_strdup("");
	else
		ENV(env)->value = ft_strdup(tmp);
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

int			main(int argc, char **argv, char **envp)
{
	t_list	*env;
	char	**bindirs;

	if (!(env = ft_envlist(envp)) || !(bindirs = ft_bindirs(envp)))
		return (EXIT_FAILURE);
	//init_implement_functions(env->content);
	argc = 0;
	argv = NULL;
	int	i;
	i = -1;
	while (42)
	{
		//ft_putstr("$> ");
		//prompt(data, 0, 0);
		//if (data->imp_func)
		//	free_env(data->imp_func);
		//if (data->bindirs)
		//	free_env(data->bindirs);
		//free(data);
		//if (argc || argv)
		//	return (1);
	}
	return (0);
}
