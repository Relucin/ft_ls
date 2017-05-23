/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmontoya <bmontoya@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/08 19:02:46 by bmontoya          #+#    #+#             */
/*   Updated: 2017/05/21 23:16:48 by bmontoya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftpf_printf.h"
#include <ftstring.h>
#include <stdlib.h>
#include <unistd.h>

int		ft_vasprintf(char **ret, const char *format, va_list ap)
{
	t_string	**parts;
	t_string	**phold;
	char		*tret;
	int			len;

	ftpf_resetpart();
	len = ft_strcrep(format, '%');
	parts = malloc(sizeof(*parts) * (len * 2 + 2));
	phold = parts;
	len = ftpf_parse(parts, format, ap);
	if (!(tret = ft_strnew(len)))
		return (-1);
	*ret = tret;
	while (*parts)
	{
		ft_strncpy(tret, (*parts)->str, (*parts)->len);
		tret += (*parts)->len;
		free((*parts)->str);
		free(*parts);
		parts++;
	}
	free(phold);
	return (len);
}

int		ft_dprintf(int fd, const char *format, ...)
{
	va_list	ap;
	char	*cret;
	int		iret;

	va_start(ap, format);
	iret = ft_vasprintf(&cret, format, ap);
	write(fd, cret, iret);
	free(cret);
	va_end(ap);
	return (iret);
}

int		ft_asprintf(char **ret, const char *format, ...)
{
	va_list	ap;
	int		iret;

	va_start(ap, format);
	iret = ft_vasprintf(ret, format, ap);
	va_end(ap);
	return (iret);
}

int		ft_vprintf(const char *format, va_list ap)
{
	char	*cret;
	int		iret;

	iret = ft_vasprintf(&cret, format, ap);
	write(1, cret, iret);
	free(cret);
	return (iret);
}

int		ft_printf(const char *format, ...)
{
	va_list	ap;
	int		ret;

	va_start(ap, format);
	ret = ft_vprintf(format, ap);
	va_end(ap);
	return (ret);
}
