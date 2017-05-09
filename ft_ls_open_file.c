/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_open_file.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/18 17:15:06 by pguillie          #+#    #+#             */
/*   Updated: 2017/04/05 13:49:42 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		ft_ls_subdir_del(t_ls_lst **b, t_ls_lst **p, t_ls_lst **c)
{
	t_ls_lst	*n;

	n = (*c)->next;
	ft_strdel(&((*c)->path));
	ft_memdel((void**)&(*c));
	if (!*p)
		*b = n;
	else
		(*p)->next = n;
	(*c) = n;
}

static t_ls_lst	*ft_ls_subdir(t_ls_lst *begin)
{
	t_ls_lst	*curr;
	t_ls_lst	*prev;
	char		*n;

	prev = NULL;
	curr = begin;
	while (curr)
	{
		ft_strrchr(curr->path, '/') ?
			n = ft_strrchr(curr->path, '/') + 1 : 0;
		if (!S_ISDIR(curr->s_stat.st_mode)
				|| ft_strequ(n, ".") || ft_strequ(n, ".."))
			ft_ls_subdir_del(&begin, &prev, &curr);
		else
		{
			prev = curr;
			curr = curr->next;
		}
	}
	return (begin);
}

static t_ls_lst	*ft_ls_store_entry(char *path, DIR *dirp, char *opt)
{
	struct dirent	*entry;
	t_ls_lst		*files;
	int				format[FORMAT_SIZE];
	int				nb_files;

	nb_files = 0;
	files = NULL;
	ft_ls_init_format(format);
	while ((entry = readdir(dirp)))
	{
		if (entry->d_name[0] != '.' || ft_strchr(opt, 'a'))
		{
			files = ft_ls_add(files, ft_ls_pathname(path, entry->d_name), opt,
					format);
			nb_files++;
		}
	}
	if (files && ft_ls_srch_opt(opt, 3, 'l', 's', 'g'))
		ft_printf("total %d\n", format[0]);
	if (!files && nb_files && ft_strchr(opt, 'R'))
		ft_ls_error(ft_strrchr(path, '/') ? ft_strrchr(path, '/') + 1 : path);
	ft_ls_display(files, opt, format);
	files = ft_strchr(opt, 'R') ? ft_ls_subdir(files) : ft_ls_clean(files);
	return (files);
}

void			ft_ls_open_file(char *path, char *opt)
{
	DIR			*dirp;
	t_ls_lst	*subdir;

	subdir = NULL;
	if (!(dirp = opendir(path)))
		ft_ls_error(ft_strrchr(path, '/') ? ft_strrchr(path, '/') + 1 : path);
	if (dirp)
	{
		subdir = ft_ls_store_entry(path, dirp, opt);
		closedir(dirp);
	}
	while (subdir)
	{
		ft_printf("\n%s:\n", subdir->path);
		ft_ls_open_file(subdir->path, opt);
		subdir = ft_ls_clean_one(subdir);
	}
}
