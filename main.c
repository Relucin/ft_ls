/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmontoya <bmontoya@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/20 03:40:24 by bmontoya          #+#    #+#             */
/*   Updated: 2017/04/26 15:56:31 by bmontoya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** For opendir / readdir
*/
#include <dirent.h>

/*
** For stat / lstat (2)
*/
#include <sys/stat.h>

/*
** For getpwuid
*/
#include <sys/types.h>
#include <pwd.h>
#include <uuid/uuid.h>

/*
** For getgrgid
*/
#include <grp.h>

/*
** For listxattr / getxattr (2)
*/
#include <sys/xattr.h>

/*
** For time / ctime
*/
#include <time.h>

/*
** For readlink
*/
#include <unistd.h>

/*
** For malloc / free / exit
*/
#include <stdlib.h>

/*
** For perror
*/
#include <stdio.h>

/*
** For strerror
*/
#include <string.h>

#include "libft.h"

enum	e_ftls_flags
{
	l = 1,
	R = 2,
	a = 4,
	r = 8,
	t = 16
};

uint8_t	g_ftls_flags = 0;
char	*g_ftls_curpath = 0;
unsigned long g_ftls_dirs = 0;

typedef struct		s_btree
{
	struct s_btree	*parent;
	struct s_btree	*rnode;
	struct s_btree	*lnode;
	void			*content;
}					t_btree;

int		ftls_btstrcmp(void *s1, void *s2)
{
	if (g_ftls_flags & r)
		return (ft_strcmp((char *)s2, (char *)s1));
	return (ft_strcmp((char *)s1, (char *)s2));
}

t_btree		*ft_btreenew(void *content)
{
	t_btree *head;

	head = malloc(sizeof(t_btree));
	head->parent = 0;
	head->rnode = 0;
	head->lnode = 0;
	head->content = content;
	return (head);
}

void		ft_btreeadd(t_btree **head, void *content, int (*f)(void *, void *))
{
	t_btree	**tmp;

	if (!*head)
		*head = ft_btreenew(content);
	else
	{
		while (1)
		{
			if (f(content, (*head)->content) < 0)
				tmp = &((*head)->lnode);
			else
				tmp = &((*head)->rnode);
			if (!*tmp)
			{
				*tmp = ft_btreenew(content);
				(*tmp)->parent = *head;
				break ;
			}
			head = tmp;
		}
	}
}

char	*ftls_makerelpath(const char *parent, const char *child)
{
	char	*fpath;

	fpath = malloc(ft_strlen(parent) + ft_strlen(child) + 2);
	fpath[0] = '\0';
	ft_strcat(fpath, parent);
	ft_strcat(fpath, "/");
	ft_strcat(fpath, child);
	return (fpath);
}

void	ftls_pfile(int ftype)
{
	if (ftype == S_IFIFO)
		printf("p");
	else if (ftype == S_IFCHR)
		printf("c");
	else if (ftype == S_IFDIR)
		printf("d");
	else if (ftype == S_IFBLK)
		printf("b");
	else if (ftype == S_IFREG)
		printf("-");
	else if (ftype == S_IFLNK)
		printf("l");
	else
		printf("s");
}

void	ftls_ogofile(int mode)
{
	int	mmask;

	mmask = mode & S_IRWXU;
	printf("%c%c%c", (mmask & S_IRUSR) ? 'r' : '-',
					(mmask & S_IWUSR) ? 'w' : '-',
					(mmask & S_IXUSR) ? 'x' : '-');
	mmask = mode & S_IRWXG;
	printf("%c%c%c", (mmask & S_IRGRP) ? 'r' : '-',
					(mmask & S_IWGRP) ? 'w' : '-',
					(mmask & S_IXGRP) ? 'x' : '-');
	mmask = mode & S_IRWXO;
	printf("%c%c%c ", (mmask & S_IROTH) ? 'r' : '-',
					(mmask & S_IWOTH) ? 'w' : '-',
					(mmask & S_IXOTH) ? 'x' : '-');
}

void	ftls_tfile(time_t ts)
{
	char	*tstr;
	char	**tstrs;

	tstr = ctime(&ts);
	tstrs = ft_strsplit(tstr, ' ');
	printf(" %s %s %.5s", tstrs[1], tstrs[2], tstrs[3]);
	free(tstrs);
}

