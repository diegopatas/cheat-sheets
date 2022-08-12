/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_invalid_read.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz <ddiniz@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 22:41:05 by ddiniz            #+#    #+#             */
/*   Updated: 2022/08/12 11:07:39 by ddiniz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

/* Há um leak proposital no programa */

int	main(void)
{
	char	*string;

	/* A linha a seguir não aloca espaço suficiente para a var string receber o
	 * byte '\0' */
	string = (char *)malloc(2 * sizeof(char));
	string[0] = '4';
	string[1] = '2';
	printf("Value: %s\n", string);
	/* A função printf segue lendo a var string e esbarra num endereço proibido.
	 * Em C, o byte '\0' determina onde uma string se encerra. */
	return (0);
}
