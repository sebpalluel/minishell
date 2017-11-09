/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/23 17:01:42 by psebasti          #+#    #+#             */
/*   Updated: 2017/11/09 18:39:08 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/includes/libft.h"
# include "minishell_struct.h"
# include "minishell_define.h"

t_list			*ft_envlist(char **envp);
char			*ft_getpath(t_sh *sh);
char			*ft_findenv(t_list *env, char *name);
void			ft_prompt(t_sh *sh);
void			ft_printprompt(t_sh *sh);

#endif
