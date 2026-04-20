#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Usuario.h"

// --- CARREGAR DADOS ---
void carregarDados(No** li, char* nomeArquivo) {
    FILE* arq = fopen(nomeArquivo, "r"); 
    if (arq == NULL) {
        printf("Erro ao abrir o arquivo %s\n", nomeArquivo);
        return;
    }

    char linha[256];
    while (fgets(linha, sizeof(linha), arq)) { 
        linha[strcspn(linha, "\n")] = 0; // Localiza o \n e o substitui por \0 (fim de string)

        char* tipo = strtok(linha, "-");    // Pega o primeiro token (U ou F)
        char* campo1 = strtok(NULL, "-");  // Pega o segundo (Email)
        char* campo2 = strtok(NULL, "-");  // Pega o terceiro (Senha ou Filme)

        if (tipo != NULL && campo1 != NULL && campo2 != NULL) {
            if (strcmp(tipo, "U") == 0) {
                cadastrarUsuario(li, campo1, campo2); // Chama cadastro de usuário
            } else if (strcmp(tipo, "F") == 0) {
                adicionarfilme(li, campo1, campo2);   // Chama adição de filme
            }
        }
    }
    fclose(arq); // Fecha o arquivo
    printf("Dados carregados com sucesso!\n");
}


No** criarLista(){
    No** li = (No**)malloc(sizeof(No*)); // Aloca o ponteiro duplo na Heap
    if(li != NULL){
        *li = NULL; 
    }
    return li;
}


int cadastrarUsuario(No** li, char* email, char* senha){
    if(li == NULL) return 0;
    
    No* atual = *li;
    // Percorre a lista para ver se o email já existe (evita duplicados)
    while(atual != NULL){
        if(strcmp(atual->dados.email, email) == 0){
            printf("\nO usuario %s ja existe\n", email);
            return 0;
        }
        atual = atual->prox;
    }

    // Aloca o novo nó do usuário
    No* novo = (No*)malloc(sizeof(No));
    if(novo == NULL) return 0;

    strcpy(novo->dados.email, email); 
    strcpy(novo->dados.senha, senha); 
    novo->dados.listafilmes = NULL;   
    
    
    novo->prox = *li;
    novo->ant = NULL;
    if(*li != NULL){
        (*li)->ant = novo; // O antigo primeiro nó agora aponta para o novo
    }
    *li = novo; // O ponteiro principal da lista agora aponta para o novo nó
    return 1;
}


int adicionarfilme(No** li, char* email, char* nomefil){
    if(li == NULL) return 0;
    
    No* atual = *li;
    while(atual != NULL && strcmp(atual->dados.email, email) != 0){
        atual = atual->prox;
    }

    if(atual == NULL){
        printf("O usuario %s nao existe\n", email);
        return 0;
    }

    Filmes* Novo = (Filmes*)malloc(sizeof(Filmes));
    if(Novo == NULL) return 0;

    strcpy(Novo->nome, nomefil);
    Novo->prox = atual->dados.listafilmes;
    Novo->ant = NULL;
    if(atual->dados.listafilmes != NULL){
        atual->dados.listafilmes->ant = Novo;
    }
    atual->dados.listafilmes = Novo;
    return 1;
}

void imprimirLista(No** li) {
    if (li == NULL || *li == NULL) {
        printf("\nA lista de usuarios esta vazia.\n");
        return;
    }
    No* atual = *li;
    while(atual != NULL){ // Percorre os usuários
        printf("\n-----------------------------------------------------\n");
        printf("Usuario: %s\n", atual->dados.email);
        printf("Filmes assistidos:\n");
        
        Filmes* atualfilmes = atual->dados.listafilmes;
        if(atualfilmes == NULL) printf("nenhum filme assistido\n");

        while(atualfilmes != NULL){ // Percorre os filmes do usuário atual
            printf("- %s\n", atualfilmes->nome);
            atualfilmes = atualfilmes->prox;
        }
        printf("-----------------------------------------------------\n");
        atual = atual->prox;
    }
}

int removerUsuario(No** li, char* email){
    if(li == NULL || *li == NULL) return 0;

    No* atual = *li;
    while(atual != NULL && strcmp(atual->dados.email, email) != 0){
        atual = atual->prox;
    }

    if(atual == NULL) return 0;

    // Ajusta o ponteiro do nó anterior ou o início da lista
    if(atual->ant == NULL) *li = atual->prox; 
    else atual->ant->prox = atual->prox;

    // Ajusta o ponteiro do nó próximo
    if(atual->prox != NULL) atual->prox->ant = atual->ant;

    // Libera a sublista de filmes do usuário antes de removê-lo
    Filmes* atualfilmes = atual->dados.listafilmes;
    while(atualfilmes != NULL){
        Filmes* aux = atualfilmes;
        atualfilmes = atualfilmes->prox;
        free(aux); // Libera cada filme
    }
    free(atual); // Libera o nó do usuário
    return 1;
}

int quantidadeFilmes(No** li, char* email){
    int somador = 0;
    if(li == NULL || *li == NULL) return 0;

    No* atual = *li;
    while(atual != NULL && strcmp(atual->dados.email, email) != 0){
        atual = atual->prox;
    }

    if(atual == NULL){
        printf("Usuario %s nao existe.",email);
        return 0;
    }

    Filmes* lista = atual->dados.listafilmes;
    while(lista != NULL){
        somador++;
        lista = lista->prox;
    }
    printf("\nO usuario %s assistiu %d filmes\n", email, somador);
    return 1;
}

int filmesParecidos(No** li, char* email1, char* email2){
    int somador = 0;
    if(li == NULL || *li == NULL) return 0;

    No* atual = *li;
    No* aux = *li;
    // Localiza os dois usuários
    while(atual != NULL && strcmp(atual->dados.email, email1) != 0) atual = atual->prox;
    while(aux != NULL && strcmp(aux->dados.email, email2) != 0) aux = aux->prox;

    if(atual == NULL || aux == NULL){
        printf("Um dos usuarios nao existe.");
        return 0;
    }
    Filmes* lista = atual->dados.listafilmes;
    // Laço aninhado: para cada filme do User1, percorre todos os do User2
    while(lista != NULL){
        Filmes* lista2 = aux->dados.listafilmes;
        while(lista2 != NULL){
            if(strcmp(lista->nome, lista2->nome) == 0){
                somador++; // Encontrou um filme com o mesmo nome
                break; // Sai do laço interno para testar o próximo filme da lista 1
            }
            lista2 = lista2->prox;
        }
        lista = lista->prox;
    }
    printf("\nos filmes iguais de %s e %s sao %d\n", email1, email2, somador);
    return 1;
}

// --- LIBERAR TODA A MEMÓRIA ---
void liberar(No** li) {
    if (li == NULL) return; 

    No* atual = *li;
    while (atual != NULL) {
        // Primeiro: libera a sublista de filmes
        Filmes* atualFilme = atual->dados.listafilmes;
        while (atualFilme != NULL) {
            Filmes* auxFilme = atualFilme;
            atualFilme = atualFilme->prox;
            free(auxFilme);
        }
        // Segundo: guarda o próximo e libera o nó do usuário
        No* auxUsuario = atual;
        atual = atual->prox;
        free(auxUsuario);
    }
    // Terceiro: Libera o ponteiro duplo alocado no criarLista()
    free(li); 
}
    void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
