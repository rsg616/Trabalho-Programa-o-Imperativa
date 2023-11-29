#include "gerador.h"
#include "editor.h"
#include "exportador.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Aqui está a função para ler um valor inteiro validado do arquivo 
int lerInteiroValidado(FILE *arquivo);

// Função para liberar memória alocada para a lista encadeada
void liberarMemoriaLista(Elemento *lista)
{
    Elemento *atual = lista;
    while (atual != NULL)
    {
        Elemento *proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }
}

// Função para inserir um novo elemento na lista(pessoas e suas respectivas informações)
void inserirElemento(Elemento **lista, Pessoa pessoas[], int *quantidade)
{
    int chave;
    printf("Digite o numero de cadastro da pessoa a ser inserida: ");
    scanf("%d", &chave);

    // Verifica se a chave já existe na lista
    Elemento *atual = *lista;
    while (atual != NULL)
    {
        if (atual->pessoa.chave == chave)
        {
            printf("Erro: Chave duplicada. Insira uma chave unica.\n");
            return;
        }
        atual = atual->proximo;
    }

    // Verifica se a quantidade máxima de pessoas já foi atingida
    if (*quantidade >= 100)
    {
        printf("Erro: Limite maximo de pessoas atingido.\n");
        return;
    }

    // Cria um novo elemento e insere na lista
    Elemento *novoElemento = criarElemento(chave);
    if (novoElemento != NULL)
    {
        printf("Digite o nome: ");
        scanf(" %[^\n]", novoElemento->pessoa.nome);
        printf("Digite a idade: ");
        novoElemento->pessoa.idade = lerInteiroValidado(stdin);
        printf("Digite a altura: ");
        scanf("%f", &novoElemento->pessoa.altura);

        // Armazena na lista mantendo a ordem crescente pela chave
        armazenarDadosMemoria(lista, novoElemento);

        // Atualiza o array de pessoas
        int indice = chave - 1;
        pessoas[indice] = novoElemento->pessoa;

        // Incrementa a quantidade de elementos
        (*quantidade)++;
        printf("Pessoa inserida com sucesso!\n");
    }
}

// Função para remover um elemento da lista por sua chave
void removerElemento(Elemento **lista, int chave)
{
    printf("Removendo pessoa com numero de cadastro %d\n", chave);
    Elemento *elementoAtual = *lista;  // Aponta para o início da lista
    Elemento *elementoAnterior = NULL; // Mantém o elemento anterior ao atual

    // Procura o elemento com a chave especificada na lista
    while (elementoAtual != NULL && elementoAtual->pessoa.chave != chave)
    {
        elementoAnterior = elementoAtual;       // Atualiza o elemento anterior
        elementoAtual = elementoAtual->proximo; // Avança para o próximo elemento
    }

    if (elementoAtual != NULL)
    {
        // Remove o elemento encontrado da lista
        if (elementoAnterior == NULL)
        {
            *lista = elementoAtual->proximo; // Se for o primeiro elemento, atualiza a cabeça da lista
        }
        else
        {
            elementoAnterior->proximo = elementoAtual->proximo; // Remove o elemento ajustando os ponteiros
        }

        free(elementoAtual); // Libera a memória do elemento removido da lista(memoria heap)
        printf("Pessoa com numero de cadastro %d removido\n", chave);
    }
    else
    {
        printf("Pessoa com numero de cadastro %d nao encontrado na lista.\n", chave);
    }

    // Verificação da lista após remoção
    Elemento *temp = *lista; // Inicia no início da lista novamente
    printf("Lista apos remocao: ");
    while (temp != NULL)
    {
        printf("%d -> ", temp->pessoa.chave); // Imprime as chaves na lista após a remoção
        temp = temp->proximo;                 // Avança para o próximo elemento
    }
    printf("NULL\n"); // Indica o fim da lista
}

// Função auxiliar para exibir um elemento recursivamente por sua chave
void exibirElemento(Elemento *lista, int chave)
{
    Elemento *elementoEncontrado = buscarElementoRecursivo(lista, chave);

    if (elementoEncontrado != NULL)
    {
        printf("Numero de Cadastro: %d\n", elementoEncontrado->pessoa.chave);
        printf("Nome: %s\n", elementoEncontrado->pessoa.nome);
        printf("Idade: %d\n", elementoEncontrado->pessoa.idade);
        printf("Altura: %.2f\n\n", elementoEncontrado->pessoa.altura);
    }
    else
    {
        printf("Pessoa com o Numero de Cadastro %d nao encontrado na lista.\n", chave);
    }
}

// Função para editar dados na lista, arquivo binário e arquivo de texto
void editarDados(Elemento **lista, const char *nomeArquivoBinario, const char *nomeArquivoTexto)
{
    int opcao;
    const int quantidade_maxima = 100; // Defina a quantidade máxima de pessoas aqui
    Pessoa pessoas[quantidade_maxima];
    int quantidade = 0; // Inicialização da variável quantidade

    // Gera dados iniciais
    gerarDados(pessoas, quantidade_maxima);

    do
    {
        printf("1. Inserir elemento\n");
        printf("2. Remover elemento\n");
        printf("3. Gerar arquivo binario e arquivo de texto\n");
        printf("4. Exibir dados de uma especifica\n");
        printf("5. Sair\n");
        printf("Digite a opcao desejada: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            printf("Digite o numero de cadastro da pessoa a ser inserida: ");
            int chave;
            scanf("%d", &chave);
            inserirElemento(lista, pessoas, &quantidade);
            break;

        case 2:
            printf("Digite o numero de cadastro da pessoa a ser removida: ");
            int chave_remover;
            scanf("%d", &chave_remover);
            removerElemento(lista, chave_remover);
            break;
        case 3:
            gravarDadosBinario(*lista, nomeArquivoBinario);
            exportarListaParaTexto(nomeArquivoTexto, *lista, pessoas);
            printf("Arquivo binario e arquivo de texto gerados.\n");
            break;
        case 4:
            printf("Digite o numero de cadastro da pessoa a ser exibida: ");
            int chave_exibir;
            scanf("%d", &chave_exibir);
            exibirElemento(*lista, chave_exibir);
            break;
        case 5:
            printf("Saindo...\n");
            break;
        default:
            printf("Opcao invalida. Tente novamente.\n");
        }
    } while (opcao != 5);

    liberarMemoriaLista(*lista); // Liberar memória alocada para a lista
}


// Função recursiva para buscar um elemento na lista por chave
Elemento* buscarElementoRecursivo(Elemento* elemento, int chave)
{
    if (elemento == NULL)
    {
        return NULL; // Elemento não encontrado
    }

    if (elemento->pessoa.chave == chave)
    {
        return elemento; // Elemento encontrado
    }

    return buscarElementoRecursivo(elemento->proximo, chave); // Chamada recursiva para o próximo elemento
}
