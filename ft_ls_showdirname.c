/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_showdirname.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 11:34:49 by pguillie          #+#    #+#             */
/*   Updated: 2017/03/22 23:28:50 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_ls_showdirname(t_ls_lst *file, char **av)
{
	char	*name;
	int		i[2];

	i[0] = 0;
	i[1] = 0;
	if (file)
		name = file->path;
	while (file)
	{
		file = file->next;
		i[0]++;
	}
	while (av[i[1]])
		i[1]++;
	if (i[0] && (i[0] > 1 || i[0] < i[1]))
	{
		if (i[1] > i[0])
			ft_putchar('\n');
		ft_printf("%s:\n", name);
	}
}
