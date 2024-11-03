#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define TAMANHO_PAGINA 4096          // Tamanho da página em bytes
#define NUM_FRAMES 1024              // Total de frames na memória física
#define NUM_PAGINAS 4096             // Total de páginas na memória virtual
#define MAX_PAGINAS_POR_PROCESSO 1024 // Máximo de páginas por processo

// Estrutura para um frame na memória física
typedef struct {
    int id;
    bool ocupado;
    int processo_id;
    int pagina_id;
} Frame;

// Estrutura para uma página na memória virtual
typedef struct {
    int id;
    bool carregada;
    int frame_id;
} Pagina;

// Entrada na tabela de páginas
typedef struct {
    int pagina_id;
    int frame_id;
    bool valida;
} EntradaTabelaPaginas;

// Tabela de páginas de um processo
typedef struct {
    int processo_id;
    EntradaTabelaPaginas entradas[MAX_PAGINAS_POR_PROCESSO];
} TabelaPaginas;

// Memória física
typedef struct {
    Frame frames[NUM_FRAMES];
    int num_frames_ocupados;
} MemoriaFisica;

// Memória virtual
typedef struct {
    Pagina paginas[NUM_PAGINAS];
} MemoriaVirtual;

// Inicialização das estruturas
void inicializar_memoria_fisica(MemoriaFisica *memoria_fisica);
void inicializar_memoria_virtual(MemoriaVirtual *memoria_virtual);
void inicializar_tabela_paginas(TabelaPaginas *tabela, int processo_id);

// Mapeamento de uma página para um frame
bool mapear_pagina(MemoriaFisica *memoria_fisica, MemoriaVirtual *memoria_virtual, TabelaPaginas *tabela, int pagina_id);

// Tradução de endereço virtual para físico
int traduzir_endereco(MemoriaVirtual *memoria_virtual, TabelaPaginas *tabela, int endereco_virtual);

// Função de teste para simulação
void testar_simulador(MemoriaFisica *memoria_fisica, MemoriaVirtual *memoria_virtual);

int main() {
    MemoriaFisica memoria_fisica;
    MemoriaVirtual memoria_virtual;

    inicializar_memoria_fisica(&memoria_fisica);
    inicializar_memoria_virtual(&memoria_virtual);

    testar_simulador(&memoria_fisica, &memoria_virtual);

    return 0;
}

// Funções de inicialização
void inicializar_memoria_fisica(MemoriaFisica *memoria_fisica) {
    for (int i = 0; i < NUM_FRAMES; i++) {
        memoria_fisica->frames[i].id = i;
        memoria_fisica->frames[i].ocupado = false;
        memoria_fisica->frames[i].processo_id = -1;
        memoria_fisica->frames[i].pagina_id = -1;
    }
    memoria_fisica->num_frames_ocupados = 0;
}

void inicializar_memoria_virtual(MemoriaVirtual *memoria_virtual) {
    for (int i = 0; i < NUM_PAGINAS; i++) {
        memoria_virtual->paginas[i].id = i;
        memoria_virtual->paginas[i].carregada = false;
        memoria_virtual->paginas[i].frame_id = -1;
    }
}

void inicializar_tabela_paginas(TabelaPaginas *tabela, int processo_id) {
    tabela->processo_id = processo_id;
    for (int i = 0; i < MAX_PAGINAS_POR_PROCESSO; i++) {
        tabela->entradas[i].pagina_id = -1;
        tabela->entradas[i].frame_id = -1;
        tabela->entradas[i].valida = false;
    }
}

// Mapeia uma página para um frame disponível
bool mapear_pagina(MemoriaFisica *memoria_fisica, MemoriaVirtual *memoria_virtual, TabelaPaginas *tabela, int pagina_id) {
    for (int i = 0; i < NUM_FRAMES; i++) {
        if (!memoria_fisica->frames[i].ocupado) {
            memoria_fisica->frames[i].ocupado = true;
            memoria_fisica->frames[i].processo_id = tabela->processo_id;
            memoria_fisica->frames[i].pagina_id = pagina_id;

            memoria_virtual->paginas[pagina_id].carregada = true;
            memoria_virtual->paginas[pagina_id].frame_id = i;

            tabela->entradas[pagina_id].pagina_id = pagina_id;
            tabela->entradas[pagina_id].frame_id = i;
            tabela->entradas[pagina_id].valida = true;

            return true;
        }
    }
    return false; // Sem frames disponíveis
}

// Traduz um endereço virtual para físico
int traduzir_endereco(MemoriaVirtual *memoria_virtual, TabelaPaginas *tabela, int endereco_virtual) {
    int num_pagina = endereco_virtual / TAMANHO_PAGINA;
    int offset = endereco_virtual % TAMANHO_PAGINA;

    if (tabela->entradas[num_pagina].valida) {
        int frame_id = tabela->entradas[num_pagina].frame_id;
        return frame_id * TAMANHO_PAGINA + offset;
    }
    printf("Page fault: Página %d não carregada na memória física.\n", num_pagina);
    return -1;
}

// Função de teste para simular o funcionamento
void testar_simulador(MemoriaFisica *memoria_fisica, MemoriaVirtual *memoria_virtual) {
    TabelaPaginas tabela_paginas;
    inicializar_tabela_paginas(&tabela_paginas, 1); // Processo 1

    // Simulação de endereços virtuais que o processo deseja acessar
    int enderecos_virtuais[] = {0, 4096, 8192, 12288}; // Exemplos de endereços em bytes
    int num_enderecos = sizeof(enderecos_virtuais) / sizeof(enderecos_virtuais[0]);

    printf("Mapeando páginas...\n");
    for (int i = 0; i < num_enderecos; i++) {
        int num_pagina = enderecos_virtuais[i] / TAMANHO_PAGINA;
        mapear_pagina(memoria_fisica, memoria_virtual, &tabela_paginas, num_pagina);
    }

    printf("\nTraduzindo endereços virtuais para físicos...\n");
    for (int i = 0; i < num_enderecos; i++) {
        int endereco_fisico = traduzir_endereco(memoria_virtual, &tabela_paginas, enderecos_virtuais[i]);
        if (endereco_fisico != -1) {
            printf("Endereço Virtual: %d -> Endereço Físico: %d\n", enderecos_virtuais[i], endereco_fisico);
        }
    }
}
