/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftls_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmontoya <bmontoya@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/23 15:17:34 by bmontoya          #+#    #+#             */
/*   Updated: 2017/05/23 15:19:35 by bmontoya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ftls.h>
#include <ftstdio.h>
#include <stdlib.h>
#include <errno.h>

void	ftls_print_file(t_ftls *ftls)
{
	if (ftls->err && ftls->err != ENOENT)
		ft_dprintf(2, "ls: %s: Permission denied\n", ftls->name);
	else if (g_ftls_flags & l)
		ftls_pl(ftls);
	else
		ft_printf("%s\n", ftls->name);
	if (!(g_ftls_flags & R) || (ftls->stat->st_mode & S_IFMT) != S_IFDIR)
	{
		free(ftls->fname);
		free(ftls->name);
		if (ftls->stat)
			free(ftls->stat);
		free(ftls);
	}
}

void	ftls_fdne(t_ftls *ftls)
{
	ft_dprintf(2, "ls: %s: No such file or directory\n",
	(*ftls->name) ? ftls->name : "fts_open");
	free(ftls->name);
	free(ftls->fname);
	free(ftls->stat);
	free(ftls);
}
