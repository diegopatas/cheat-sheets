/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_invalid_write_sol.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz <ddiniz@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 23:09:32 by ddiniz            #+#    #+#             */
/*   Updated: 2022/08/12 11:04:46 by ddiniz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

int	main(void)
{
	char	*string_1;

	string_1 = (char *)malloc(4 * sizeof(char));
	string_1[0] = '0';
	string_1[1] = '4';
	string_1[2] = '2';
	string_1[3] = '\0';
	printf("str_1: %s\n", string_1);
// 	free(string_1);
	return (0);
}
