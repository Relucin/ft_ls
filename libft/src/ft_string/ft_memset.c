/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmontoya <bmontoya@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/01 14:20:53 by bmontoya          #+#    #+#             */
/*   Updated: 2017/05/21 16:41:10 by bmontoya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memset(void *b, int c, size_t len)
{
	char			*s;
	unsigned int	i;

	s = (char*)b;
	i = 0;
	while (i < len)
		s[i++] = c;
	return (b);
}
