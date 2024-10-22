### 1. Inclusão de Bibliotecas
```c
#include <stdio.h>
#include <stdlib.h>
```
- **`<stdio.h>`**: Inclui funções para entrada e saída padrão, como `printf` e `scanf`.
- **`<stdlib.h>`**: Inclui funções para alocação de memória dinâmica, como `malloc` e `free`.

### 2. Definição da Estrutura da Célula
```c
struct reg {
    int conteudo;
    struct reg *prox;
};

typedef struct reg celula;
```
- **`struct reg`**: Define a estrutura da célula, que contém um inteiro (`conteudo`) e um ponteiro (`prox`) para a próxima célula na lista.
- **`typedef`**: Cria um alias (`celula`) para facilitar o uso da estrutura, permitindo declarar variáveis do tipo `celula`.

### 3. Função para Imprimir a Lista
```c
void imprimirLista(celula *inicio) {
    celula *atual = inicio;
    while (atual != NULL) {
        printf("%d -> ", atual->conteudo);
        atual = atual->prox;
    }
    printf("NULL\n");
}
```
- **`imprimirLista`**: Recebe um ponteiro para a primeira célula da lista.
- **`atual`**: Um ponteiro usado para percorrer a lista.
- **`while`**: Loop que itera sobre a lista enquanto `atual` não for `NULL`, imprimindo o `conteudo` de cada célula.
- **`printf("NULL\n")`**: Indica o fim da lista.

### 4. Função para Adicionar Elemento
```c
celula* adicionarElemento(celula *inicio, int valor) {
    celula *novaCelula = (celula*)malloc(sizeof(celula));
    if (novaCelula == NULL) {
        fprintf(stderr, "Erro na alocação de memória!\n");
        return inicio;
    }
    novaCelula->conteudo = valor;
    novaCelula->prox = inicio; // Insere no início
    return novaCelula;
}
```
- **`adicionarElemento`**: Recebe a cabeça da lista (`inicio`) e um valor para adicionar.
- **`malloc`**: Aloca memória para uma nova célula. Se a alocação falhar, imprime um erro e retorna a lista original.
- **`novaCelula->conteudo`**: Define o valor da nova célula.
- **`novaCelula->prox = inicio`**: O ponteiro `prox` da nova célula aponta para a célula anterior (ou `NULL`, se for a primeira).
- **Retorna**: O novo início da lista, que agora inclui a nova célula.

### 5. Função para Remover a Lista e Liberar Memória
```c
void removerLista(celula *inicio) {
    celula *atual = inicio;
    celula *temp;

    while (atual != NULL) {
        temp = atual;
        atual = atual->prox;
        free(temp); // Libera a memória da célula
    }
}
```
- **`removerLista`**: Recebe a cabeça da lista e libera a memória de todas as células.
- **`temp`**: Um ponteiro temporário que armazena a célula atual antes de mover para a próxima.
- **`free(temp)`**: Libera a memória da célula atual. Este processo continua até que todas as células sejam liberadas.

### 6. Função Principal
```c
int main() {
    celula *lista = NULL;

    // Adicionando três instâncias à lista
    lista = adicionarElemento(lista, 10);
    lista = adicionarElemento(lista, 20);
    lista = adicionarElemento(lista, 30);

    // Imprimindo a lista
    printf("Lista encadeada: ");
    imprimirLista(lista);

    // Calculando a quantidade de memória gasta por cada instância da célula
    printf("Memória usada por cada célula: %lu bytes\n", sizeof(celula));

    // Remover a lista e liberar a memória
    removerLista(lista);
    lista = NULL;

    return 0;
}
```
- **`main`**: A função principal onde a execução começa.
- **`celula *lista = NULL;`**: Inicializa a lista como vazia.
- **`adicionarElemento`**: Adiciona três valores à lista (10, 20, 30).
- **`imprimirLista`**: Chama a função para imprimir os valores da lista.
- **`sizeof(celula)`**: Calcula e imprime o tamanho em bytes de uma célula.
- **`removerLista(lista)`**: Libera a memória da lista após o uso e define `lista` como `NULL` para evitar referências a memória liberada.

### 7. Compilação e Execução
Para compilar e executar o código:
```bash
gcc -o lista_encadeada lista_encadeada.c
./lista_encadeada
```
- **`gcc`**: Compilador C que cria um executável a partir do código fonte.
- **`./lista_encadeada`**: Executa o programa compilado.

### Considerações Finais
- **Gerenciamento de Memória**: É fundamental garantir que toda a memória alocada seja liberada após o uso para evitar vazamentos de memória.
- **Erros de Alocação**: Sempre verifique se a alocação de memória foi bem-sucedida.
- **Estruturas de Dados**: Entender listas encadeadas é essencial para aprender sobre estruturas de dados mais complexas e a manipulação de memória em C.

### Código Completo

```c
#include <stdio.h>
#include <stdlib.h>

// Definição da estrutura da célula
struct reg {
    int conteudo;
    struct reg *prox;
};

typedef struct reg celula;

// Função para imprimir todos os valores da lista
void imprimirLista(celula *inicio) {
    celula *atual = inicio;
    while (atual != NULL) {
        printf("%d -> ", atual->conteudo);
        atual = atual->prox;
    }
    printf("NULL\n");
}

// Função para adicionar um novo elemento à lista
celula* adicionarElemento(celula *inicio, int valor) {
    celula *novaCelula = (celula*)malloc(sizeof(celula));
    if (novaCelula == NULL) {
        fprintf(stderr, "Erro na alocação de memória!\n");
        return inicio;
    }
    novaCelula->conteudo = valor;
    novaCelula->prox = inicio; // Insere no início
    return novaCelula;
}

// Função para remover todos os elementos da lista e liberar a memória
void removerLista(celula *inicio) {
    celula *atual = inicio;
    celula *temp;

    while (atual != NULL) {
        temp = atual;
        atual = atual->prox;
        free(temp); // Libera a memória da célula
    }
}

// Função principal
int main() {
    celula *lista = NULL;

    // Adicionando três instâncias à lista
    lista = adicionarElemento(lista, 10);
    lista = adicionarElemento(lista, 20);
    lista = adicionarElemento(lista, 30);

    // Imprimindo a lista
    printf("Lista encadeada: ");
    imprimirLista(lista);

    // Calculando a quantidade de memória gasta por cada instância da célula
    printf("Memória usada por cada célula: %lu bytes\n", sizeof(celula));

    // Remover a lista e liberar a memória
    removerLista(lista);
    lista = NULL;

    return 0;
}
```
