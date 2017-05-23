/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftpf_numbers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmontoya <bmontoya@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 03:29:50 by bmontoya          #+#    #+#             */
/*   Updated: 2017/05/21 17:41:57 by bmontoya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftpf_printf.h"
#include <ftstring.h>
#include <stdlib.h>

void		ftpf_signedmods(char **str, size_t *tlen, size_t len)
{
	char	*tmp;

	if (len != ft_strlen(*str))
	{
		tmp = ft_strnew(len);
		if (!(g_part.flags & (NEG | ZER)) && g_part.width)
			ft_strcatmulti(tmp, " ", g_part.width);
		if (**str == '-')
			ft_strcat(tmp, "-");
		else if (g_part.flags & (PLS | SPC))
			ft_strcat(tmp, (g_part.flags & PLS) ? "+" : " ");
		if ((g_part.flags & ZER) && !(g_part.flags & NEG) && g_part.width)
			ft_strcatmulti(tmp, (g_part.flags & ZER) ? "0" : " ", g_part.width);
		if (g_part.prec)
			ft_strcatmulti(tmp, "0", g_part.prec);
		ft_strcat(tmp, (**str == '-') ? (*str) + 1 : *str);
		if ((g_part.flags & NEG) && g_part.width)
			ft_strcatmulti(tmp, " ", g_part.width);
		free(*str);
		*str = tmp;
	}
	*tlen += len;
	g_part.len = len;
}

char		*ftpf_signed(size_t *len, va_list ap)
{
	char	*ret;
	size_t	slen;

	if (g_part.length & (l | ll | j | z))
		ret = ftpf_ltoa_10(va_arg(ap, long));
	else if (g_part.length & h)
		ret = ftpf_ltoa_10((short)va_arg(ap, int));
	else if (g_part.length & hh)
		ret = ftpf_ltoa_10((char)va_arg(ap, int));
	else
		ret = ftpf_ltoa_10(va_arg(ap, int));
	if (g_part.p && *ret == '0')
		*ret = '\0';
	if ((g_part.p && (g_part.flags & ZER)) || (g_part.flags & NEG))
		g_part.flags ^= ZER;
	if ((g_part.flags & (PLS | SPC)) == (PLS | SPC))
		g_part.flags ^= SPC;
	slen = (*ret == '-') ? ft_strlen(ret) - 1 : ft_strlen(ret);
	g_part.prec -= (g_part.prec > slen) ? slen : g_part.prec;
	slen += (*ret == '-') ? g_part.prec + 1 : g_part.prec;
	slen += ((g_part.flags & (PLS | SPC)) && *ret != '-') ? 1 : 0;
	g_part.width -= (g_part.width > slen) ? slen : g_part.width;
	slen += g_part.width;
	ftpf_signedmods(&ret, len, slen);
	return (ret);
}

static void	ftpf_usmresolve(char **str, char *tmp, size_t *tlen, size_t len)
{
	free(*str);
	*str = tmp;
	*tlen += len;
	g_part.len = len;
}

void		ftpf_unsignedmods(char **str, size_t *tlen, size_t len)
{
	char	*tmp;

	if (**str == '0' && g_part.p)
	{
		**str = '\0';
		--len;
	}
	g_part.prec -= (g_part.prec > len) ? len : g_part.prec;
	len += (g_part.flags & ALT) ? g_part.prec + 2 : g_part.prec;
	g_part.width -= (g_part.width > len) ? len : g_part.width;
	len += g_part.width;
	tmp = ft_strnew(len);
	if (!(g_part.flags & (NEG | ZER)) && g_part.width)
		ft_strcatmulti(tmp, " ", g_part.width);
	if (g_part.flags & ALT)
		ft_strcat(tmp, (g_part.base == 16) ? "0x" : "0b");
	if ((g_part.flags & ZER) && !(g_part.flags & NEG) && g_part.width)
		ft_strcatmulti(tmp, "0", g_part.width);
	ft_strcatmulti(tmp, "0", g_part.prec);
	ft_strcat(tmp, *str);
	if ((g_part.flags & NEG) && g_part.width)
		ft_strcatmulti(tmp, (g_part.flags & ZER) ? "0" : " ", g_part.width);
	if (g_part.flags & X)
		ft_strupper(tmp);
	ftpf_usmresolve(str, tmp, tlen, len);
}

char		*ftpf_unsigned(size_t *len, va_list ap)
{
	char	*ret;
	size_t	slen;

	if (g_part.length & (l | ll | j | z))
		ret = ftpf_ultoa_base(va_arg(ap, uint64_t), g_part.base);
	else if (g_part.length & h)
		ret = ftpf_ultoa_base((uint16_t)va_arg(ap, uint32_t), g_part.base);
	else if (g_part.length & hh)
		ret = ftpf_ultoa_base((uint8_t)va_arg(ap, uint32_t), g_part.base);
	else
		ret = ftpf_ultoa_base(va_arg(ap, uint32_t), g_part.base);
	slen = ft_strlen(ret);
	if (g_part.base == 8 && (g_part.flags & ALT))
	{
		g_part.flags ^= ALT;
		++g_part.p;
		g_part.prec = (g_part.prec > slen) ? g_part.prec : slen + 1;
		g_part.prec -= (*ret == '0') ? 1 : 0;
	}
	if ((g_part.flags & ZER) && ((g_part.flags & NEG) || g_part.p))
		g_part.flags ^= ZER;
	if ((g_part.flags & ALT) && *ret == '0')
		g_part.flags ^= ALT;
	ftpf_unsignedmods(&ret, len, slen);
	return (ret);
}
