/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmontoya <bmontoya@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 17:15:46 by bmontoya          #+#    #+#             */
/*   Updated: 2017/05/21 16:38:16 by bmontoya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ftstring.h>

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t ilen;

	if (!size)
		return (ft_strlen(src));
	ilen = 0;
	while (*dst && --size)
	{
		dst++;
		ilen++;
	}
	ilen += ft_strlen(src);
	if (!size)
		return (++ilen);
	size--;
	while (size--)
		*dst++ = *src++;
	*dst = '\0';
	return (ilen);
}
