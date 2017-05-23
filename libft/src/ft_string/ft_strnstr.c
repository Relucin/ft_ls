/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmontoya <bmontoya@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 20:39:39 by bmontoya          #+#    #+#             */
/*   Updated: 2017/05/21 16:35:14 by bmontoya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	unsigned int f;
	unsigned int s;

	f = 0;
	s = 0;
	while (f < len && big[f])
	{
		if (!little[s])
			return ((char*)(big + f));
		if (f + s < len && big[f + s] == little[s])
		{
			s++;
			continue;
		}
		s = 0;
		f++;
	}
	if (!little[0])
		return ((char*)big);
	return (NULL);
}
