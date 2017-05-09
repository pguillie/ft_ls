/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_disp_filetype.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/05 14:26:46 by pguillie          #+#    #+#             */
/*   Updated: 2017/04/05 15:48:12 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_ls_disp_color(struct stat st)
{
	if ((S_ISVTX & st.st_mode) && (S_IWOTH & st.st_mode)
			&& (S_IXOTH & st.st_mode))
		ft_putstr("\033[42;30m");
	else if (S_ISDIR(st.st_mode) && S_IRUSR & st.st_mode && S_IWUSR & st.st_mode
	&& S_IXUSR & st.st_mode && S_IRGRP & st.st_mode && S_IWGRP & st.st_mode
	&& S_IXGRP & st.st_mode && S_IROTH & st.st_mode && S_IWOTH & st.st_mode
	&& S_IXOTH & st.st_mode)
		ft_putstr("\033[43;30m");
	else if (S_ISDIR(st.st_mode))
		ft_putstr("\033[34;01m");
	else if (S_ISBLK(st.st_mode))
		ft_putstr("\033[46;34m");
	else if (S_ISCHR(st.st_mode))
		ft_putstr("\033[43;34m");
	else if (S_ISLNK(st.st_mode))
		ft_putstr("\033[35m");
	else if (S_ISFIFO(st.st_mode))
		ft_putstr("\033[33m");
	else if (S_ISSOCK(st.st_mode))
		ft_putstr("\033[36m");
	else if (S_IXUSR & st.st_mode || S_IXGRP & st.st_mode
			|| S_IXOTH & st.st_mode)
		ft_putstr("\033[32m");
}

void	ft_ls_disp_tag(struct stat st)
{
	if (S_ISDIR(st.st_mode))
		ft_putchar('/');
	else if (S_ISLNK(st.st_mode))
		ft_putchar('@');
	else if (S_ISSOCK(st.st_mode))
		ft_putchar('=');
	else if (S_ISWHT(st.st_mode))
		ft_putchar('%');
	else if (S_ISFIFO(st.st_mode))
		ft_putchar('|');
	else if (S_IXUSR & st.st_mode || S_IXGRP & st.st_mode
			|| S_IXOTH & st.st_mode)
		ft_putchar('*');
}
