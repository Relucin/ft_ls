/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftls.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmontoya <bmontoya@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/28 16:35:51 by bmontoya          #+#    #+#             */
/*   Updated: 2017/05/22 20:03:47 by bmontoya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FTLS_H
# define FTLS_H
# include <dirent.h>
# include <sys/stat.h>

typedef struct		s_ftls
{
	char			*name;
	char			*fname;
	struct stat		*stat;
	int				err;
	DIR				*dp;
}					t_ftls;

enum	e_ftls_flags
{
	R = 1,
	a = 2,
	d = 4,
	l = 8,
	r = 16,
	t = 32
};
extern int			g_ftls_blocks;
extern int			g_ftls_lnklen;
extern int			g_ftls_owrlen;
extern int			g_ftls_grplen;
extern int			g_ftls_bytes;
extern int			g_ftls_major;
extern int			g_ftls_minor;

void				ftls_pl(t_ftls *ftls);
void				ftls_maxset(t_ftls *ftls);
char				ftls_fmode(int type);
void				ftls_rwx(t_ftls *ftls, char *rights);
void				ftls_time(t_ftls *ftls);

int					ftls_sort(t_ftls *d1, t_ftls *d2);
int					ftls_rsort(t_ftls *d1, t_ftls *d2);
int					ftls_rtsort(t_ftls *d1, t_ftls *d2);
int					ftls_tsort(t_ftls *d1, t_ftls *d2);
#endif
