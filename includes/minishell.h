/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/23 17:01:42 by psebasti          #+#    #+#             */
/*   Updated: 2017/12/18 19:36:04 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/includes/libft.h"
# include "minishell_struct.h"
# include "minishell_define.h"
# include <termios.h>

t_list			*ft_envlist(char **envp);
void			ft_handlectrlc(int sig);
int				ft_elsefuncs(t_sh *sh);
char			**ft_bindirs(t_sh *sh);
void			ft_editenv(t_list *env, char *name, char *value);
int				ft_error(char *shell, char *command, const char *error, \
		int r_val);
char			*ft_getpath(t_sh *sh);
t_list			*ft_searchenv(t_list *env, char *name);
void			ft_delenvelem(t_list **env, char *name);
void			ft_delenvnode(void *content, size_t size);
int				ft_delmatch(void *content, void *name);
int				ft_prompt(t_sh *sh);
void			ft_printprompt(t_sh *sh);
char			**ft_getenv(t_sh *sh);
int				ft_checkaccess(char *shell, char *path, int mode, int env_mode);
void			ft_echo(void *a);
void			ft_cd(void *a);
void			ft_setenv(void *a);
void			ft_unsetenv(void *a);
void			ft_env(void *a);
void			ft_exit(void *a);
void			ft_pwd(void *a);

pid_t			g_father;
#endif
