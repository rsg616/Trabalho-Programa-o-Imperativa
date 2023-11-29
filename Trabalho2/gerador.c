#include "gerador.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> 

// Função para gerar dados aleatórios para um array de Pessoa
void gerarDados(Pessoa *pessoas, int quantidade)
{
    srand(time(NULL));
    // Preenche o array com dados aleatórios para 20 primeiras pessoas
    for (int i = 0; i < quantidade; i++)
    {
        pessoas[i].chave = i + 1; // Atribui valores únicos para a chave
        sprintf(pessoas[i].nome, "Pessoa %d", i + 1);
        pessoas[i].idade = rand() % 100 + 1;
        pessoas[i].altura = (float)(rand() % 200 + 100) / 100;
    }
}

int lerInteiroValidado(FILE *arquivo)
{
    int valor;
    if (fscanf(arquivo, "%d", &valor) != 1)
    {
        printf("Erro: nao foi possível ler um número inteiro valido.\n");
        exit(EXIT_FAILURE);
    }
    // Aqui, você pode realizar mais validações conforme necessário
    if (valor < 0 || valor > 100)
    {
        printf("Erro: valor inteiro fora do intervalo esperado.\n");
        exit(EXIT_FAILURE);
    }
    return valor;
}

void lerArquivo(const char *nomeArquivo)
{
    FILE *arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo %s\n", nomeArquivo);
        exit(EXIT_FAILURE);
    }

    // Exemplo de leitura validada de um número inteiro
    int numeroLido = lerInteiroValidado(arquivo);

    // Use o número lido conforme necessário
    printf("Numero lido: %d\n", numeroLido);

    fclose(arquivo);
}

// Função para criar um novo elemento da lista encadeada
Elemento *criarElemento(int chave)
{
    Elemento *novoElemento = (Elemento *)malloc(sizeof(Elemento)); // Aloca memória para um novo elemento
    if (novoElemento != NULL)
    {
        novoElemento->pessoa.chave = chave; // Define a chave do novo elemento
        novoElemento->proximo = NULL;       // Inicializa o próximo como NULL (final da lista)
    }
    return novoElemento; // Retorna o novo elemento criado
}

// Função para armazenar um elemento na memória, mantendo a ordem crescente pela chave
void armazenarDadosMemoria(Elemento **lista, Elemento *novoElemento)
{
    Elemento *elementoAtual = *lista;
    Elemento *elementoAnterior = NULL;

    // Encontra o local correto na lista para inserir o novo elemento mantendo a ordem crescente pela chave
    while (elementoAtual != NULL && elementoAtual->pessoa.chave < novoElemento->pessoa.chave)
    {
        elementoAnterior = elementoAtual;
        elementoAtual = elementoAtual->proximo;
    }

    if (elementoAnterior == NULL)
    {
        novoElemento->proximo = *lista; // Insere no início da lista
        *lista = novoElemento;
    }
    else
    {
        novoElemento->proximo = elementoAtual; // Insere no meio ou no final da lista
        elementoAnterior->proximo = novoElemento;
    }
}

// Função para gravar os dados em formato binário
void gravarDadosBinario(Elemento *lista, const char *nomeArquivo)
{
    FILE *arquivo = fopen(nomeArquivo, "wb"); // Abre o arquivo para escrita em binário
    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo %s\n", nomeArquivo);
        return;
    }

    Elemento *elementoAtual = lista;
    while (elementoAtual != NULL)
    {
        fwrite(&elementoAtual->pessoa.chave, sizeof(int), 1, arquivo); // Escreve a chave no arquivo binário
        elementoAtual = elementoAtual->proximo;
    }

    fclose(arquivo); // Fecha o arquivo após a escrita
    printf("Dados binarios gravados com sucesso no arquivo %s\n", nomeArquivo);
}

// Função para ler os dados de um arquivo de texto e criar uma lista encadeada a partir deles
Elemento *lerDadosTexto(const char *nomeArquivo)
{
    FILE *arquivo = fopen(nomeArquivo, "r"); // Abre o arquivo para leitura
    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo %s\n", nomeArquivo);
        return NULL;
    }

    Elemento *lista = NULL; // Inicializa a lista como vazia
    int chave;
    char nome[50];
    int idade;
    float altura;

    // Lê os dados do arquivo de texto e cria elementos na lista encadeada
    while (fscanf(arquivo, "Numero de cadastro: %d\nNome: %49[^\n]\nIdade: %d\nAltura: %f\n\n", &chave, nome, &idade, &altura) == 4)
    {
        Elemento *novoElemento = criarElemento(chave); // Cria um novo elemento com a chave lida
        if (novoElemento != NULL)
        {
            strcpy(novoElemento->pessoa.nome, nome);     // Copia o nome para o elemento
            novoElemento->pessoa.idade = idade;          // Define a idade do elemento
            novoElemento->pessoa.altura = altura;        // Define a altura do elemento
            armazenarDadosMemoria(&lista, novoElemento); // Armazena o novo elemento na lista
        }
    }

    fclose(arquivo); // Fecha o arquivo após a leitura
    return lista;    // Retorna a lista encadeada criada a partir dos dados do arquivo de texto
}

void liberarMemoria(Elemento *lista)
{
    Elemento *atual = lista;
    while (atual != NULL)
    {
        Elemento *proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }
}
