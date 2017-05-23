/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmontoya <bmontoya@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 20:39:39 by bmontoya          #+#    #+#             */
/*   Updated: 2017/05/21 16:27:11 by bmontoya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

char	*ft_strstr(const char *big, const char *little)
{
	unsigned int f;
	unsigned int s;

	f = 0;
	s = 0;
	if (!big[0] && !little[0])
		return ((char*)big);
	while (big[f])
	{
		if (!little[s])
			return ((char*)(big + f));
		if (big[f + s] == little[s])
		{
			s++;
			continue;
		}
		s = 0;
		f++;
	}
	return (NULL);
}
