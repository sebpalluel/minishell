/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 17:32:06 by psebasti          #+#    #+#             */
/*   Updated: 2017/11/09 19:32:21 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_printprompt(t_sh *sh)
{
	ft_putstr(ANSI_RESET);
	ft_putstr(ANSI_BOLD);
	ft_putstr(ANSI_RED);
	ft_putstr("minishell:");
	ft_putstr(ANSI_RESET);
	ft_putstr(ANSI_GREEN);
	ft_putstr(sh->path);
	ft_putstr(ANSI_BLINK);
	ft_putstr(ANSI_RED);
	ft_putstr(" $> ");
	ft_putstr(ANSI_RESET);
	ft_putstr(ANSI_BLINK);
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

void		ft_readline(t_sh *sh)
{
	sh->commands = ft_strsplitequ(sh->line, " \t");
}

void		ft_prompt(t_sh *sh)
{
	int		pid;

	if (sh->line > 0)
		ft_readline(sh);
	ft_printprompt(sh);
	free(sh->line);
	wait(&pid);
}
