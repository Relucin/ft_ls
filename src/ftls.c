/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftls.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmontoya <bmontoya@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/17 12:18:40 by bmontoya          #+#    #+#             */
/*   Updated: 2017/05/23 15:27:37 by bmontoya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ftls.h>
#include <stdbool.h>
#include <ftstdio.h>
#include <ftstring.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <dstruct/ftbtree.h>
#define FTLS_HIDDEN(str) (ft_strcmp(str, ".") && ft_strcmp(str, ".."))
#define FTLS_ATEST(str) (g_ftls_flags & a) ? FTLS_HIDDEN(str) : true
#define FTLS_FLAG(TYPE) (g_ftls_flags & TYPE)
#define FTLS_ISDIR(file) ((file->stat->st_mode & S_IFMT) == S_IFDIR)

int		g_ftls_blocks = 0;
int		(*g_sort)() = 0;
int		g_ftls_flags = 0;
t_btree	*g_ftls_ctree = 0;
t_btree	*g_ftls_dtree = 0;
t_btree	*g_ftls_ntree = 0;
int		g_ftls_print = 0;

bool	ftls_option(const char *option)
{
	const char	*opts = "Radlrt1";
	char		*tmp;

	if (!ft_strcmp(option, "--"))
		return (false);
	while (*++option)
	{
		if ((tmp = ft_strchr(opts, *option)))
		{
			if (*option == '1')
			{
				if (g_ftls_flags & l)
					g_ftls_flags ^= l;
				continue ;
			}
			g_ftls_flags |= 1 << (tmp - opts);
		}
		else
		{
			ft_dprintf(2, "ls: illegal option -- %c\n", *option);
			ft_dprintf(2, "usage: ls: [-%s] [file ...]\n", opts);
			exit(EXIT_FAILURE);
		}
	}
	return (true);
}

void	ftls_initdir(const char *dir)
{
	t_ftls		*data;

	data = malloc(sizeof(t_ftls));
	data->name = ft_strdup(dir);
	data->fname = ft_strdup(dir);
	data->stat = malloc(sizeof(struct stat));
	if (g_ftls_flags & l)
		data->err = lstat(dir, data->stat);
	else
	{
		if ((data->err = stat(dir, data->stat)))
			data->err = lstat(dir, data->stat);
	}
	if (data->err)
		ft_btreeadd(&g_ftls_ntree, data, &ftls_sort);
	else if ((data->stat->st_mode & S_IFMT) == S_IFDIR && !(g_ftls_flags & d))
	{
		data->dp = opendir(dir);
		ft_btreeadd(&g_ftls_dtree, data, g_sort);
	}
	else
		ft_btreeadd(&g_ftls_ctree, data, g_sort);
}

void	ftls_add_file(const char *name, const char *path, t_btree **dir)
{
	t_ftls	*file;

	file = malloc(sizeof(t_ftls));
	file->name = ft_strdup(name);
	file->stat = 0;
	file->fname = 0;
	file->err = 0;
	if (g_ftls_flags & (R | t | l))
	{
		file->stat = malloc(sizeof(struct stat));
		ft_asprintf(&(file->fname), "%s%s%s", path,
		(!ft_strcmp("/", path)) ? "" : "/", name);
		file->err = lstat(file->fname, file->stat);
		if (g_ftls_flags & l && !file->err)
			ftls_maxset(file);
	}
	if ((FTLS_FLAG(R)) && (FTLS_ISDIR(file)) && (FTLS_ATEST(file->name)))
	{
		file->dp = opendir(file->fname);
		ft_btreeadd(dir, file, g_sort);
	}
	else
		file->dp = 0;
	ft_btreeadd(&g_ftls_ctree, file, g_sort);
}

void	ftls(void)
{
	ft_btreeiof(g_ftls_ntree, &ftls_fdne);
	ft_btreeiof(g_ftls_ctree, &ftls_print_file);
	ftls_clear_globals();
	if (g_ftls_ctree)
	{
		g_ftls_ctree = 0;
		g_ftls_print = 2;
	}
	else if (g_ftls_ntree ||
		(g_ftls_dtree && (g_ftls_dtree->lnode || g_ftls_dtree->rnode)))
		g_ftls_print = 1;
	while (g_ftls_dtree)
		ftls_readtree((t_ftls *)ft_btreermmin(&g_ftls_dtree));
}

int		main(int argc, const char **argv)
{
	while (--argc > 0 && **++argv == '-')
	{
		if (!ft_strcmp(*argv, "-"))
			break ;
		else if (!ftls_option(*argv))
		{
			++argv;
			--argc;
			break ;
		}
	}
	ftls_select_sort();
	while (argc--)
		ftls_initdir(*argv++);
	if (!g_ftls_dtree && !g_ftls_ctree && !g_ftls_ntree)
		ftls_initdir(".");
	ftls();
	return (0);
}
