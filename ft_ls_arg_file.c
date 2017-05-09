/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_arg_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/18 12:15:03 by pguillie          #+#    #+#             */
/*   Updated: 2017/04/05 12:35:03 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static char		**ft_ls_arg_sort(char **av)
{
	char	*tmp;
	int		i;

	if (!av[0] || !av[1])
		return (av);
	i = 0;
	while (av[i + 1])
	{
		if (ft_strcmp(av[i], av[i + 1]) > 0)
		{
			tmp = av[i];
			av[i] = av[i + 1];
			av[i + 1] = tmp;
			i = -1;
		}
		i++;
	}
	return (av);
}

static t_ls_lst	*ft_ls_begin(t_ls_lst *begin, int file)
{
	t_ls_lst	*tmp;

	if (file)
	{
		tmp = begin->next;
		ft_strdel(&begin->path);
		ft_memdel((void**)&begin);
		begin = tmp;
	}
	return (begin);
}

t_ls_lst		*ft_ls_arg_file(char **av, int st)
{
	t_ls_lst	*begin;
	t_ls_lst	*list;
	struct stat	tmp_stat;
	int			files;

	av = ft_ls_arg_sort(av);
	if (stat(".", &tmp_stat) < 0)
		ft_ls_error(".");
	if (!(begin = ft_ls_list_new(".", &tmp_stat)))
		return (NULL);
	list = begin;
	files = 0;
	while (*av)
	{
		if ((st ? lstat(*av, &tmp_stat) < 0 : stat(*av, &tmp_stat) < 0))
			ft_ls_error(*av);
		else if ((list->next = ft_ls_list_new(*av, &tmp_stat)))
			list = list->next;
		av++;
		files++;
	}
	return (ft_ls_begin(begin, files));
}

t_ls_lst		*ft_ls_arg_reg(t_ls_lst **file, int *format, char *opt)
{
	t_ls_lst	*reg;
	t_ls_lst	*prev;
	t_ls_lst	*cur;

	reg = NULL;
	prev = NULL;
	cur = *file;
	while (cur)
	{
		if (!S_ISDIR(cur->s_stat.st_mode) || ft_strchr(opt, 'd'))
		{
			if (!prev)
				*file = cur->next;
			else
				prev->next = cur->next;
			reg = ft_ls_reg_add(reg, cur, opt, format);
			cur = prev ? prev->next : *file;
		}
		else
		{
			prev = cur;
			cur = cur->next;
		}
	}
	return (reg);
}
