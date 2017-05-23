/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmontoya <bmontoya@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 17:25:59 by bmontoya          #+#    #+#             */
/*   Updated: 2017/05/21 16:36:10 by bmontoya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

char	*ft_strncpy(char *dst, const char *src, size_t n)
{
	unsigned int count;

	count = 0;
	while (count < n)
	{
		if (*src)
			dst[count++] = *src++;
		else
			dst[count++] = '\0';
	}
	return (dst);
}
