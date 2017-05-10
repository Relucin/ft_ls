/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmontoya <bmontoya@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 14:20:41 by bmontoya          #+#    #+#             */
/*   Updated: 2017/05/09 17:32:56 by bmontoya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftls.h"

int		g_ftls_flags = 0;
t_btree	*g_ftls_dtree = 0;
t_btree *g_ftls_ctree = 0;
t_btree	*g_ftls_ntree = 0;
int		(*g_sort)(void *, void *) = 0;
bool	g_ftls_print = false;

bool	ftls_option(const char *option)
{
	const char	*opts = "Ralrt";
	char		*tmp;

	if (!ft_strcmp(option, "--"))
		return (false);
	while (*++option)
	{
		if ((tmp = ft_strchr(opts, *option)))
			g_ftls_flags |= 1 << (tmp - opts);
		else if (*option == '1')
			continue ;
		else
		{
			printf("ft_ls: illegal option -- %c\n", *option);
			printf("ft_ls: [-%s] [file ...]\n", opts);
			exit(EXIT_FAILURE);
		}
	}
	return (true);
}

void	ftls_initdir(const char *dir)
{
	t_ftls		*data;

	data = malloc(sizeof(t_ftls));
	data->dp = opendir(dir);
	data->name = ft_strdup(dir); //TODO: Think about removing this
	data->fname = ft_strdup(dir);
	if ((g_ftls_flags & t) || !data->dp)
	{
		data->stat = malloc(sizeof(struct stat));
		if (lstat(dir, data->stat))
		{
			ft_btreeadd(&g_ftls_ntree, data, &ftls_sort);
			return ;
		}
		if ((data->stat->st_mode & S_IFMT) != S_IFDIR)
		{
			ft_btreeadd(&g_ftls_ctree, data, g_sort);
			return ;
		}
	}
	else
		data->stat = 0;
	ft_btreeadd(&g_ftls_dtree, data, g_sort);
}

void	ftls_fdne(void *data)
{
	t_ftls	*ftls;

	ftls = (t_ftls *)data;
	printf("ft_ls: %s: No such file or directory\n", ftls->name);
	free(ftls->name);
	free(ftls->stat);
	free(ftls);
}

void	ftls_pcdir(void *data)
{
	t_ftls			*ftls;

	ftls = (t_ftls *)data;
	printf("%s\n", ftls->name);
	if (!ftls->fname)
	{
		free(ftls->name);
		free(ftls->stat);
		free(ftls);
	}
}

#define FTLS_HIDDEN(str) (ft_strcmp(str, ".") && ft_strcmp(str, ".."))
#define FTLS_ATEST(str) (g_ftls_flags & a) ? FTLS_HIDDEN(str) : true
#define FTLS_FLAG(TYPE) (g_ftls_flags & TYPE)
#define FTLS_ISDIR(file) ((file->stat->st_mode & S_IFMT) == S_IFDIR)

void	ftls_mkfile(const char *name, const char *path)
{
	t_ftls	*file;

	file = malloc(sizeof(t_ftls));
	file->name = ft_strdup(name);
	file->stat = 0;
	file->fname = 0;
	if (g_ftls_flags & (R | t | l))
	{
		file->stat = malloc(sizeof(struct stat));
		asprintf(&(file->fname), "%s%s%s", path,
		(!ft_strcmp("/", path)) ? "" : "/", name);
		lstat(file->fname, file->stat);
	}
	if (FTLS_FLAG(R) && FTLS_ISDIR(file) && FTLS_ATEST(file->name))
	{
		file->dp = opendir(file->fname);
		ft_btreeadd(&g_ftls_dtree, file, g_sort);
	}
	else if (file->fname)
	{
		free(file->fname);
		file->fname = 0;
	}
	ft_btreeadd(&g_ftls_ctree, file, g_sort);
}

void	ftls_pdir(t_ftls *ftls)
{
	struct dirent	*sdp;

	if (g_ftls_print)
		printf("\n%s:\n", ftls->fname);
	else
		g_ftls_print = true;
	if (ftls->dp)
	{
		while ((sdp = readdir(ftls->dp)) != NULL)
			if (sdp->d_name[0] != '.' || g_ftls_flags & a)
				ftls_mkfile(sdp->d_name, ftls->fname);
		ft_btreeiof(g_ftls_ctree, &ftls_pcdir);
		g_ftls_ctree = 0;
		closedir(ftls->dp); //TODO: Func to clean directory
	}
	else
		dprintf(2, "ft_ls: %s: Permission denied\n", ftls->name);
	free(ftls->name);
	free(ftls->fname);
	if (ftls->stat)
		free(ftls->stat);
	free(ftls);
}

void	ftls_select_sort(void)
{//TODO: rtsort needs to be fixed?
	if (g_ftls_flags & (r | t))
		g_sort = &ftls_rtsort;
	if (g_ftls_flags & r)
		g_sort = &ftls_rsort;
	else if (g_ftls_flags & t)
		g_sort = &ftls_tsort;
	else
		g_sort = &ftls_sort;
}

int		main(int argc, const char **argv)
{
	while (--argc > 0 && **++argv == '-')
		if (!ftls_option(*argv))
		{
			++argv;
			--argc;
			break ;
		}
	ftls_select_sort();
	while (argc--)
		ftls_initdir(*argv++);
	if (!g_ftls_dtree && !g_ftls_ctree && !g_ftls_ntree)
		ftls_initdir(".");
	ft_btreeiof(g_ftls_ntree, &ftls_fdne);
	ft_btreeiof(g_ftls_ctree, &ftls_pcdir);
	if (g_ftls_ctree)
	{
		g_ftls_ctree = 0;
		g_ftls_print = true;
	}
	while (g_ftls_dtree)
		ftls_pdir((t_ftls *)ft_btreermmin(&g_ftls_dtree));
	return (0);
}
