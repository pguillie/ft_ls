/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/18 11:23:49 by pguillie          #+#    #+#             */
/*   Updated: 2017/04/05 12:35:45 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		main(int ac, char **av)
{
	t_ls_lst	*file;
	t_ls_lst	*reg;
	char		*opt;
	int			format[FORMAT_SIZE];

	opt = ft_ls_arg_opt(&av);
	file = ft_ls_arg_file(av, (ft_ls_srch_opt(opt, 2, 'l', 'g')
				|| (ft_strchr(opt, 's') && ft_strchr(opt, 'd'))));
	ft_ls_init_format(format);
	reg = ft_ls_arg_reg(&file, format, opt);
	if (reg)
		ft_ls_disp_beg(reg, opt, format);
	ft_ls_showdirname(file, av);
	while (file)
	{
		if (!ac)
			ft_printf("\n%s:\n", file->path);
		ft_ls_open_file(file->path, opt);
		file = ft_ls_clean_one(file);
		ac = 0;
	}
	ft_strdel(&opt);
	return (0);
}
