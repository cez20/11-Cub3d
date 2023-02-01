/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anarodri <anarodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 11:29:15 by anarodri          #+#    #+#             */
/*   Updated: 2022/12/15 12:50:28 by anarodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Outputs the character ’c’ to the given file descriptor. */

#include "../libft.h"

void	ft_putchar_fd(char c, int fd)
{
	write (fd, &c, 1);
}
