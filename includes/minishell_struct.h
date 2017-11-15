/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_struct.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/23 17:04:51 by psebasti          #+#    #+#             */
/*   Updated: 2017/11/15 14:06:22 by psebasti         ###   ########.fr       */
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
	builtinfunc		*builtins;
	char			*line;
	char			*path;
	char			**commands;
	int				pid;
}					t_sh;

#endif
