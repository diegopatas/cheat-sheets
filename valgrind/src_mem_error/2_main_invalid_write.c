/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_invalid_write.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz <ddiniz@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 23:09:32 by ddiniz            #+#    #+#             */
/*   Updated: 2022/08/12 11:08:54 by ddiniz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

/* Há um leak proposital no programa */

int	main(void)
{
	char	*string_1;

	/* A seguir é alocado espaço insuficiente para a var string_1 e é esperado
	 * que haja 2 erros de invalid write pegos pelo valgrind */
	string_1 = (char *)malloc(2 * sizeof(char));
	string_1[0] = '0';
	string_1[1] = '4';
	string_1[2] = '2';
	string_1[3] = '\0';
	printf("str_1: %s\n", string_1);
	/* A printf é a responsável pelos erros de invalid read, já cobertos */
	return (0);
}
