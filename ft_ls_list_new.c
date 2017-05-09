/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_list_new.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/18 11:31:19 by pguillie          #+#    #+#             */
/*   Updated: 2017/04/05 13:53:37 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_ls_lst	*ft_ls_list_new(char *name, struct stat *stat_addr)
{
	t_ls_lst	*new;

	if (!(new = (t_ls_lst*)ft_memalloc(sizeof(t_ls_lst))))
		return (NULL);
	new->s_stat = *stat_addr;
	if (!(new->path = ft_strdup(name)))
	{
		ft_memdel((void**)&new);
		return (NULL);
	}
	return (new);
}
