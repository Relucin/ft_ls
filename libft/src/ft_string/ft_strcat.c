/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmontoya <bmontoya@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 15:35:03 by bmontoya          #+#    #+#             */
/*   Updated: 2017/05/21 16:40:40 by bmontoya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ftstring.h>

char	*ft_strcat(char *s1, const char *s2)
{
	(void)ft_strcpy(s1 + ft_strlen(s1), s2);
	return (s1);
}
