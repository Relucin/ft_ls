/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftpf_otypes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmontoya <bmontoya@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 20:53:27 by bmontoya          #+#    #+#             */
/*   Updated: 2017/05/21 17:35:47 by bmontoya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftpf_printf.h"
#include <stdlib.h>
#include <ftstring.h>

char	*ftpf_noarg(char c, size_t *len)
{
	char	*ret;

	ret = malloc(2);
	if (!c)
	{
		g_part.len = 0;
		ret[0] = '\0';
		return (ret);
	}
	ret[0] = c;
	ret[1] = '\0';
	*len += 1;
	g_part.len = 1;
	if (g_part.width > 1)
		return (ftpf_pad(ret, len, 1));
	return (ret);
}

char	*ftpf_pointer(size_t *len, va_list ap)
{
	char	*ret;
	char	*tmp;

	ret = ftpf_ultoa_base(va_arg(ap, uint64_t), 16);
	if (*ret == '0' && g_part.p)
		*ret = '\0';
	g_part.len = ft_strlen(ret);
	g_part.prec -= (g_part.prec > g_part.len) ? g_part.len : g_part.prec;
	g_part.len += g_part.prec + 2;
	g_part.width -= (g_part.width > g_part.len) ? g_part.len : g_part.width;
	g_part.len += g_part.width;
	tmp = ft_strnew(g_part.len);
	if (!(g_part.flags & (NEG | ZER)) || (!(g_part.flags & NEG) && g_part.p))
		ft_strcatmulti(tmp, " ", g_part.width);
	ft_strcat(tmp, "0x");
	if ((g_part.flags & ZER) && !(g_part.flags & NEG) && !g_part.p)
		ft_strcatmulti(tmp, "0", g_part.width);
	ft_strcatmulti(tmp, "0", g_part.prec);
	ft_strcat(tmp, ret);
	if ((g_part.flags & NEG))
		ft_strcatmulti(tmp, " ", g_part.width);
	free(ret);
	*len += g_part.len;
	return (tmp);
}

char	*ftpf_npointer(size_t *len, va_list ap)
{
	if (g_part.length & (l | ll | j | z))
		*va_arg(ap, long *) = (long)*len;
	else if (g_part.length & h)
		*va_arg(ap, int *) = (short)*len;
	else if (g_part.length & hh)
		*va_arg(ap, int *) = (char)*len;
	else
		*va_arg(ap, int *) = (int)*len;
	return (0);
}

char	*ftpf_arg(size_t *len, va_list ap, t_parse f)
{
	va_list	dap;
	char	*tmp;

	va_copy(dap, ap);
	while (--g_part.arg)
		(void)va_arg(dap, void *);
	tmp = f(len, dap);
	va_end(dap);
	return (tmp);
}
