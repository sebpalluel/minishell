/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/23 17:01:42 by psebasti          #+#    #+#             */
/*   Updated: 2017/11/24 17:38:23 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/includes/libft.h"
# include "minishell_struct.h"
# include "minishell_define.h"

t_list			*ft_envlist(char **envp);
int				ft_error(char *command, const char *error, int r_val);
char			*ft_getpath(t_sh *sh);
char			*ft_findenv(t_list *env, char *name);
int				ft_prompt(t_sh *sh);
void			ft_printprompt(t_sh *sh);
char			**ft_getenv(t_sh *sh);
void			ft_echo(void *a);
void			ft_cd(void *a);
void			ft_setenv(void *a);
void			ft_unsetenv(void *a);
void			ft_env(void *a);
void			ft_exit(void *a);

#endif
