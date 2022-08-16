---
Aliases: 
---
%%
> Type: #type/product/article 
> Status: #status/draft
> Previous: [[C Syntax Improvements Checklist]]
> Next: 

%%

> context:  [[@gonzalez-morris2020Beginning]] #issue/no-tag #issue/orphan #issue/no-type 
> Series: 

---
# C Strutuctures

## Essencial

### Definir

- Você pode criar coleção de variáveis de tipos distintos, chamada estrutura, e tratar essa coleção como uma unidade. Use a palavra-chave `struct` como abaixo:

```c
struct s_horse {
	int  age;
	int  height;
};
```

**Fatos**
- É um novo tipo, não uma nova variável.
- O nome do tipo criado é `tag name`/ `struct tag`.
- As variáveis membros são `membros` ou `atributos`.


### Declarar

- Após criar/ definir um tipo com a `struct` você pode declarar uma variável correspondente:

```c
struct s_horse dubling;
```

### Remover keyword `struct`

- Para remover a necessidade de incluir a palavra `struct` em toda declaração de variável, inclua `typedef` na definição da estrutura:

```c
typedef struct s_horse {
	int age;
	char *name;
};

s_horse paris;
```

### Usar alias

- Você pode criar um para a sua `struct` de duas formas.

- Assim:

```c
typedef struct s_horse t_horse;

struct s_horse {
	int age;
	char *name;
}
```

- ou assim:

```c
typedef struct s_horse {
	int age;
	char *name;
} t_horse;
```

### Acessar/ usar membros da `struct`

- Para acessar um membro de uma `struct` escreva o nome da `struct` seguido de ponto final mais o nome do membro, assim:

```c
t_horse milan;

milan.age = 42;
```

**Fatos:**

- Por si, uma variável `struct` não é um ponteiro.
- O ponto é chamado `selection operator`.

### Inicializar variáveis-membro

- Você pode inicializar membro a membro, assim:

```c
t_horse viena;

viena.age = 42;
viena.name = "ricky";
```

- Você também pode inicializar em lote, com ou sem order, assim:

```c
t_horse paris = {42, "ricky"};
t_horse viena = {.name = "morty", .age = 14};
```

### Array de `struct`

- Você pode criar um array de `struct` e ele segue a mesma lógica de um array simples, exemplo:

```c
typedef struct s_horse {
	int age;
	char *name;
} t_horse;

t_horse my_horses[5];

my_horses[0].age = 42;
```

- Você pode usar normalmente os atributos dos elementos do array numa expressão.

```c
int average;

my_horses[0].age = 42;
my_horses[1].age = 24;
average = (my_horses[0].age = 42 + my_horses[1].age = 24) / 2;
```


## Ponteiros

### Ponteiros para `struct`

- Você pode usar ponteiros para `struct` normalmente.
- Da forma a seguir você aponta para uma variável do tipo `struct`:


```c
t_horse tokyo;
t_horse *ptr;
/* snippets */
ptr = &tokyo;
``` 

- Agora, dessa forma, você aponta pra um elemento de um array:

```c
t_horse toronto[40];
t_horse *ptr;
/* snippets */
ptr = &toronto[0];
```

**Dereferência**

- Há duas formas de dereferênciar os valores dos atributos.
- Assim:

```c
t_horse quebec;
t_horse *ptr;
/* snippets */
ptr = &quebec;
(*ptr).age = 42;
```

- Ou assim:

```c
t_horse oaxaca;
t_horse *ptr;
/* snippets */
ptr = &oaxaca;
ptr->age = 42;
```

**Obs**
- A notação `->` é chamada de ponteiro para membro.
- Essa notação é mais legível.
- Note que a precedência do `selection operator` é maior do que a do ponteiro.

### Alocação dinâmica de `struct`

- Você pode alocar dinamicamente uma `struc` usando a função `malloc(3)`.

```c
#include <stdlib.h>
/* snippets */
t_horse *lima;

lima = (t_horse *)malloc(sizeof(lima));
```

- Você também pode alocar um array de ponteiros, mas precisaria usar loops para alocar todas as variáveis. O essencial é: a notação a seguir é válida.

