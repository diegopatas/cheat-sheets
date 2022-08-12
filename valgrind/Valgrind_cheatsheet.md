---
Aliases: 
---
%%
> Tag: [[valgrind]]
> Type: #type/product/tech 
> Status: #status/check-in
> Previous: 
> Next: 

> Branches: 

%%

> Context: #issue/no-tag #issue/orphan #issue/no-type 

---
# Valgrind (Memcheck)
---
## Breve introdução

1. Esse material é introdutório e não exaustivo.
3. Ele acompanha os códigos fonte dos exemplos que estão disponíveis para download.
4. Esses códigos foram compilados usando `gcc -Wall -Wextra -Werro main.c`
5. Se você é cadete da 42SP e caso prefira, verifique com a comunidade onde achar o vídeo que gravamos sobre esse conteúdo.

## O que é o Valgrind?

- `valgrind` é na verdade um conjunto de ferramentas que inclui o Memcheck, Callgrind, entre outros. Nesse workaround vamos abordar o `memcheck`.
- `memcheck` é uma ferramenta de detecção de erros de memória, como por exemplo leitura e escrita inválida de memória, leaks de memória dinamicamente alocada, etc.


---
## Comandos básicos
- Os comandos a seguir são equivalente e rodam o vanilla `valgrind`.

```bash
valgrind --tool=memcheck <meu_binário>
```

```bash
valgrind <meu_binário>
```

---
## Tipos de erros detectados e como interpretá-los

### Erro do tipo Invalid read/ invalid write

- Invalid Read
	- Ocorre quando você tenta acessar/ler uma memória a qual você não possui permissão.
- Invalid Write
	- Ocorre quando você tenta escrever/gravar em uma memória a qual você não possui permissão.

**Exemplo: Invalide read**

- Programa: `1_main_invalid_read.c`.
- Problema: uma string foi alocada e inicializada, mas não foi alocado espaço suficiente para o abrigar o byte nulo, `\0`.	
- Lembre-se de compilar o programa e depois executar o `valgrind`.

```bash
gcc main_invalid_read.c
valgrind a.out
```

- Saída:

```bash
==31957== Invalid read of size 1    # <==== AQUI!
==31957==    at 0x48426B4: __strlen_sse2 (vg_replace_strmem.c:496)
==31957==    by 0x48DFD14: __vfprintf_internal (vfprintf-internal.c:1688)
==31957==    by 0x48C8D3E: printf (printf.c:33)
==31957==    by 0x1091AC: main (in /home/diego/main/2k_Projeto/2005_Git/42_school/42_Game/0_cheatsheet/valgrind/a.out)
==31957==  Address 0x4a5c042 is 0 bytes after a block of size 2 alloc'd
==31957==    at 0x483C855: malloc (vg_replace_malloc.c:381)
==31957==    by 0x10917E: main (in /home/diego/main/2k_Projeto/2005_Git/42_school/42_Game/0_cheatsheet/valgrind/a.out)
==31957== 
Value: 42 
```

- Solução: alocar mais espaço e atribuir o byte nulo, `\0`. 
- Veja os comentários no source code do programa `1_main_invalid_read_sol.c`.

### Vamos interpretar essa saída

**Leitura**

- A saída está em forma de pilha (stack), então a primeira função chamada pelo programa, que é a `main`, vem por último;
- Os endereços em hexadecimal indicam a variáveis envolvidas no B.O. (informação útil para ser usada no GDB);
- O número à esquerda na forma `==256256==` é o ID do seu programa/ processo, isto é, o PID;
- A informação entre parênteses indica o arquivo e a linha por onde o problema passou, `(printf.c:33)`.
- O `valgrind` exibe o tamanho dos elementos que deram problema, então o `Invalid read of size 1` indica possivelmente o tipo da var problemática; nesse caso, provavelmente estamos lidando com um `char` que costuma ter `size` 1 por default no sistema. Se houver 2 logs na forma `Invalid read of size 1` quer dizer que 2 `char` independentes são a fonte do erro.


**Troubleshooting**

- Então um bom caminho seria olhar qual variável tentamos ler na função `printf`;
- Depois, verificar o que alocamos na função `malloc`;
- Por fim, avaliar como inicialização nossa variável problemática.
	- Temos o byte nulo? 
	- A quantidade de espaço foi alocada corretamente?

---
**Exemplo: invalid write**

