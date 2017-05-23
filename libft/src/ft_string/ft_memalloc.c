/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmontoya <bmontoya@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/01 17:26:42 by bmontoya          #+#    #+#             */
/*   Updated: 2017/05/21 16:53:20 by bmontoya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>

void	*ft_memalloc(size_t size)
{
	void *mem;
	char *tmp;

	if (!size || !(mem = malloc(size)))
		return (NULL);
	tmp = (char*)mem;
	while (--size)
		*tmp++ = 0;
	*tmp = 0;
	return (mem);
}
