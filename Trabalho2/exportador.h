#ifndef EXPORTADOR_H
#define EXPORTADOR_H

#include "gerador.h"

// Funções para exportar dados
void exportarParaBinario(const char *nomeArquivo, Pessoa *pessoas, int quantidade);
void exportarParaTexto(const char *nomeArquivo, Pessoa *pessoas, int quantidade);
void exportarListaParaTexto(const char *nomeArquivo, Elemento *lista, Pessoa pessoas[]);

#endif 
