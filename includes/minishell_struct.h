/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_struct.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/23 17:04:51 by psebasti          #+#    #+#             */
/*   Updated: 2017/12/20 17:01:32 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_STRUCT_H
# define MINISHELL_STRUCT_H

# include "minishell.h"
# include "minishell_define.h"

typedef struct		s_builtins
{
	void			(*builtinfunc)(void *a);
}					t_builtins;

typedef struct		s_env
{
	char			*name;
	char			*value;
}					t_env;

typedef struct		s_sh
{
	t_list			*env;
	char			**bindirs;
	char			**validfuncs;
	char			**envi;
	t_builtins		*builtins;
	char			*line;
	char			*path;
	pid_t			father;
	char			**commands;
	char			buff[PATH_MAX];
	int				return_col;
}					t_sh;

#endif
