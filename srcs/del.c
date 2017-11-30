/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 11:12:09 by psebasti          #+#    #+#             */
/*   Updated: 2017/11/30 11:14:50 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	free_liste(t_liste *lst)
{
	free(lst->nom);
	free(lst->valeur);
	free(lst);
}

static void	suppr_cont_env(t_liste *tmp, t_liste *tmp2, char *nom)
{
	tmp = g_env;
	if (ft_strcmp(tmp->nom, nom) == 0)
	{
		tmp2 = tmp->next;
		free_liste(tmp);
		g_env = tmp2;
		return ;
	}
	while (tmp->next && ft_strcmp(tmp->next->nom, nom))
		tmp = tmp->next;
	if (tmp->next->next)
	{
		tmp2 = tmp->next->next;
		free_liste(tmp->next);
		tmp->next = tmp2;
	}
	else
	{
		free_liste(tmp->next);
		tmp->next = NULL;
	}
}

void		ft_delenvelem(t_sh *sh, char *name)
{
	t_list	*tmp;
	t_list	*tmp2;
	char	*tmp3;

	tmp2 = NULL;
	tmp3 = ft_strjoin("$", name);
	tmp = ft_searchenv(sh->env, name);
	free(tmp3);
	if (tmp == NULL)
		return (ft_erreur(name, 2));
	else
		suppr_cont_env(tmp, tmp2, name);
	return ;
}
