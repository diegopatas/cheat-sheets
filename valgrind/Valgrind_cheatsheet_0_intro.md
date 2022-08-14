---
Aliases: 
---
%%
> Tag: [[valgrind]]
> Type: #type/product/tech 
> Status: #status/check-in
> Previous: [[Valgrind_cheatsheet_0_intro]]
> Next: [[Valgrind_cheatsheet_1_mem_error]]

> Branches: [[Valgrind_cheatsheet_2_leak]]

%%

> Context: #issue/no-tag #issue/orphan #issue/no-type 

---
# Valgrind Memcheck Tool - Introdução
---
## Recadinhos

1. Esse material é introdutório e não exaustivo.
3. Os códigos fonte desse workaround estão disponíveis para baixar nesse repositório.
	- Eles contém comentários indicando as partes problemáticas resolvidas nesse tutorial.
4. Esses códigos foram compilados usando `gcc -Wall -Wextra -Werror main.c`
5. Se você é cadete da 42SP e caso prefira, verifique com a comunidade onde achar o vídeo que gravamos sobre esse conteúdo.
6. RTFM!: `man valgrind` ou `man 1 valgrind`.

## O que é o Valgrind?

O `valgrind` é na verdade um conjunto de ferramentas que inclui o Memcheck, Callgrind, entre outros. Nesse workaround vamos abordar o `memcheck`.

 O `memcheck` é uma ferramenta de detecção de erros de memória, como por exemplo leitura e escrita inválida de memória, leaks de memória dinamicamente alocada, etc.

## Cheatsheet

```bash
gcc -Wall -Wextra -Werror <meu_binario>

# Formas equivalentes de executar o valgrind
valgrind <meu_binario>
valgrind --tool=memcheck <meu_binario>

# Flags essenciais
valgrind --leak-check=full <meu_binario>
valgrind --track-origins=yes <meu_binario>
valgrind --show-leak-kinds=all <meu_binario>

valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes <meu_bin>
```

---
## Antes de mais nada: a função `malloc` o perigo da alocação dinâmica de memória

A maior parte dos problemas e bugs de um programa relacionados à memória está relacionado a alocação dinâmica da mesma. 


O compilador consegue nos auxiliar na identificação de alguns problemas existentes na stack em tempo de compilação, mas nos dá carta branca para manipular a heap, e é aí que mora o perigo.


Tenhamos em mente que a função `malloc(3)` reserva um pedaço de memória na região da Heap e retorna um ponteiro que aponta para a primeira posição do bloco em questão. 


A função `free(3)` remove a reserva realizada pela `malloc(3)`, mas ainda assim estamos permitidos usar a variável que continha o endereço da região alocada e liberada.

---

###### Reference

- Documentação:
	- [Memcheck: a memory error detector](https://valgrind.org/docs/manual/mc-manual.html#mc-manual.leaks)
	- [Valgrind gdbserver](https://valgrind.org/docs/manual/manual-core-adv.html#manual-core-adv.gdbserver-commandhandling)
- Livros:
	- 
- Vídeos:
	- [Using Valgrind: Free Tools for Memory Management and Debugging](https://www.youtube.com/watch?v=-VDiEe9hxC4&list=PLhaU2Dr9h_F2g3hBdtjPETI0cDp14AwVO&index=34)
	- [Beginner's Guide to Valgrind](https://www.youtube.com/watch?v=QmYhUDYY_nY&list=PLhaU2Dr9h_F2GjIL6X0hg9BurYInCU3ux&index=18)
- Artigos:
	- [Eliminating undefined values with Valgrind, the easy way – Nicholas Nethercote](https://blog.mozilla.org/nnethercote/2009/02/27/eliminating-undefined-values-with-valgrind-the-easy-way/)
	- [Paper sobre verificação bit a bit do Memcheck](https://valgrind.org/docs/memcheck2005.pdf)