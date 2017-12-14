/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_define.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/23 17:04:37 by psebasti          #+#    #+#             */
/*   Updated: 2017/12/14 12:52:39 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_DEFINE_H
# define MINISHELL_DEFINE_H

# include "minishell.h"

# define ENV(x)			((t_env *)(*(x)->env).content)
# define ENVSTRUCT(x)	((t_env *)(*(x)).content)
# define NUMBUILTIN		8
# define SHELL			"minishell: "
# define CMD_DEL		-1

#endif
