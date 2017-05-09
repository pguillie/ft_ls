/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_format.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/19 16:37:47 by pguillie          #+#    #+#             */
/*   Updated: 2017/03/29 10:37:02 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_ls_init_format(int *format)
{
	int		i;

	i = 0;
	while (i < FORMAT_SIZE)
		format[i++] = 0;
}

void	ft_ls_update_format(int *format, struct stat st, char *name)
{
	format[0] += st.st_blocks;
	if (ft_intlen(st.st_blocks) > format[1])
		format[1] = ft_intlen(st.st_blocks);
	if ((int)ft_strlen(name) > format[2])
		format[2] = ft_strlen(name);
	if (ft_intlen(st.st_nlink) > format[3])
		format[3] = ft_intlen(st.st_nlink);
	if ((int)ft_strlen(getpwuid(st.st_uid)->pw_name) > format[4])
		format[4] = ft_strlen(getpwuid(st.st_uid)->pw_name);
	if ((int)ft_strlen(getgrgid(st.st_gid)->gr_name) > format[5])
		format[5] = ft_strlen(getgrgid(st.st_gid)->gr_name);
	if (S_ISCHR(st.st_mode) || S_ISBLK(st.st_mode))
		format[6] < 8 ? format[6] = 8 : 0;
	else if (ft_intlen(st.st_size) > format[6])
		format[6] = ft_intlen(st.st_size);
}