```c
t_horse *lima[42];
```


**Obs:**
- O uso do operador `sizeof` é fundamental nessa alocação pois o sistema vai buscar sempre o alinhamento de memória, o que torna impraticável a determinação à mão do tamanho da variável do tipo `struct`.

### Incorporação de `struct`

- É possível incorporar uma estrutura dentro de outra e o compilador garante uns 15 níveis de convolução, se necessário.

```c
typedef struct s_date {
	int date;
	int month;
	int year;
} t_date;

typedef struct s_horse {
	t_date birth;
	int teeth;
	char *name;
} t_horse;

t_horse bogota;
bogota.birth.date = 21;
```

### Membros de `struct` do tipo ponteiro para `struct`

- Qualquer ponteiro pode ser um membro de qualquer estrutura. Isso implica que podemos ter um ponteiro do mesmo tipo da estrutura definida, sem erros! 
- Essa aplicação é útil para criarmos estruturas do tipo lista, pilha, árvore e assim por diante.
- Veja um exemplo

```c
typedef struct s_list {
	void *data;
	struct t_list *next;
} t_list;
```

**Interpretação**
- A estrutura possui dois membros.
- O primeiro membro é um ponteiro `void *`, logo pode ser atribuído por qualquer outro tipo de dado, como uma string `char *` relativa ao nome de um cavalo.
- O segundo membro é um ponteiro do tipo `t_list *`, ou seja, ele pode abrigar o endereço de uma variável do mesmo tipo, no caso, uma lista.
- Assim, quando criamos uma lista, um elemento dessa lista possui um nome e o endereço do próximo membro da lista.

## Funções

### Uma `struct` como argumento de função

- Esse comportamento funciona como os demais tipos primitivos.

```c
typedef struct s_data {
	char *password;
	int address;
} t_data;

int ft_my_funct(t_data var_1)
{
	/* snippets */
	return (0);
}
```

### Ponteiros para estruturas como argumentos de função

**Detalhes para ter em mente**
- Quando passamos uma estrutura com um argumento para uma função nós estamos enviando uma cópia dessa estrutura. 
	- Nesse caso, fica assegurada as informações originais da variável.
- Ou seja, quando passamos ponteiros para estruturas como argumentos de função estamos acessando memória que está fora do escopo da `stack` da função chamada e em execução.
	- Nesse caso, pode ser modificado o valor da variável, inclusive seu endereço.

```c
typedef struct s_data {
	char *password;
	int address;
} t_data;

int ft_my_funct(t_data *var_1)
{
	var_1->address = 42;
	/* snippets */
}
```

- Usar um qualificador `const` pode ajudar a minimizar a sensibilidade do código. Ou seja, no escopo da função, a variável é tida como constante.

```c
int ft_my_funct(t_data const *var_1)
{
	/* snippets */
}
```

- Para os casos acima, lembre-se de passar o endereço da `struct` durante a chamada da função no programa.

```c
typedef struct s_data {
	char *password;
	int address;
} t_data;

int ft_my_funct(t_data *var_1)
{
	/* snippets */
}

int main(void)
{
	t_data var_1;
	/* snippets */
	ft_my_funct(&var_1);
	return(0);
}
```

### Retornos de função do tipo `struct`

- Podemos retornar estruturas em chamadas de função, mas é mais conveniente retornar ponteiros para estruturas.

```c
t_horse *ft_create_horse(void)
{
	t_horse *var;
	var = (t_horse *)malloc(sizeof(var));
	return (var);
}
```

## Union

### Compartilhando memória

- Poderíamos compartilhar tipos distintos de estruturas como um grupo. Podem surgir outras necessidades e razões para agrupar dados. De qualquer forma, uma `union` tem a função de facilitar essa operação.

```c
union u_group_data {
	t_horse *tokyo;
	t_data  *info;
} u_group1;
```

- Estruturas `union` dificultam a leitura do código consideravelmente
- Elas trabalham de forma análoga as estruturas `struct`.

## Considerações finais

- Há uma série de detalhes omitidos nesse seção, então consulte a documentação para mais detalhes.
