/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftpf_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmontoya <bmontoya@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 15:01:20 by bmontoya          #+#    #+#             */
/*   Updated: 2017/05/21 17:42:33 by bmontoya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <ftstring.h>
#include "ftpf_printf.h"

char	*ftpf_ultoa_base(uint64_t nbr, int base)
{
	uint64_t	cpy;
	uint8_t		length;
	char		*ret;

	cpy = nbr;
	length = 0;
	while (cpy)
	{
		cpy /= base;
		++length;
	}
	if (!nbr)
		++length;
	ret = malloc(sizeof(*ret) * (length + 1));
	ret[length--] = '\0';
	if (!nbr)
		ret[0] = '0';
	while (nbr)
	{
		ret[length--] = "0123456789abcdef"[nbr % base];
		nbr /= base;
	}
	return (ret);
}

char	*ftpf_ltoa_10(int64_t nbr)
{
	char	*tmp;
	char	*ret;
	char	l[2];

	if (nbr >= 0)
		return (ftpf_ultoa_base(nbr, 10));
	l[0] = ((nbr % 10) * -1) + '0';
	l[1] = '\0';
	nbr = (nbr / 10) * -1;
	if (nbr)
	{
		tmp = ftpf_ultoa_base(nbr, 10);
		ret = malloc(ft_strlen(tmp) + 3);
		ft_strcpy(ret, "-");
		ft_strcat(ret, tmp);
		free(tmp);
	}
	else
	{
		ret = malloc(3);
		ft_strcpy(ret, "-");
	}
	ft_strcat(ret, l);
	return (ret);
}

void	ftpf_resetpart(void)
{
	g_part.width = 0;
	g_part.prec = 0;
	g_part.arg = 0;
	g_part.flags = 0;
	g_part.p = 0;
	g_part.length = 0;
}

char	*ftpf_pad(char *str, size_t *len, size_t strl)
{
	char	*tmp;
	char	*thold;
	char	*shold;
	char	pad;

	pad = (g_part.flags & ZER && !(g_part.flags & NEG)) ? '0' : ' ';
	shold = str;
	tmp = ft_strnew(g_part.width);
	thold = tmp;
	g_part.width -= strl;
	*len += g_part.width;
	g_part.len += g_part.width;
	if (g_part.flags & NEG)
		while (*str)
			*tmp++ = *str++;
	while (g_part.width)
	{
		*tmp++ = pad;
		--g_part.width;
	}
	if (!(g_part.flags & NEG))
		while (*str)
			*tmp++ = *str++;
	free(shold);
	return (thold);
}
