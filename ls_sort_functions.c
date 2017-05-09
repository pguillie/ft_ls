/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_sort_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/09 16:41:21 by pguillie          #+#    #+#             */
/*   Updated: 2017/04/05 12:06:20 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		ft_ls_cmp_name(t_ls_lst *a, t_ls_lst *b)
{
	return (ft_strcmp(a->path, b->path) <= 0 ? 1 : 0);
}

int		ft_ls_cmp_mtime(t_ls_lst *a, t_ls_lst *b)
{
	if (a->s_stat.st_mtime == b->s_stat.st_mtime)
		return (ft_ls_cmp_name(a, b));
	if (a->s_stat.st_mtime > b->s_stat.st_mtime)
		return (1);
	return (0);
}

int		ft_ls_cmp_size(t_ls_lst *a, t_ls_lst *b)
{
	if (a->s_stat.st_size == b->s_stat.st_size)
		return (ft_ls_cmp_name(a, b));
	if (a->s_stat.st_size > b->s_stat.st_size)
		return (1);
	return (0);
}

int		ft_ls_cmp_atime(t_ls_lst *a, t_ls_lst *b)
{
	if (a->s_stat.st_atime == b->s_stat.st_atime)
		return (ft_ls_cmp_name(a, b));
	if (a->s_stat.st_atime > b->s_stat.st_atime)
		return (1);
	return (0);
}
