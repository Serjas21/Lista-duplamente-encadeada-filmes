#ifndef USUARIO_H_
#define USUARIO_H_

struct filmes {
    char nome[100];         
    struct filmes* prox;    
    struct filmes* ant;     
};
typedef struct filmes Filmes; 


struct usuario {
    char email[100];        
    char senha[100];        
    Filmes* listafilmes;   
};
typedef struct usuario Usuario; 

struct no {
    Usuario dados;          
    struct no* prox;        
    struct no* ant;         
};
typedef struct no No;       


No** criarLista();
int cadastrarUsuario(No** li, char* email, char* senha);
int adicionarfilme(No** li, char* email, char* nome);
void imprimirLista(No** li);
int removerUsuario(No** li, char* email);
int quantidadeFilmes(No** li, char* email);
int filmesParecidos(No** li, char* email1, char* email2);
void liberar(No** li);
void carregarDados(No** li, char* nomeArquivo);
void limparBuffer();
#endif