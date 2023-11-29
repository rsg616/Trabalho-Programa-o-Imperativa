#ifndef EDITOR_H
#define EDITOR_H

#include "gerador.h"

// Função para editar dados: lista, arquivo binário e arquivo de texto
void editarDados(Elemento** lista, const char* nomeArquivoBinario, const char* nomeArquivoTexto);
// Função recursiva para buscar um elemento na lista por chave
Elemento* buscarElementoRecursivo(Elemento* elemento, int chave);

#endif 
