/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_clean.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/11 18:02:38 by pguillie          #+#    #+#             */
/*   Updated: 2017/03/29 10:15:01 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_ls_lst	*ft_ls_clean_one(t_ls_lst *file)
{
	t_ls_lst	*next;

	next = file->next;
	ft_strdel(&file->path);
	ft_memdel((void**)&file);
	return (next);
}

t_ls_lst	*ft_ls_clean(t_ls_lst *file)
{
	t_ls_lst	*tmp;

	while (file)
	{
		tmp = file->next;
		ft_strdel(&file->path);
		ft_memdel((void**)&file);
		file = tmp;
	}
	return (NULL);
}
