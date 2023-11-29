#ifndef GERADOR_H
#define GERADOR_H

// Estrutura para representar uma Pessoa
typedef struct {
    int chave; // Novo campo para representar a chave única
    char nome[50];
    int idade;
    float altura;
} Pessoa;

// Estrutura Elemento para lista encadeada
typedef struct Elemento {
    Pessoa pessoa; // Contém os dados de uma pessoa
    struct Elemento *proximo; // Ponteiro para o próximo elemento na lista
} Elemento;

// Protótipos das funções do gerador.c
Elemento *criarElemento(int chave);
void armazenarDadosMemoria(Elemento **lista, Elemento *novoElemento);
void gravarDadosBinario(Elemento *lista, const char *nomeArquivo);
Elemento *lerDadosTexto(const char *nomeArquivo);
void gerarDados(Pessoa *pessoas, int quantidade);

void liberarMemoria(Elemento *lista);

#endif
