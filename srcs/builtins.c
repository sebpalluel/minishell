/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 14:10:14 by psebasti          #+#    #+#             */
/*   Updated: 2017/11/15 15:21:41 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_echo(void *a)
{
	if (a)
		printf("echo\n");
}

void	ft_cd(void *a)
{
	if (a)
		printf("cd\n");
}

void	ft_setenv(void *a)
{
	if (a)
		printf("setenv\n");
}

void	ft_unsetenv(void *a)
{
	if (a)
		printf("unsetenv\n");
}

void	ft_env(void *a)
{
	if (a)
		printf("env\n");
}

void	ft_exit(void *a)
{
	if (a)
		printf("exit\n");
}
