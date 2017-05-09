/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/18 11:25:27 by pguillie          #+#    #+#             */
/*   Updated: 2017/04/07 18:12:06 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <sys/ioctl.h>
# include <sys/types.h>
# include <sys/acl.h>
# include <sys/stat.h>
# include <sys/xattr.h>
# include <dirent.h>
# include <grp.h>
# include <pwd.h>
# include "../../libft/includes/libft.h"

/*
** DEFINE
*/

# define MAX_OPT 64
# define OPTIONS "FGRSadglrstu1"
# define FORMAT_SIZE 7
# define LINK_BUFFSIZE 512
# define SPACE "          "

/*
** STRUCTURE
*/

typedef struct		s_ls_lst
{
	char			*path;
	struct stat		s_stat;
	struct s_ls_lst	*next;
}					t_ls_lst;

/*
** MAIN
*/

char				*ft_ls_arg_opt(char ***av);
int					ft_ls_srch_opt(char *opt, int nb, ...);
t_ls_lst			*ft_ls_arg_file(char **av, int l);
t_ls_lst			*ft_ls_arg_reg(t_ls_lst **file, int *format, char *opt);
void				ft_ls_showdirname(t_ls_lst *file, char **av);
void				ft_ls_open_file(char *path, char *opt);
void				ft_ls_error(char *str);

/*
** LIST
*/

t_ls_lst			*ft_ls_list_new(char *name, struct stat *stat_addr);
t_ls_lst			*ft_ls_add(t_ls_lst *begin, char *nm, char *opt, int *fmt);
t_ls_lst			*ft_ls_reg_add(t_ls_lst *b, t_ls_lst *n, char *o, int *f);
t_ls_lst			*ft_ls_clean_one(t_ls_lst *list);
t_ls_lst			*ft_ls_clean(t_ls_lst *list);
char				*ft_ls_pathname(char *path, char *name);

/*
** SORT
*/

int					ft_ls_cmp_name(t_ls_lst *a, t_ls_lst *b);
int					ft_ls_cmp_mtime(t_ls_lst *a, t_ls_lst *b);
int					ft_ls_cmp_atime(t_ls_lst *a, t_ls_lst *b);
int					ft_ls_cmp_size(t_ls_lst *a, t_ls_lst *b);

/*
** STAT
*/

struct stat			*ft_ls_stat(char *name, char *opt);
void				ft_ls_init_format(int *format);
void				ft_ls_update_format(int *format, struct stat s, char *name);

/*
** DISPLAY
*/

void				ft_ls_display(t_ls_lst *file, char *opt, int *format);
void				ft_ls_disp_beg(t_ls_lst *file, char *opt, int *format);
void				ft_ls_disp_color(struct stat st);
void				ft_ls_disp_tag(struct stat st);
void				ft_ls_disp_nb(int nb, int size);
void				ft_ls_disp_str(char *str, int size);
void				ft_ls_disp_mode(struct stat info);
void				ft_ls_disp_date(struct stat info, char *u);
int					ft_ls_layout(char *name, char *opt, int *form, int *sum);

#endif
