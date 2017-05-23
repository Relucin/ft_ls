/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftpf_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmontoya <bmontoya@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 21:08:11 by bmontoya          #+#    #+#             */
/*   Updated: 2017/05/21 17:34:46 by bmontoya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftpf_printf.h"
#include <ftstring.h>
#include <stdlib.h>

t_parse		g_ftpffuncs[6] =
{
	&ftpf_string, &ftpf_chars, &ftpf_signed,
	&ftpf_pointer, &ftpf_unsigned, &ftpf_npointer
};

void		ftpf_converter(char c)
{
	if (c == 'D' || c == 'O' || c == 'U' || c == 'C' || c == 'S')
	{
		g_part.length |= l;
		c += 32;
		g_part.type = c;
	}
	else
		g_part.type = c;
	if (g_part.type == 'i')
		g_part.type = 'd';
	if (c == 'b' || c == 'o' || c == 'u' || c == 'x' || c == 'X')
	{
		if (c == 'b')
			g_part.base = 2;
		else if (c == 'o')
			g_part.base = 8;
		else if (c == 'u')
			g_part.base = 10;
		else
			g_part.base = 16;
		if (c == 'X')
			g_part.flags |= X;
		g_part.type = 'u';
	}
}

char		*ftpf_getstr(const char **format, size_t *len, va_list ap)
{
	static char	*types = "scdpun";
	uint8_t		i;

	i = 0;
	while (**format)
	{
		if (!ftpf_checkflags(format))
			if (!ftpf_checkprecision(format, ap))
				if (!ftpf_checknums(format, ap))
					if (!ftpf_checklength(format))
						break ;
	}
	ftpf_converter(**format);
	while (types[i] && types[i] != g_part.type)
		i++;
	if (**format)
		++(*format);
	if (types[i] && g_part.arg)
		return (ftpf_arg(len, ap, g_ftpffuncs[i]));
	else if (types[i])
		return (g_ftpffuncs[i](len, ap));
	else
		return (ftpf_noarg(g_part.type, len));
}

t_string	*ftpf_addtstr(char *str)
{
	t_string *new;

	new = malloc(sizeof(t_string));
	new->str = str;
	new->len = g_part.len;
	return (new);
}

t_string	*ftpf_addpart(const char **fmt, size_t *len, int *plen, va_list ap)
{
	char	*str;

	if (*plen)
	{
		str = ft_strsub(*fmt, 0, *plen);
		*len += *plen;
		(*fmt) += *plen;
		g_part.len = *plen;
		*plen = 0;
		return (ftpf_addtstr(str));
	}
	str = ftpf_getstr(fmt, len, ap);
	if (str)
		return (ftpf_addtstr(str));
	else
		return (0);
}

int			ftpf_parse(t_string **parts, const char *format, va_list ap)
{
	int			i;
	t_string	*tmp;
	size_t		len;

	i = 0;
	len = 0;
	while (format[i])
	{
		if (format[i] == '%')
		{
			if (i > 0)
				*parts++ = ftpf_addpart(&format, &len, &i, ap);
			format++;
			tmp = ftpf_addpart(&format, &len, &i, ap);
			if (tmp)
				*parts++ = tmp;
			ftpf_resetpart();
		}
		if (format[i] && format[i] != '%')
			++i;
	}
	if (i)
		*parts++ = ftpf_addpart(&format, &len, &i, ap);
	*parts = 0;
	return (len);
}
