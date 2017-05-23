/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmontoya <bmontoya@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/01 15:12:47 by bmontoya          #+#    #+#             */
/*   Updated: 2017/05/21 16:40:56 by bmontoya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ftstring.h>

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	char *d;
	char *s;

	d = (char*)(dst + n - 1);
	s = (char*)(src + n - 1);
	if (src > dst)
		return (ft_memcpy(dst, src, n));
	while (n)
	{
		*d-- = *s--;
		n--;
	}
	return (dst);
}
