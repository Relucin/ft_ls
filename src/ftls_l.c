/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftls_l.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmontoya <bmontoya@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/10 14:54:00 by bmontoya          #+#    #+#             */
/*   Updated: 2017/05/22 16:41:43 by bmontoya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ftls.h>
#include <sys/syslimits.h>
#include <ftstring.h>
#include <ftstdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include <unistd.h>
#include <uuid/uuid.h>
#define FTLS_ISCHR(file) ((file->stat->st_mode & S_IFMT) == S_IFCHR)
#define FTLS_ISBLK(file) ((file->stat->st_mode & S_IFMT) == S_IFBLK)

int		g_ftls_lnklen = 0;
int		g_ftls_owrlen = 0;
int		g_ftls_grplen = 0;
int		g_ftls_bytes = 0;
int		g_ftls_major = 0;
int		g_ftls_minor = 0;

char	ftls_fmode(int type)
{
	if (type == S_IFBLK)
		return ('b');
	else if (type == S_IFCHR)
		return ('c');
	else if (type == S_IFDIR)
		return ('d');
	else if (type == S_IFLNK)
		return ('l');
	else if (type == S_IFIFO)
		return ('p');
	else if (type == S_IFSOCK)
		return ('s');
	else
		return ('-');
}

void	ftls_rwx(t_ftls *ftls, char *rights)
{
	rights[0] = (ftls->stat->st_mode & S_IRUSR) ? 'r' : '-';
	rights[1] = (ftls->stat->st_mode & S_IWUSR) ? 'w' : '-';
	if (ftls->stat->st_mode & S_ISUID)
		rights[2] = (ftls->stat->st_mode & S_IXUSR) ? 's' : 'S';
	else
		rights[2] = (ftls->stat->st_mode & S_IXUSR) ? 'x' : '-';
	rights[3] = (ftls->stat->st_mode & S_IRGRP) ? 'r' : '-';
	rights[4] = (ftls->stat->st_mode & S_IWGRP) ? 'w' : '-';
	if (ftls->stat->st_mode & S_ISGID)
		rights[5] = (ftls->stat->st_mode & S_IXGRP) ? 's' : 'S';
	else
		rights[5] = (ftls->stat->st_mode & S_IXGRP) ? 'x' : '-';
	rights[6] = (ftls->stat->st_mode & S_IROTH) ? 'r' : '-';
	rights[7] = (ftls->stat->st_mode & S_IWOTH) ? 'w' : '-';
	if (ftls->stat->st_mode & S_ISVTX)
		rights[8] = (ftls->stat->st_mode & S_IXOTH) ? 't' : 'T';
	else
		rights[8] = (ftls->stat->st_mode & S_IXOTH) ? 'x' : '-';
	rights[9] = ' ';
	rights[10] = '\0';
}

void	ftls_time(t_ftls *ftls)
{
	char	**tstr;
	time_t	tloc;

	tstr = ft_strsplit(ctime(&ftls->stat->st_mtimespec.tv_sec), ' ');
	time(&tloc);
	tloc -= ftls->stat->st_mtimespec.tv_sec;
	tloc *= (tloc < 0) ? -1 : 1;
	tstr[4][4] = '\0';
	ft_printf("%s %2s %5.5s ", tstr[1], tstr[2],
	(tloc >= 15780000) ? tstr[4] :
						tstr[3]);
	free(tstr[0]);
	free(tstr[1]);
	free(tstr[2]);
	free(tstr[3]);
	free(tstr[4]);
	free(tstr);
}

void	ftls_pl(t_ftls *ftls)
{
	char			rights[PATH_MAX];
	struct passwd	*ptmp;
	struct group	*gtmp;

	ftls_rwx(ftls, rights);
	ptmp = getpwuid(ftls->stat->st_uid);
	gtmp = getgrgid(ftls->stat->st_gid);
	ft_printf("%c%s %*d %-*s  %-*s  ",
	ftls_fmode(ftls->stat->st_mode & S_IFMT), rights, g_ftls_lnklen,
	ftls->stat->st_nlink, g_ftls_owrlen, (ptmp) ? ptmp->pw_name : "",
	g_ftls_grplen, (gtmp) ? gtmp->gr_name : "");
	if ((FTLS_ISCHR(ftls)) || (FTLS_ISBLK(ftls)))
		ft_printf("%*ld, %*ld ", g_ftls_major, (long)major(ftls->stat->st_rdev),
		g_ftls_minor, (long)minor(ftls->stat->st_rdev));
	else
		ft_printf("%*lld ", g_ftls_bytes + ((g_ftls_major) ?
		g_ftls_major + g_ftls_minor : 0), ftls->stat->st_size);
	ftls_time(ftls);
	if ((ftls->stat->st_mode & S_IFMT) == S_IFLNK)
	{
		rights[readlink(ftls->fname, rights, PATH_MAX)] = '\0';
		ft_printf("%s -> %s\n", ftls->name, rights);
	}
	else
		ft_printf("%s\n", ftls->name);
}

int		ft_strnbrlen(long long nbr, int base)
{
	int len;

	len = (nbr < 0) ? 2 : 1;
	while ((nbr /= base))
		++len;
	return (len);
}

void	ftls_maxset(t_ftls *ftls)
{
	int				size;

	g_ftls_blocks += ftls->stat->st_blocks;
	size = ft_strnbrlen(ftls->stat->st_nlink, 10);
	if (size > g_ftls_lnklen)
		g_ftls_lnklen = size;
	if ((FTLS_ISCHR(ftls)) || (FTLS_ISBLK(ftls)))
	{
		size = ft_strnbrlen(major(ftls->stat->st_rdev), 10);
		if (size > g_ftls_major)
			g_ftls_major = size;
		size = ft_strnbrlen(minor(ftls->stat->st_rdev), 10);
		if (size > g_ftls_minor)
			g_ftls_minor = size;
	}
	size = ft_strlen(getpwuid(ftls->stat->st_uid)->pw_name);
	if (size > g_ftls_owrlen)
		g_ftls_owrlen = size;
	size = ft_strlen(getgrgid(ftls->stat->st_gid)->gr_name);
	if (size > g_ftls_grplen)
		g_ftls_grplen = size;
	size = ft_strnbrlen(ftls->stat->st_size, 10);
	if (size > g_ftls_bytes)
		g_ftls_bytes = size;
}
