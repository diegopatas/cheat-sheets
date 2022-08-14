/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_main_unaddressable_sol.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz <ddiniz@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 17:05:09 by ddiniz            #+#    #+#             */
/*   Updated: 2022/08/12 18:39:49 by ddiniz           ###   ########.fr       */
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
	/* Abaixo inicializamos o buffer adequadamente */
	buffer[0] = '4';
	buffer[1] = '2';
	buffer[2] = '\0';
	/* A seguir também inicializamos o track */
	track[0] = 0;
	write (1, buffer, 3);
// 	free(buffer);
// 	free(track);
	return (track[0]);
}
