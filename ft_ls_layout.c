/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_layout.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/21 17:23:07 by pguillie          #+#    #+#             */
/*   Updated: 2017/03/29 10:19:31 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	ft_ls_fill(char *name, int *size, int prev_len, int next)
{
	struct winsize	win;

	ioctl(0, TIOCGSIZE, &win);
	if (!next || prev_len + (size[0] + size[1]) * 2 >= win.ws_col)
	{
		ft_putchar('\n');
		prev_len = 0;
	}
	else
	{
		ft_ls_disp_str("", size[0] - ft_strlen(name));
		prev_len += size[0] + size[1] + 1;
	}
	return (prev_len);
}

int			ft_ls_layout(char *name, char *opt, int *format, int *sum)
{
	int		size[2];

	size[0] = format[2];
	size[1] = ft_strchr(opt, 's') ? format[1] + 1 : 0;
	if (ft_ls_srch_opt(opt, 3, 'l', 'g', '1'))
		ft_putchar('\n');
	else
		sum[0] = ft_ls_fill(name, size, sum[0], sum[1]);
	return (sum[0]);
}
