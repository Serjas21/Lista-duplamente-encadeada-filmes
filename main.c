#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Usuario.h"

int main() {
    No** Lista = criarLista();
    int opcao;
    char email1[100], email2[100], senha[100], filme[100];

    carregarDados(Lista, "dados.txt");

    do {
        printf("\n========= SISTEMA DE USUARIOS E FILMES =========");
        printf("\n1. Cadastrar Usuario");
        printf("\n2. Adicionar Filme a um Usuario");
        printf("\n3. Remover Usuario");
        printf("\n4. Listar Tudo (Relatorio)");
        printf("\n5. Consultar Quantidade de Filmes");
        printf("\n6. Comparar Filmes entre dois Usuarios");
        printf("\n0. Sair");
        printf("\n================================================");
        printf("\nEscolha uma opcao: ");
        scanf("%d", &opcao);
        limparBuffer(); 

        switch (opcao) {
            case 1:
                printf("Email: ");
                fgets(email1, 100, stdin);
                email1[strcspn(email1, "\n")] = 0;
                printf("Senha: ");
                fgets(senha, 100, stdin);
                senha[strcspn(senha, "\n")] = 0;
                
                if (cadastrarUsuario(Lista, email1, senha)) 
                    printf("Usuario cadastrado!\n");
                break;

            case 2:
                printf("Email do usuario: ");
                fgets(email1, 100, stdin);
                email1[strcspn(email1, "\n")] = 0;
                printf("Nome do Filme: ");
                fgets(filme, 100, stdin);
                filme[strcspn(filme, "\n")] = 0;
                
                if (adicionarfilme(Lista, email1, filme))
                    printf("Filme adicionado com sucesso!\n");
                break;

            case 3:
                printf("Email do usuario a remover: ");
                fgets(email1, 100, stdin);
                email1[strcspn(email1, "\n")] = 0;
                
                if (removerUsuario(Lista, email1))
                    printf("Usuario removido.\n");
                else
                    printf("Usuario nao encontrado.\n");
                break;

            case 4:
                imprimirLista(Lista);
                break;

            case 5:
                printf("Email para consulta: ");
                fgets(email1, 100, stdin);
                email1[strcspn(email1, "\n")] = 0;
                quantidadeFilmes(Lista, email1);
                break;

            case 6:
                printf("Email do primeiro usuario: ");
                fgets(email1, 100, stdin);
                email1[strcspn(email1, "\n")] = 0;
                printf("Email do segundo usuario: ");
                fgets(email2, 100, stdin);
                email2[strcspn(email2, "\n")] = 0;
                filmesParecidos(Lista, email1, email2);
                break;

            case 0:
                printf("Saindo e liberando memoria...\n");
                break;

            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 0);

    liberar(Lista);
    return 0;
}