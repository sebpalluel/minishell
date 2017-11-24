/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_struct.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/23 17:04:51 by psebasti          #+#    #+#             */
/*   Updated: 2017/11/24 16:12:03 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_STRUCT_H
# define MINISHELL_STRUCT_H

# include "minishell.h"

typedef void (*builtinfunc)(void *a);

typedef struct		s_env
{

	char			*name;
	char			*value;
	char			*env_str;
}					t_env;

typedef struct		s_sh
{

	t_list			*env;
	char			**bindirs;
	char			**validfuncs;
	char			**envi;
	builtinfunc		*builtins;
	char			*line;
	char			*path;
	pid_t			father;
	char			**commands;
}					t_sh;

#endif