- Programa: `2_main_invalid_write.c`.
- Problema: uma string foi alocada, mas não tem espaço suficiente para receber uma cópia de conteúdo de outra string maior.


```bash
gcc main_invalid_write.c
valgrind a.out
```

- Saída:

```bash 
==32987== Invalid write of size 1  # <==== AQUI!                                                                                                                
==32987==    at 0x10919D: main (in /home/diego/main/2k_Projeto/2005_Git/42_school/42_Game/0_cheatsheet/valgrind/a.out)                             
==32987==  Address 0x4a5c042 is 0 bytes after a block of size 2 alloc'd                                                                            
==32987==    at 0x483C855: malloc (vg_replace_malloc.c:381)                                                                                        
==32987==    by 0x10917E: main (in /home/diego/main/2k_Projeto/2005_Git/42_school/42_Game/0_cheatsheet/valgrind/a.out)                             
```

- Solução: alocar mais espaço para alocar todos os dados necessários.
- Veja os comentários no source code do programa `2_main_invalid_write_sol.c`.

---
### Erro do tipo **Uninitialized**

- Invalid
	- Lembrando que, como vimos, erros do tipo invalid ocorrem geralmente quando alocamos e definimos uma variável, mas a memória alocada não foi suficiente para armazenar todos os dados necessários, então quando tentamos acessar a área adjacente de memória ocorrem os problemas.
- Uninitialized
	- **Uninitialized error** ocorre quando alocamos memória, mas não definimos/ atribuímos um valor para a variável alocada.

- Programa: `3_main_uninitialized_malloc.c`.
- Problema: a variável `creator` foi alocada, mas não inicializada.
- Saída:

```bash
==46475== Conditional jump or move depends on uninitialised value(s) # <== AQUI!
==46475==    at 0x48426A9: __strlen_sse2 (vg_replace_strmem.c:496)
==46475==    by 0x48DFD14: __vfprintf_internal (vfprintf-internal.c:1688)
==46475==    by 0x48C8D3E: printf (printf.c:33)
==46475==    by 0x1091A9: main (in /home/diego/main/2k_Projeto/2005_Git/42_school/42_Game/0_cheatsheet/valgrind/a.out)
```

- Solução: inicializar a variável com algum valor adequado.
- Veja os comentários no source code do programa `3_main_uninitialized_malloc_sol.c`.

**Observação**

- No programa `3_main_uninitialized_gccflag.c` consta um exemplo onde usamos uma variável do tipo `int` sem inicializá-la, mas esse problema é identificado pelo compilador com o uso de flag. O mesmo não ocorre se usamos a função`malloc`.

- Para testar essa afirmação, faça:

```bash
gcc -Werror 3_main_uninitialized_gccflag.c
```

- Porém, se você não usar as flags de compilação, então vai observar um erro parecido.
- Então, usando a flag `--track-origins=yes` você é capaz de identificar que a sua variável problemática foi inicializada na área `stack` do seu programa.

```bash
gcc 3_main_uninitialized_gccflag.c
valgrind --track-origins=yes a.out
```

- Saída:

```bash
# 
==47699== Conditional jump or move depends on uninitialised value(s)                                                                            
==47699==    at 0x48DE958: __vfprintf_internal (vfprintf-internal.c:1687)                                                                          
==47699==    by 0x48C8D3E: printf (printf.c:33)                                                                                                    
==47699==    by 0x10917A: main (in /home/diego/main/2k_Projeto/2005_Git/42_school/42_Game/0_cheatsheet/valgrind/a.out)                             
==47699==  Uninitialised value was created by a stack allocation  # <==== AQUI!                                                                                 
==47699==    at 0x109149: main (in /home/diego/main/2k_Projeto/2005_Git/42_school/42_Game/0_cheatsheet/valgrind/a.out)
# 
```


---
### Details about malloc and free functions

- `malloc`
	- It reserves a piece of memory into the heap and returns a pointer to the first spot of the memory.
- `free`
	- It removes the reservation about a piece of memory previously allocated. 
	- You can still work with the variable.
	- You cannot free a pointer twice, one right after another.

```bash
valgrind --leak-check=full <your_program>
```

```bash
valgrind --track-origins=yes <your_program>
```

```bash
valgrind --show-leak-kinds=all
```

#### **Callgrind** commands

```bash
valgrind --tool=calgrind <your_program>
```

```bash
callgrind_annotate callgrind.out.PID -inclusive=yes --tree=both | grep -v build
```


