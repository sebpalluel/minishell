/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 17:32:06 by psebasti          #+#    #+#             */
/*   Updated: 2017/11/09 18:41:41 by psebasti         ###   ########.fr       */
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

int			ft_countcommands(char *str)
{
	int		count;

	count = 0;
	while (*str)
	{
		if (*str != ' ' && *str != '\t')
		{
			while (*str && *str != ' ' && *str != '\t')
				++str;
			++count;
		}
		else
			++str;
	}
	return (count);
}

static void	ft_initcommands(t_sh *sh)
{
	char	*tmp;
	int		i;
	int		j;

	j = -1;
	if (!(sh->commands = (char**)malloc(sizeof(char*) * \
					(ft_countcommands(sh->line) + 1))))
		exit(EXIT_FAILURE);
	while (*sh->line)
	{
		if (*sh->line != ' ' && *sh->line != '\t')
		{
			tmp = sh->line;
			i = 0;
			while (*sh->line && *sh->line != ' ' && *sh->line != '\t')
			{
				++i;
				++sh->line;
			}
			sh->commands[++j] = ft_strsub(tmp, 0, i);
		}
		else
			++sh->line;
	}
	sh->commands[++j] = NULL;
}

void		ft_readline(t_sh *sh)
{
	ft_initcommands(sh);

}

void		ft_prompt(t_sh *sh)
{
	int		pid;

	if (sh->line > 0)
		ft_readline(sh);
	ft_printprompt(sh);
	free(sh->line);
	wait(&pid);
	ft_putstr("\n$> ");
}
