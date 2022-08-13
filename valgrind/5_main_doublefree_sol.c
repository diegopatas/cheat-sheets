/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5_main_doublefree_sol.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz <ddiniz@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 18:41:42 by ddiniz            #+#    #+#             */
/*   Updated: 2022/08/12 19:28:29 by ddiniz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

int	main(void)
{
	char	*word;
	char	*wrapper;

	word = (char *)malloc(3 * sizeof(word));
	word[0] = '4';
	word[1] = '2';
	word[2] = '\0';
	wrapper = word;
	/* A seguir usamos a var wrapper no lugar da var word e aplicamos free. */
	printf("Bang! %s\n", wrapper);
	free(wrapper);
	return (0);
}
