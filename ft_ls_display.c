/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_display.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/11 17:11:37 by pguillie          #+#    #+#             */
/*   Updated: 2017/04/05 15:48:23 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	ft_ls_disp_long(char *name, struct stat st, int *format, char *opt)
{
	acl_t	acl;

	ft_ls_disp_mode(st);
	acl = acl_get_file(name, ACL_TYPE_EXTENDED);
	if (listxattr(name, NULL, 0, XATTR_NOFOLLOW) > 0)
		ft_putchar('@');
	else if (acl)
		ft_putchar('+');
	else
		ft_putchar(' ');
	acl_free((void*)acl);
	ft_ls_disp_nb(st.st_nlink, format[3] + 1);
	if (!ft_strchr(opt, 'g'))
		ft_ls_disp_str(getpwuid(st.st_uid)->pw_name, format[4] + 1);
	ft_ls_disp_str(getgrgid(st.st_gid)->gr_name, format[5] + 1);
	if (S_ISCHR(st.st_mode) || S_ISBLK(st.st_mode))
	{
		ft_ls_disp_nb(major(st.st_rdev), format[6] - 5 + 1);
		ft_putchar(',');
		ft_ls_disp_nb(minor(st.st_rdev), 4);
	}
	else
		ft_ls_disp_nb(st.st_size, format[6] + 1);
	ft_ls_disp_date(st, ft_strchr(opt, 'u'));
}

static void	ft_ls_disp_opt(t_ls_lst *file, char *opt, int *format)
{
	if (ft_strchr(opt, 's'))
	{
		ft_ls_disp_nb(file->s_stat.st_blocks, format[1]);
		ft_putchar(' ');
	}
	if (ft_ls_srch_opt(opt, 2, 'l', 'g'))
		ft_ls_disp_long(file->path, file->s_stat, format, opt);
	if (ft_strchr(opt, 'G'))
		ft_ls_disp_color(file->s_stat);
}

static void	ft_ls_disp_link(t_ls_lst *file, char *opt)
{
	char	link[LINK_BUFFSIZE];

	if (ft_ls_srch_opt(opt, 2, 'l', 'g')
			&& S_ISLNK(file->s_stat.st_mode))
	{
		ft_memset(link, 0, LINK_BUFFSIZE);
		readlink(file->path, link, LINK_BUFFSIZE);
		ft_printf(" -> %s", link);
	}
}

void		ft_ls_display(t_ls_lst *file, char *opt, int *format)
{
	char	*name;
	int		sum[2];

	sum[0] = 0;
	while (file)
	{
		name = ft_strrchr(file->path, '/');
		name = (name ? name + 1 : file->path);
		if (name[0] != '.' || ft_strchr(opt, 'a'))
		{
			ft_ls_disp_opt(file, opt, format);
			ft_printf("%s{eoc}", name);
			ft_strchr(opt, 'F') ? ft_ls_disp_tag(file->s_stat) : 0;
			ft_ls_disp_link(file, opt);
			sum[1] = file->next ? 1 : 0;
			sum[0] = ft_ls_layout(name, opt, format, sum);
		}
		file = file->next;
	}
}

void		ft_ls_disp_beg(t_ls_lst *file, char *opt, int *format)
{
	int		sum[2];

	sum[0] = 0;
	while (file)
	{
		ft_ls_disp_opt(file, opt, format);
		ft_printf("%s{eoc}", file->path);
		ft_strchr(opt, 'F') ? ft_ls_disp_tag(file->s_stat) : 0;
		ft_ls_disp_link(file, opt);
		sum[1] = file->next ? 1 : 0;
		sum[0] = ft_ls_layout(file->path, opt, format, sum);
		file = ft_ls_clean_one(file);
	}
}
