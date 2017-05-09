/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_disp_fields.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 15:59:22 by pguillie          #+#    #+#             */
/*   Updated: 2017/03/29 09:59:34 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_ls_disp_nb(int nb, int size)
{
	size -= ft_intlen(nb);
	while (size > 0)
	{
		write(1, SPACE, (size > 10 ? 10 : size));
		size -= 10;
	}
	ft_putnbr(nb);
}

void	ft_ls_disp_str(char *str, int size)
{
	size -= ft_strlen(str);
	ft_putchar(' ');
	ft_putstr(str);
	while (size > 0)
	{
		write(1, SPACE, (size > 10 ? 10 : size));
		size -= 10;
	}
}

void	ft_ls_disp_date(struct stat info, char *u)
{
	time_t	now;
	time_t	file_time;
	char	*date;

	now = time(NULL);
	date = u ? ctime(&info.st_atime) + 4 : ctime(&info.st_mtime) + 4;
	file_time = u ? info.st_atime : info.st_mtime;
	if (now - file_time > 6 * 31 * 24 * 3600
			|| file_time - now > 6 * 31 * 24 * 3600)
		ft_memmove(date + 7, date + 15, 5);
	ft_printf(" %.12s ", date);
}
