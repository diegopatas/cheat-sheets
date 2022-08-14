---
Aliases: 
---
%%
> Tag: [[valgrind]]
> Type: #type/product/tech 
> Status: #status/check-in
> Previous: [[Valgrind_cheatsheet_1_mem_error]]
> Next: 

> Branches: 

%%

> Context: #issue/no-tag #issue/orphan #issue/no-type 

---
# Valgrind Parte 2: leaks

---
## Funcionamento e interpretação

O Memcheck realiza uma série de rastreios, entre eles, todos os ponteiros devolvidos a cada chamada da função `malloc(3)`, então quando o programa é encerrado a Memcheck consegue determinar quais desses ponteiros não foram liberados com a função `free(3)`.


Observe que um bloco de memória alocado pode ser acessado de duas formas. Uma é através do ponteiro que aponta para o início do bloco (starter-pointer), que é devolvido pela `malloc`. A outra é através de um ponteiro que aponta para qualquer endereço subsequente ao endereço inicial do bloco (interior-pointer). 

Por exemplo, se um bloco de memória tem quatro posições, então um ponteiro guardando o endereço da primeira posição é um starter-pointer e um ponteiro apontando para qualquer uma das outras três é um interior-pointer.

Dito isso, vamos observar 4 tipos de leaks identificados na saída do valgrind, no LEAK SUMMARY, que tem relação com esses tipos de ponteiros citados.

**Exemplo: LEAK SUMMARY**

```
LEAK SUMMARY:
   definitely lost: 48 bytes in 3 blocks.
   indirectly lost: 32 bytes in 2 blocks.
     possibly lost: 96 bytes in 6 blocks.
   still reachable: 64 bytes in 4 blocks.
        suppressed: 0 bytes in 0 blocks.

```


- Vamos entender o que diz cada um desses quatro agrupamentos:
	- *Still reachable:* há starter-pointers apontando para os blocos antes do final do programa, ou seja, seriam passíveis de um free e fáceis de serem resolvidos.
	- *Definitely lost:* não há ponteiros acessando o bloco, ou seja, nenhuma variável guarda o endereço do bloco, logo a função free não pode ser aplicada diretamente, e isso é um problema crítico para o programa.
	- *Indirectly lost:* quando há perdas indiretas de endereço. Ocorre quando um starter-pointer se perde e isso causa a perda de todos os ponteiros que dependiam do starter-pointer para serem acessados.
	- *Possibly lost:* ocorre quando identifica-se algum interior-pointer ativo, ou seja, existe a possibilidade de um starter-pointer do programa estar perdido?


**Atenção:** o log não diz como, onde ou o porquê seu programa vazou, isso é contigo! E os mais perigosos vazamentos são os *definitely* e *possibly lost*.

---
## Comandos e flags

A primeira flag é a `--leak-check=full` que reproduz mais detalhes dos vazamentos do tipo *definitely lost* e *possibly lost*. Aliás, dado que nem todo erro apontado pelo Valgrind é um erro de fato, como por exemplo interromper um programa em andamento via um sinal, essa flag vai apontar todos os erros realmente problemático.

A essa altura você já deve entender melhor do log, então vou omití-lo. O comando fica assim:

```bash
valgrind --leak-check=full <meu_binario>
```

Em conjunto com a flag `--leak-check` você pode usar a flag `--show-leak-kinds` para detalhar os leaks. Alguns exemplos de combinações:

```bash
valgrind --leak-check=full --show-leak-kinds=all <meu_binario>
valgrind --leak-check=full --show-leak-kinds=none <meu_binario>
valgrind --leak-check=full --show-leak-kinds=definite <meu_binario>
valgrind --leak-check=full --show-leak-kinds=reacheable <meu_binario>
valgrind --leak-check=full --show-leak-kinds=indirect <meu_binario>
valgrind --leak-check=full --show-leak-kinds=possible <meu_binario>
valgrind --leak-check=full --show-leak-kinds=definite,possible <meu_binario>
```

Agora, a flag para fechar esse circuito básico é a `--track-origins=yes`, ela é responsável por rastrear a origem dos valores não inicializados (pode entendê-los como não definidos). De fato, o Valgrind vai identificar os valores não inicializados que estão sendo utilizados de uma forma a apresentar perigos ao programa, do contrário, esses problemas são ignorados.

Juntando todas as flags, temos:

```bash
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes <meu_binario>
```

---
## Uma breve discussão sobre undefined values

A primeira coisa a se ter em mente é que o Memcheck passa um pente fino em cada bit dos valores presentes no programa. Isso o permite determinar se cada um é definido ou indefinido, e além disso, a ferramente faz operações de verificação sempre que necessário. Ou seja, nada passa indeterminado.

De fato, um valor não inicializado não é um problema se ele não for usado de uma forma crítica no programa, como por exemplo, para avaliar uma condição de desvio em um `if`. Veja um exemplo no programa `2_main_stack_heap_sol_2.c`. 

Outros casos onde o valgrind vai apontar problemas:
- Desvios condicionais (devido a possíveis comportamentos indefinidos);
- Valores como argumentos em syscalls;
- Como um endereço num carregamento ou armazenamento.

---
## Usando o Valgrind-Memcheck em conjunto com o GDB

Em primeiro lugar, é necessário compilar seu projeto usando a flag `-g` ou `-g3` de modo que fiquem disponíveis os símbolos para serem visualizados, a saber, seu código fonte.

Depois, é necessário executar o valgrind com as flags `--vgdb=yes --vgdb-error=0`, dessa forma:

```bash
valgrind --vgdb=yes --vgdb-error=0 <meu_binario>
```

O Programa irá iniciar um loop, então é necessário abrir o GDB em outro terminal nesse momento, para estabelecer a conexão entre os dois.

Execute o gdb:

```bash
gdb -q <meu_binario> --tui
```

Agora, execute o comando a seguir para estabelecer a conexão:

```bash
target remote | vgdb
```

Para utilizar o valgrind no gdb é necessário usar o comando `monitor` pois ele é o responsável por fazer as requisições ao processo do valgrind. Exemplos de uso:

```bash
monitor leak_check full reachable any  # LEAK SUMMARY
mo l f r a                             # versão curta do comando acima
monitor v.kill                         # encerra a conexão
info inferiors
kill
k
kill inferiors <number>
```

E esses comandos encerram o workaround.

---
# Conclusão

Vimos como trabalhar com o básico dos erros de memória com exemplos. Também vimos como ocorrem os vazamentos de memória, também com exemplos. Encerramos com a combinação do GDB com o Valgrind, de maneira simples.

Então agora é: bora codar cambada!
