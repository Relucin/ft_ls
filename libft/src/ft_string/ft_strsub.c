/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmontoya <bmontoya@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/02 00:28:02 by bmontoya          #+#    #+#             */
/*   Updated: 2017/05/21 16:26:52 by bmontoya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char *ns;
	char *hold;

	if (!(ns = (char*)malloc(len + 1)))
		return (NULL);
	hold = ns;
	len += start;
	while (start < len)
		*ns++ = s[start++];
	*ns = '\0';
	return (hold);
}
