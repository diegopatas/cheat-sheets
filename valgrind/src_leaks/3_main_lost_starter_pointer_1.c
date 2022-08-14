/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_main_lost_starter_pointer_1.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz <ddiniz@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 10:37:43 by ddiniz            #+#    #+#             */
/*   Updated: 2022/08/13 11:08:35 by ddiniz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

/* O problema presente é o de alocar memória para a var ptr, depois atribuir
 * outro endereço (string literal) e assim perdemos o rastro do bloco alocado.
 * Mesmo aplicando free não resolve o problema. */
int	main(void)
{
	char	*ptr;
	char	*str;

	ptr = (char *)malloc(42 * sizeof(char));
	str = "ricky and morry";
	/* A linha a seguir nos faz perder o rastro do bloco alocado. */
	ptr = str;
	printf("Cartoon: %s\n", ptr);
	/* A free não é capaz de desempenhar sua função. */
	free(ptr);
	return (0);
}
