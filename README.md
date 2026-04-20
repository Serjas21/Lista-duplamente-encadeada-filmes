
# 🎬 CineList Manager - Sistema de Gerenciamento de Filmes

Este é um sistema desenvolvido em C que utiliza estruturas de dados dinâmicas para gerenciar usuários e suas respectivas listas de filmes assistidos. O projeto foca no uso eficiente de memória e na organização modular de código.

## 📌 Visão Geral do Projeto

O programa resolve o problema de armazenamento de perfis de usuários onde cada perfil possui uma lista de tamanho variável (filmes). Em vez de usar arrays estáticos, o sistema utiliza listas duplamente encadeadas heterogêneas.



## 🛠️ Estrutura de Dados

O projeto está organizado da seguinte forma:
- **Lista Principal:** Uma lista duplamente encadeada onde cada nó representa um `Usuario`.
- **Sublista:** Cada usuário possui um ponteiro para sua própria lista duplamente encadeada de `Filmes`.

Esta arquitetura permite:
1. Inserção e remoção rápida de usuários.
2. Cada usuário ter um número ilimitado de filmes (limitado apenas pela memória RAM).
3. Navegação bidirecional em ambas as listas (ponteiros `prox` e `ant`).

## 🚀 Funcionalidades

- **Carga de Dados:** Lê um arquivo `dados.txt` e popula o sistema automaticamente.
- **Gestão de Usuários:** Cadastro, busca e remoção completa (incluindo limpeza da sublista).
- **Gestão de Filmes:** Adiciona filmes específicos para cada conta de e-mail.
- **Análise de Afinidade:** Calcula quantos filmes dois usuários têm em comum.
- **Relatórios:** Exibe todos os usuários e seus respectivos filmes de forma organizada.

## 📂 Organização dos Arquivos

| Arquivo | Descrição |
| :--- | :--- |
| `main.c` | Ponto de entrada com o menu interativo para o usuário. |
| `Usuario.h` | Protótipos das funções e definições das `structs`. |
| `Usuario.c` | Implementação de toda a lógica de manipulação das listas. |
| `dados.txt` | Arquivo de persistência para carga inicial de teste. |

## 📄 Exemplo de Formatação do dados.txt
Para que o carregamento automático funcione, o arquivo deve seguir este padrão:

U-email-senha (Para Usuários)

F-email-nomeDoFilme (Para Filmes)
