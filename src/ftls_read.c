/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftls_read.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmontoya <bmontoya@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/23 15:24:58 by bmontoya          #+#    #+#             */
/*   Updated: 2017/05/23 15:29:19 by bmontoya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ftls.h>
#include <ftstdio.h>
#include <dstruct/ftbtree.h>
#include <stdlib.h>

void	ftls_readdir(t_ftls *ftls, t_btree **sub_dir)
{
	struct dirent	*sdp;

	while ((sdp = readdir(ftls->dp)) != NULL)
	{
		if (sdp->d_name[0] != '.' || g_ftls_flags & a)
			ftls_add_file(sdp->d_name, ftls->fname, sub_dir);
	}
	if (ftls->err)
		ft_dprintf(2, "ls: %s: Permission denied\n", ftls->name);
	else if ((g_ftls_flags & l) && g_ftls_ctree)
		ft_printf("total %d\n", g_ftls_blocks);
	ft_btreeiof(g_ftls_ctree, &ftls_print_file);
	ftls_clear_globals();
	g_ftls_ctree = 0;
	closedir(ftls->dp);
}

void	ftls_readtree(t_ftls *ftls)
{
	t_btree			*sub_dir;

	sub_dir = 0;
	if (g_ftls_print)
		ft_printf("%s%s:\n", (g_ftls_print++ == 1) ? "" : "\n", ftls->fname);
	else
		g_ftls_print = 2;
	if (ftls->dp)
		ftls_readdir(ftls, &sub_dir);
	else
		ft_dprintf(2, "ls: %s: Permission denied\n", ftls->name);
	free(ftls->name);
	free(ftls->fname);
	free(ftls->stat);
	free(ftls);
	while (sub_dir)
		ftls_readtree((t_ftls *)ft_btreermmin(&sub_dir));
}
