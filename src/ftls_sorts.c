/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftls_sorts.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmontoya <bmontoya@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 19:45:28 by bmontoya          #+#    #+#             */
/*   Updated: 2017/05/21 23:30:25 by bmontoya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ftls.h>
#include <ftstring.h>

int		ftls_sort(t_ftls *d1, t_ftls *d2)
{
	if (!d1->fname || !d2->fname)
		return (ft_strcmp(d1->name, d2->name));
	return (ft_strcmp(d1->fname, d2->fname));
}

int		ftls_rsort(t_ftls *d1, t_ftls *d2)
{
	if (!d1->fname || !d2->fname)
		return (ft_strcmp(d2->name, d1->name));
	return (ft_strcmp(d2->fname, d1->fname));
}

int		ftls_tsort(t_ftls *d1, t_ftls *d2)
{
	long	test;

	test = d2->stat->st_mtimespec.tv_sec - d1->stat->st_mtimespec.tv_sec;
	if (!test)
	{
		test = d2->stat->st_mtimespec.tv_nsec - d1->stat->st_mtimespec.tv_nsec;
		if (!test)
			return (ftls_sort(d1, d2));
	}
	if (test >= 0)
		return (1);
	return (-1);
}

int		ftls_rtsort(t_ftls *d1, t_ftls *d2)
{
	long test;

	test = d1->stat->st_mtimespec.tv_sec - d2->stat->st_mtimespec.tv_sec;
	if (!test)
	{
		test = d1->stat->st_mtimespec.tv_nsec - d2->stat->st_mtimespec.tv_nsec;
		if (!test)
			return (ftls_rsort(d1, d2));
	}
	if (test >= 0)
		return (1);
	return (-1);
}