void	ftls_lsprint(const char *f_name)
{
	struct stat			buf;
	char				*tpath;
	int					i;

	i = 0;
	if (g_ftls_flags & l)
	{
		tpath = ftls_makerelpath(g_ftls_curpath, f_name);
		lstat(tpath, &buf);
		ftls_pfile(buf.st_mode & S_IFMT);
		ftls_ogofile(buf.st_mode);
		printf(" %d", buf.st_nlink);
		printf(" %s", getpwuid(buf.st_uid)->pw_name);
		printf(" %s", getgrgid(buf.st_gid)->gr_name);
		printf(" %lld", buf.st_size);
		ftls_tfile(buf.st_mtimespec.tv_sec);
		printf(" %s\n", f_name);
	}
	else
		printf("%s\n", f_name);
}

void	ftls_btioprint(t_btree *tree)
{
	if (tree)
	{
		ftls_btioprint(tree->lnode);
		free(tree->lnode);
		ftls_lsprint(tree->content);
		free(tree->content);
		ftls_btioprint(tree->rnode);
		free(tree->rnode);
	}
}

void	ftls_print(t_btree **dhead)
{
	//TODO Handle errors elsewhere
	DIR				*dp;
	struct dirent	*sdp;
	struct stat		buf;
	t_btree			*files;
	char			*tpath;

	dp = opendir(g_ftls_curpath);
	files = 0;
	if (dp)
	{
		while ((sdp = readdir(dp)) != NULL)
			if (sdp->d_name[0] != '.' || g_ftls_flags & a)
			{
				ft_btreeadd(&files, ft_strdup(sdp->d_name), &ftls_btstrcmp);
				if ((g_ftls_flags & R) && ft_strcmp(sdp->d_name, ".") && ft_strcmp(sdp->d_name, ".."))
				{
					tpath = ftls_makerelpath(g_ftls_curpath, sdp->d_name);
					lstat(tpath, &buf);
					if ((buf.st_mode & S_IFMT) == S_IFDIR)
					{
						ft_btreeadd(dhead, tpath, &ftls_btstrcmp);
						++g_ftls_dirs;
					}
					else
						free(tpath);
				}
			}
		ftls_btioprint(files);
		free(files);
		closedir(dp);
	}
	else if (!stat(g_ftls_curpath, &buf))
	{
		if (buf.st_mode & S_IFDIR)
			printf("ft_ls: %s: Permission denied\n", g_ftls_curpath);
		else
			printf("%s\n", g_ftls_curpath);
	}
	else
		printf("ft_ls: %s: No such file or directory\n", g_ftls_curpath);
}

int		ftls_readoptions(t_btree **dir, const char *option)
{
	const static char	*opts = "lRart";
	int					i;

	if (*option == '-')
	{
		while (*++option)
		{
			i = 0;
			while (opts[i] && *option != opts[i])
				i++;
			if (opts[i])
				g_ftls_flags |= 1 << i;
			else
			{
				printf("ft_ls: illegal option -- %c\n", *option);
				printf("usage: ft_ls [%s] [file ...]\n", opts);
				return (0);
			}
		}
	}
	else
	{
		ft_btreeadd(dir, ft_strdup(option), &ftls_btstrcmp);
		++g_ftls_dirs;
	}
	return (1);
}

void	ftls_btioread(t_btree **dirs)
{
	static unsigned long n_dirs = 0;

	if (*dirs)
	{
		ftls_btioread(&(*dirs)->lnode);
		free((*dirs)->lnode);
		if (n_dirs)
			printf("%s:\n", (*dirs)->content);
		g_ftls_curpath = (*dirs)->content;
		ftls_print(&(*dirs));
		++n_dirs;
		if (n_dirs != g_ftls_dirs)
			printf("\n");
		free((*dirs)->content);
		ftls_btioread(&(*dirs)->rnode);
		free((*dirs)->rnode);
	}
}

int		main(int argc, const char **argv)
{
	int		i;
	t_btree	*dirs;

	dirs = 0;
	if (argc != 1)
	{
		i = 1;
		while (i < argc)
			if (!ftls_readoptions(&dirs, argv[i++]))
				return (-1);
	}
	if (!dirs)
	{
		ft_btreeadd(&dirs, ft_strdup("."), &ftls_btstrcmp);
		++g_ftls_dirs;
	}
	ftls_btioread(&dirs);
	free(dirs);
	// while (1);
	return (1);
}
