/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftpf_strings.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmontoya <bmontoya@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 16:26:49 by bmontoya          #+#    #+#             */
/*   Updated: 2017/05/21 17:33:22 by bmontoya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ftpf_printf.h>
#include <ftstring.h>
#include <stdlib.h>

size_t	ftpf_wtos(char *ret, wchar_t str)
{
	size_t	i;

	i = 0;
	if (str < (MB_CUR_MAX == 1 ? 0xFF : 0x7F))
		ret[i++] = str;
	else
	{
		if (str < (1 << 11))
			ret[i++] = 0xC0 | (str >> 6);
		else
		{
			if (str < (1 << 16))
				ret[i++] = 0xE0 | (str >> 12);
			else
			{
				ret[i++] = 0xF0 | (str >> 18);
				ret[i++] = 0x80 | ((str >> 12) & 0x3F);
			}
			ret[i++] = 0x80 | ((str >> 6) & 0x3F);
		}
		ret[i++] = 0x80 | (str & 0x3F);
	}
	ret[i] = 0;
	return (i);
}

char	*ftpf_wstos(wchar_t *str)
{
	uint64_t	i;
	char		*ret;
	char		tmp[5];

	i = 0;
	while (str[i])
		i++;
	ret = malloc(sizeof(*ret) * ((i * 4) + 1));
	ret[0] = '\0';
	g_part.prec = (g_part.p) ? g_part.prec : i * 4;
	g_part.p = 0;
	while (*str)
	{
		if (g_part.prec >= (i = ftpf_wtos(tmp, *str++)))
		{
			g_part.prec -= i;
			ft_strcat(ret, tmp);
		}
		else
			break ;
	}
	return (ret);
}

char	*ftpf_string(size_t *len, va_list ap)
{
	char		*aps;
	char		*tmp;
	uint64_t	strl;

	aps = va_arg(ap, char *);
	if (!aps)
	{
		aps = malloc(7);
		ft_strcpy(aps, "(null)");
		g_part.length |= l;
	}
	else if (g_part.length & l)
		aps = ftpf_wstos((wchar_t*)aps);
	strl = ft_strlen(aps);
	strl = (g_part.p && strl > g_part.prec) ? g_part.prec : strl;
	*len += strl;
	g_part.len = strl;
	tmp = ft_strsub(aps, 0, strl);
	if (g_part.length & l)
		free(aps);
	if (g_part.width > strl)
		return (ftpf_pad(tmp, len, strl));
	return (tmp);
}

#define FTPF_CM(t) (!(g_part.flags & NEG)) ? g_part.width + t : t

char	*ftpf_chars(size_t *len, va_list ap)
{
	char	*ret;
	char	*tmp;

	ret = ft_strnew(4);
	g_part.len = 1;
	if (g_part.length & l)
		g_part.len += ftpf_wtos(ret, va_arg(ap, wchar_t)) - 1;
	else
		ret[0] = (char)va_arg(ap, int);
	*len += g_part.len;
	g_part.width -= (g_part.width > g_part.len) ? g_part.len : g_part.width;
	if (g_part.width)
	{
		tmp = ft_strnew(g_part.len + g_part.width);
		if (!(g_part.flags & NEG))
			ft_strcatmulti(tmp, (g_part.flags & ZER) ? "0" : " ", g_part.width);
		ft_memcpy(FTPF_CM(tmp), ret, g_part.len);
		if (g_part.flags & NEG)
			ft_strcatmulti(tmp + g_part.len, " ", g_part.width);
		g_part.len += g_part.width;
		*len += g_part.width;
		free(ret);
		return (tmp);
	}
	return (ret);
}
