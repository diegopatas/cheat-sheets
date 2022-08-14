/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_invalid_read_sol.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz <ddiniz@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 22:41:05 by ddiniz            #+#    #+#             */
/*   Updated: 2022/08/12 11:08:10 by ddiniz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

int	main(void)
{
	char	*string;

	/* Agora nós alocamos espaço suficiente e atribuímos o byte '\0' */
	string = (char *)malloc(3 * sizeof(char));
	string[0] = '4';
	string[1] = '2';
	string[2] = '\0';
	printf("Value: %s\n", string);
// 	free(string);
	return (0);
}
