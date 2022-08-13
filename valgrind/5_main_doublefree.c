/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5_main_doublefree.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz <ddiniz@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 18:41:42 by ddiniz            #+#    #+#             */
/*   Updated: 2022/08/12 19:06:47 by ddiniz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

int	main(void)
{
	char	*word;
	char	*wrapper;

	word = (char *)malloc(3 * sizeof(word));
	wrapper = word;
	word[0] = '4';
	word[1] = '2';
	word[2] = '\0';
	printf("Bang! %s\n", word);
	/* A seguir operamos um double free diretamente.
	 * Pode ocorrer de operarmos apenas um free, mas não no endereço inicial do
	 * bloco, algo como free(++word). O log de erro é o mesmo, mas o problema
	 * é outro! */
	free(word);
	free(wrapper);
	return (0);
}
