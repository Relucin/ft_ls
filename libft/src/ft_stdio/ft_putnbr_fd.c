/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmontoya <bmontoya@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/03 00:18:04 by bmontoya          #+#    #+#             */
/*   Updated: 2017/05/21 16:46:06 by bmontoya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <ftstring.h>

void	ft_putnbr_fd(int n, int fd)
{
	char			str[12];
	long int		i;
	unsigned int	len;
	unsigned int	flag;

	flag = (n < 0) ? 1 : 0;
	i = (flag) ? (long int)n * -1 : n;
	len = 0;
	while (n && ++len)
		n /= 10;
	len += (!len) ? 1 : 0;
	str[0] = '-';
	str[len-- + flag] = '\0';
	while (len)
	{
		str[len-- + flag] = ((i % 10) + '0');
		i /= 10;
	}
	str[0 + flag] = ((i % 10) + '0');
	write(fd, &(*str), ft_strlen(str));
}
