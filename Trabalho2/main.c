#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "gerador.h"
#include "exportador.h"
#include "editor.h"

// Função principal
int main()
{
    const int quantidade = 20;
    Pessoa pessoas[quantidade]; // Array de 20 pessoas

    gerarDados(pessoas, quantidade); // Gera dados aleatórios para as pessoas

    exportarParaBinario("pessoas.bin", pessoas, quantidade); // Exporta dados para arquivo binário
    exportarParaTexto("pessoas.txt", pessoas, quantidade);   // Exporta dados para arquivo de texto

    Elemento *lista = NULL; // Inicializa uma lista encadeada de Elemento a partir do array de Pessoa

    // Preenche a lista encadeada com os dados das pessoas
    for (int i = 0; i < quantidade; ++i)
    {
        Elemento *novoElemento = criarElemento(pessoas[i].chave); // Cria um novo elemento com a chave única
        novoElemento->pessoa = pessoas[i];                        // Preenche o elemento com os dados da Pessoa
        armazenarDadosMemoria(&lista, novoElemento);              // Armazena na lista
    }

    // Opções do Editor
    editarDados(&lista, "pessoasatt.bin", "pessoasatt.txt"); // Chama função para editar os dados

    liberarMemoria(lista); // Liberar memória alocada para a lista

    return 0;
}
