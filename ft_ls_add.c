/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_add.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/19 15:45:27 by pguillie          #+#    #+#             */
/*   Updated: 2017/04/05 13:53:44 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char			*ft_ls_pathname(char *path, char *name)
{
	return (ft_strcat(ft_strcat(ft_strcpy(ft_strnew(ft_strlen(path)
			+ ft_strlen(name) + (ft_strequ(path, "/") ? 0 : 1)), path),
			ft_strequ(path, "/") ? "" : "/"), name));
}

static int		(*ft_ls_find_cmp(char *opt))(t_ls_lst*, t_ls_lst*)
{
	if (ft_strchr(opt, 'S'))
		return (ft_ls_cmp_size);
	else if (ft_strchr(opt, 't'))
	{
		if (ft_strchr(opt, 'u'))
			return (ft_ls_cmp_atime);
		else
			return (ft_ls_cmp_mtime);
	}
	else
		return (ft_ls_cmp_name);
}

static t_ls_lst	*ft_ls_insert(t_ls_lst *begin, t_ls_lst *new, int rev,
		int (*cmp)(t_ls_lst*, t_ls_lst*))
{
	t_ls_lst	*prev;
	t_ls_lst	*file;

	if (!begin)
		begin = new;
	else
	{
		prev = NULL;
		file = begin;
		while (file && rev - cmp(file, new))
		{
			prev = file;
			file = file->next;
		}
		new->next = file;
		if (!prev)
			begin = new;
		else
			prev->next = new;
	}
	return (begin);
}

t_ls_lst		*ft_ls_add(t_ls_lst *begin, char *name, char *opt, int *format)
{
	t_ls_lst	*new;
	struct stat	tmp_stat;
	int			rev;
	char		*end_name;

	if (!name || lstat(name, &tmp_stat) < 0)
	{
		ft_ls_error(ft_strrchr(name, '/') ? ft_strrchr(name, '/') + 1 : name);
		name ? ft_strdel(&name) : 0;
		return (begin);
	}
	end_name = ft_strrchr(name, '/');
	!end_name ? end_name = name : end_name + 1;
	ft_ls_update_format(format, tmp_stat, end_name);
	new = ft_ls_list_new(name, &tmp_stat);
	ft_strdel(&name);
	rev = ft_strchr(opt, 'r') ? 1 : 0;
	begin = ft_ls_insert(begin, new, rev, ft_ls_find_cmp(opt));
	return (begin);
}

t_ls_lst		*ft_ls_reg_add(
		t_ls_lst *begin, t_ls_lst *new, char *opt, int *format)
{
	int		rev;

	new->next = NULL;
	ft_ls_update_format(format, new->s_stat, new->path);
	rev = ft_strchr(opt, 'r') ? 1 : 0;
	begin = ft_ls_insert(begin, new, rev, ft_ls_find_cmp(opt));
	return (begin);
}
