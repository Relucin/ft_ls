/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftls_set.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmontoya <bmontoya@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/23 15:20:56 by bmontoya          #+#    #+#             */
/*   Updated: 2017/05/23 15:22:23 by bmontoya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ftls.h>

void	ftls_select_sort(void)
{
	if (g_ftls_flags & r)
	{
		if (g_ftls_flags & t)
			g_sort = &ftls_rtsort;
		else
			g_sort = &ftls_rsort;
	}
	else if (g_ftls_flags & t)
		g_sort = &ftls_tsort;
	else
		g_sort = &ftls_sort;
}

void	ftls_clear_globals(void)
{
	g_ftls_blocks = 0;
	g_ftls_lnklen = 0;
	g_ftls_owrlen = 0;
	g_ftls_grplen = 0;
	g_ftls_bytes = 0;
	g_ftls_major = 0;
	g_ftls_minor = 0;
}
