/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_main_unaddressable.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz <ddiniz@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 17:05:09 by ddiniz            #+#    #+#             */
/*   Updated: 2022/08/12 17:55:45 by ddiniz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

int	main(void)
{
	char	*buffer;
	int		*track;

	buffer = (char *)malloc(3 * sizeof(buffer));
	track = (int *)malloc(sizeof(int));
	/* A função write é uma syscall e estamos passando o buffer pra ela. */
	write (1, buffer, 3);
	/* A função return é uma syscall e estamos passando um elemento do buffer */
	return (track[0]);
}
