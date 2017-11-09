/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/23 16:45:28 by psebasti          #+#    #+#             */
/*   Updated: 2017/11/09 12:13:42 by psebasti         ###   ########.fr       */
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
	printf("env str %s\n", str);
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

int			main(int argc, char **argv, char **envp)
{
	t_list	*env;

	env = ft_envlist(envp);
	printf("env str after %s\n", ENV(env)->env_str);
	//init_implement_functions(env->content);
	argc = 0;
	argv = NULL;
	while (42)
	{
		//init_env(&(data->env), envp, NULL);
		//data->bin_directories = get_bin_directories(envp);
		//ft_putstr("$> ");
		//prompt(data, 0, 0);
		//if (data->imp_func)
		//	free_env(data->imp_func);
		//if (data->bin_directories)
		//	free_env(data->bin_directories);
		//free(data);
		//if (argc || argv)
		//	return (1);
	}
	return (0);
}
