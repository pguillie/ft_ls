/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_srch_opt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 10:24:14 by pguillie          #+#    #+#             */
/*   Updated: 2017/04/05 15:39:41 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	ft_ls_opt_ret(int *res, int size)
{
	int		i;

	i = 0;
	while (i < size)
	{
		if (res[i++])
			return (1);
	}
	return (0);
}

int			ft_ls_srch_opt(char *opt, int nb, ...)
{
	va_list		ap;
	char		c;
	int			i[2];
	int			res[nb];

	va_start(ap, nb);
	i[1] = 0;
	while (nb--)
	{
		c = (char)va_arg(ap, int);
		i[0] = ft_strlen(opt);
		res[i[1]] = 0;
		while (i[0]-- && res[i[1]] == 0)
		{
			if ((c == '1' && (opt[i[0]] == 'l' || opt[i[0]] == 'g'))
					|| ((c == 'l' || c == 'g') && opt[i[0]] == '1'))
				i[0] = 0;
			else if (opt[i[0]] == c)
				res[i[1]] = 1;
		}
		i[1]++;
	}
	va_end(ap);
	return (ft_ls_opt_ret(res, i[1]));
}
