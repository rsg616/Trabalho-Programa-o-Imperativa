#include "exportador.h"
#include <stdio.h>

// Exporta dados para um arquivo binário
void exportarParaBinario(const char *nomeArquivo, Pessoa *pessoas, int quantidade)
{
    FILE *arquivo = fopen(nomeArquivo, "wb"); // Abre o arquivo para escrita binária
    if (arquivo == NULL)
    {
        perror("Erro ao abrir o arquivo");
        return;
    }

    fwrite(pessoas, sizeof(Pessoa), quantidade, arquivo); // Escreve os dados no arquivo binário
    fclose(arquivo);                                      // Fecha o arquivo após a escrita
}

// Exporta dados para um arquivo de texto
void exportarParaTexto(const char *nomeArquivo, Pessoa *pessoas, int quantidade)
{
    FILE *arquivo = fopen(nomeArquivo, "w"); // Abre o arquivo para escrita de texto
    if (arquivo == NULL)
    {
        perror("Erro ao abrir o arquivo");
        return;
    }

    // Escreve os dados das pessoas no arquivo de texto
    for (int i = 0; i < quantidade; i++)
    {
        fprintf(arquivo, "Numero de Cadastro: %d\nNome: %s\nIdade: %d\nAltura: %.2f\n\n",
                pessoas[i].chave, pessoas[i].nome, pessoas[i].idade, pessoas[i].altura);
    }

    fclose(arquivo); // Fecha o arquivo após a escrita
}

// Exporta dados de uma lista encadeada para um arquivo de texto sem a verificação do array de pessoas
void exportarListaParaTexto(const char *nomeArquivo, Elemento *lista, Pessoa pessoas[])
{
    FILE *arquivo = fopen(nomeArquivo, "w"); // Abre o arquivo para escrita de texto
    if (arquivo == NULL)
    {
        perror("Erro ao abrir o arquivo");
        return;
    }

    Elemento *elementoAtual = lista;
    while (elementoAtual != NULL)
    {
        int chave_lista = elementoAtual->pessoa.chave; // Chave na lista

        fprintf(arquivo, "Chave: %d\n", pessoas[chave_lista - 1].chave);
        fprintf(arquivo, "Nome: %s\n", pessoas[chave_lista - 1].nome);
        fprintf(arquivo, "Idade: %d\n", pessoas[chave_lista - 1].idade);
        fprintf(arquivo, "Altura: %.2f\n\n", pessoas[chave_lista - 1].altura);

        elementoAtual = elementoAtual->proximo;
    }

    fclose(arquivo); // Fecha o arquivo após a escrita
}
