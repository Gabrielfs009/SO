// Gabriel Forster Souza - 10409702
// Rodrigo Mello de Campos Silva - 10409316
// Rodrigo Lucas Rosales - 10365071
// Vitor Leandro Machado - 10409358

#define _GNU_SOURCE
#include <malloc.h>
#include <sched.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

// Pilha de 64kB
#define FIBER_STACK (1024 * 64)

// Estrutura para manter dados compartilhados
struct ThreadArgs {
  int data;
  int returnData;
};

// A thread filha executará esta função
int threadFunction(void *argument) {
  struct ThreadArgs *args = (struct ThreadArgs *)argument;
  printf("Thread filha recebeu dados do pai: %d\n", args->data);
  args->returnData = args->data * 2; // Modifica os dados e os retorna ao pai
  printf("Thread filha saindo\n");
  return 0;
}

int main() {
  void *stack;
  pid_t pid;
  struct ThreadArgs args;
  args.data = 42; // Dados de exemplo para passar para a thread filha

  // Aloca a pilha
  stack = malloc(FIBER_STACK);
  if (stack == NULL) {
    perror("malloc: não foi possível alocar a pilha");
    exit(1);
  }

  printf("Criando thread filha\n");

  // Chama a função clone do sistema para criar a thread filha
  pid =
      clone(&threadFunction, (char *)stack + FIBER_STACK,
            SIGCHLD | CLONE_FS | CLONE_FILES | CLONE_SIGHAND | CLONE_VM, &args);
  if (pid == -1) {
    perror("clone");
    exit(2);
  }

  // Aguarda a saída da thread filha
  pid = waitpid(pid, NULL, 0);
  if (pid == -1) {
    perror("waitpid");
    exit(3);
  }

  // Libera a pilha
  free(stack);
  printf("Thread filha retornou e a pilha foi liberada.\n");
  printf("Dados recebidos da thread filha: %d\n",
         args.returnData); // Imprime os dados recebidos da thread filha

  return 0;
}
