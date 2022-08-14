/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_main_lost_starter_pointer_2.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz <ddiniz@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 10:37:43 by ddiniz            #+#    #+#             */
/*   Updated: 2022/08/13 11:17:07 by ddiniz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

/* O problema aqui é o de andar com o endereço inicial do bloco alocado.
 * Repare que conseguimos trabalhar com a memória, porém ocorre o leak igualmen
 * te. */
int	main(void)
{
	char	*ptr;

	ptr = (char *)malloc(42 * sizeof(char));
	/* A linha a seguir avança para o próximo endereço do bloco alocado. */
	ptr++;
	ptr[0] = '4';
	ptr[1] = '2';
	ptr[2] = '\0';
	printf("Cartoon: %s\n", ptr);
	/* A free também é inefetiva nesse caso */
	free(ptr);
	return (0);
}
