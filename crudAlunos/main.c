#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _livro {
    char titulo[100];
    int num_paginas;
    float preco;
} Livro;

typedef struct _aluno {
    char nome[64];
    int idade;
    Livro *livro_favorito;
} Aluno;

// construtor para livros
Livro * createLivro(const char *titulo, int num_paginas, float preco) {
    Livro *livro = (Livro *) calloc(1, sizeof(Livro));
    strcpy(livro->titulo, titulo);
    livro->num_paginas = num_paginas;
    livro->preco = preco;
    return livro;
}

void printLivro (const Livro *livro) {
    printf("Titulo: %s\n", livro->titulo);
    printf("Numero de paginas: %d\n", livro->num_paginas);
    printf("Preco do livro: R$ %.2f\n", livro->preco);
}

void destroirLivro(Livro **livro_ref) {
    Livro *livro = *livro_ref;
    free(*livro_ref);
    *livro_ref = NULL;
}

Livro *copyLivro (const Livro *livro) {
    return createLivro(livro->titulo, livro->num_paginas, livro->preco);
}

Aluno *criarAluno (const char *nome, int idade, const Livro *livroAluno) {
    Aluno *aluno = (Aluno *)calloc(1, sizeof(Aluno));
    strcpy(aluno->nome, nome);
    aluno->idade = idade;
    aluno->livro_favorito = copyLivro(livroAluno);
}

void printAluno (const Aluno *aluno) {
    printf("Nome aluno: %s\n", aluno->nome);
    printf("Idade: %d\n", aluno->idade);
    puts("Livro favorito:\n");
    printLivro(aluno->livro_favorito);
}

void destroirAluno (Aluno **aluno_ref) {
    Aluno *aluno = *aluno_ref;
    destroirLivro(&aluno->livro_favorito);
    free(aluno);
    *aluno_ref = NULL;
}

void atualizarAluno(Aluno *aluno, const char *novo_nome, int nova_idade, Livro *novo_livro_favorito) {

    if (novo_nome != NULL && strlen(novo_nome) > 0) {
        strcpy(aluno->nome, novo_nome);
    }
    aluno->idade = nova_idade;
    destroirLivro(&aluno->livro_favorito);
    aluno->livro_favorito = copyLivro(novo_livro_favorito);
}

int main () {

    Livro *harryPotter = createLivro("Harry Potter e a Pedra Filosofal", 200, 25);
    Aluno *leonardo = criarAluno("Leonardo Roth", 19, harryPotter);

    printAluno(leonardo);
    printf("Endereço do livro favorito (copia) = %p. Endereço do livro original: %p\n",
    (void*)leonardo->livro_favorito, (void*)harryPotter);

    Livro *senhorDosAneis = createLivro("O Senhor dos Anéis", 300, 50);
    atualizarAluno(leonardo, "Leonardo Vitor Roth", 19, senhorDosAneis);

    puts("\nApós a atualização:\n");
    printAluno(leonardo);
    printf("Endereço do novo livro favorito (copia) = %p. Endereço do livro original: %p\n",
    (void*)leonardo->livro_favorito, (void*)senhorDosAneis);

    destroirLivro(&harryPotter);
    destroirLivro(&senhorDosAneis);
    destroirAluno(&leonardo);

    return 0;
}