/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_arg_opt.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/18 11:40:38 by pguillie          #+#    #+#             */
/*   Updated: 2017/03/29 11:12:16 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	ft_ls_illegal_opt(char c)
{
	ft_printf("ft_ls: illegal option -- %c\n", c);
	ft_printf("usage: ft_ls [-%s] [file ...]\n", OPTIONS);
}

static char	*ft_ls_valid(char *opt)
{
	int		i;

	i = 0;
	while (opt[i])
	{
		if (!ft_strchr(OPTIONS, opt[i]))
		{
			ft_ls_illegal_opt(opt[i]);
			ft_strdel(&opt);
			exit(EXIT_FAILURE);
		}
		i++;
	}
	return (opt);
}

char		*ft_ls_arg_opt(char ***av)
{
	char	*opt;
	int		i;

	if (!(opt = ft_strnew(MAX_OPT)))
	{
		perror(NULL);
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (*++*av && (**av)[0] == '-' && (**av)[1] && ft_strcmp(**av, "--"))
	{
		while (*(++**av))
		{
			if (i < MAX_OPT)
				opt[i++] = ***av;
		}
	}
	if (ft_strequ(**av, "--"))
		(*av)++;
	return (ft_ls_valid(opt));
}
