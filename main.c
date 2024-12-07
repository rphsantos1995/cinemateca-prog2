#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>

#define true 1
#define false 0

typedef int bool;

int globalID = 0;

typedef struct {
    int ID;
    char titulo[100];
    char genero[50];
    int duracao; // minutos
    int ano;
    int nota;
} FILME;

typedef struct aux {
    FILME reg;
    struct aux* prox;
} ELEMENTO;

typedef ELEMENTO* PONT;

typedef struct {
    PONT inicio;
} LISTA;

void inicializarLista(LISTA* l) {
    l->inicio = NULL;
    FILE* arquivo = fopen("catalogo.bin", "rb");
    if (arquivo != NULL) {
        FILME filme;
        while (fread(&filme, sizeof(FILME), 1, arquivo)) {
            ELEMENTO* novo = (ELEMENTO*)malloc(sizeof(ELEMENTO));
            novo->reg = filme;
            novo->prox = l->inicio;
            l->inicio = novo;

            if (filme.ID >= globalID) {
                globalID = filme.ID + 1;
            }
        }
        fclose(arquivo);
    }
}

int tamanho(LISTA* l) {
    PONT end = l->inicio;
    int tam = 0;
    while (end != NULL) {
        tam++;
        end = end->prox;
    }
    return tam;
}

void atualizarCatalogo(LISTA* l) {
    FILE* arquivo = fopen("catalogo.bin", "wb");
    if (arquivo == NULL) return;

    PONT atual = l->inicio;
    while (atual != NULL) {
        fwrite(&atual->reg, sizeof(FILME), 1, arquivo);
        atual = atual->prox;
    }
    fclose(arquivo);
}

void bubbleSortTitulo(LISTA* l) {
    if (l->inicio == NULL || l->inicio->prox == NULL) {
        return;
    }

    bool ordenado;
    do {
        ordenado = false;
        PONT atual = l->inicio;
        PONT anterior = NULL;

        while (atual->prox != NULL) {
            PONT proximo = atual->prox;

            if (strcmp(atual->reg.titulo, proximo->reg.titulo) > 0) {
                if (anterior == NULL) {
                    l->inicio = proximo;
                } else {
                    anterior->prox = proximo;
                }

                atual->prox = proximo->prox;
                proximo->prox = atual;

                ordenado = true;
            }

            anterior = atual;
            atual = atual->prox;
        }
    } while (ordenado);
}

void exibirLista(LISTA* l) {
    bubbleSortTitulo(l);
    PONT end = l->inicio;
    printf("=============== Catálogo de Filmes ===============\n\n");
    while (end != NULL) {
        printf("ID: %d\n", end->reg.ID);
        printf("Título: %s\n", end->reg.titulo);
        printf("Gênero: %s\n", end->reg.genero);
        printf("Duração: %d minutos\n", end->reg.duracao);
        printf("Lançamento: %d\n", end->reg.ano);
        printf("Nota: %d\n", end->reg.nota);
        printf("-------------------------------------------\n");
        end = end->prox;
    }
    printf("==================================================\n\n");
}


void adicionarFilme(LISTA* l) {
    FILME filme;
    printf("=============== Adicionar Filme ===============\n\n");

    printf("Digite o título do filme: ");
    fgets(filme.titulo, sizeof(filme.titulo), stdin);
    filme.titulo[strcspn(filme.titulo, "\n")] = 0;
    
    for(int i = 0; filme.titulo[i] != '\0'; i++){
        filme.titulo[i] = toupper(filme.titulo[i]);
    }

    printf("Digite o gênero do filme: ");
    fgets(filme.genero, sizeof(filme.genero), stdin);
    filme.genero[strcspn(filme.genero, "\n")] = 0;
    
    for(int i = 0; filme.genero[i] != '\0'; i++){
        filme.genero[i] = toupper(filme.genero[i]);
    }

    printf("Digite a duração do filme (em minutos): ");
    if (scanf("%d", &filme.duracao) != 1) {
        printf("Entrada inválida! Filme não adicionado.\n");
        return;
    }
    getchar(); // Limpa o '\n' no buffer

    printf("Digite o ano de lançamento (aaaa): ");
    if (scanf("%d", &filme.ano) != 1) {
        printf("Entrada inválida! Filme não adicionado.\n");
        return;
    }
    
    getchar();
    
    printf("Digite a nota para o filme (1 a 10): ");
    if (scanf("%d", &filme.nota) != 1 || filme.nota < 1 || filme.nota > 10) {
        printf("Entrada inválida! Filme não adicionado.\n");
        return;
    }
    
    getchar(); // Limpa o '\n' no buffer
    
    filme.ID = globalID;
    globalID++;
    
    ELEMENTO* novo = (ELEMENTO*)malloc(sizeof(ELEMENTO));
    novo->reg = filme;
    novo->prox = l->inicio;
    l->inicio = novo;

    atualizarCatalogo(l);
    printf("\nFilme adicionado com sucesso!\n");
}

void removerFilme(LISTA* l, int id) {
    
    if(tamanho(l) < 1) {
        printf("Lista vazia - sem elementos para remover");
        return;
    }
    
    ELEMENTO* atual = l->inicio;
    ELEMENTO* anterior = NULL;
    
    
    while (atual != NULL && atual->reg.ID != id) {
        anterior = atual;
        atual = atual->prox;
    }

    if (atual != NULL) {
        if (anterior == NULL) {
            l->inicio = atual->prox;
        } else {
            anterior->prox = atual->prox;
        }

        free(atual);
        atualizarCatalogo(l);
        printf("\nFilme removido com sucesso!\n");
    } else {
        printf("\nFilme não encontrado! Tente outro ID.\n");
    }
}

void buscarFilmePorNome(LISTA *l, char *titulo) {
    
    if(tamanho(l) < 1) {
        printf("Lista vazia - sem elementos para buscar");
        return;
    }
    
    ELEMENTO *atual = l->inicio;
    bool encontrado = false;

    printf("=== Resultado da Busca por Nome ===\n\n");
    while (atual != NULL) {
        if (strcasecmp(atual->reg.titulo, titulo) == 0) {
            printf("ID: %d\n", atual->reg.ID);
            printf("Filme: %s\n", atual->reg.titulo);
            printf("Gênero: %s\n", atual->reg.genero);
            printf("Duração: %d minutos\n", atual->reg.duracao);
            printf("Nota: %d\n", atual->reg.nota);
            printf("-------------------------------------------\n");
            encontrado = true;
            break; 
        }
        atual = atual->prox;
    }

    if (!encontrado) {
        printf("Nenhum filme encontrado com o nome '%s'.\n", titulo);
    }
}

void buscarFilmePorGenero(LISTA *l, char *genero) {

    if(tamanho(l) < 1) {
        printf("Lista vazia - sem elementos para buscar");
        return;
    }    

    ELEMENTO *atual = l->inicio;
    bool encontrado = false;

    printf("=== Resultado da Busca por Gênero ===\n\n");
    while (atual != NULL) {
        if (strcasecmp(atual->reg.genero, genero) == 0) {
            printf("ID: %d\n", atual->reg.ID);
            printf("Filme: %s\n", atual->reg.titulo);
            printf("Gênero: %s\n", atual->reg.genero);
            printf("Duração: %d minutos\n", atual->reg.duracao);
            printf("Nota: %d\n", atual->reg.nota);
            printf("-------------------------------------------\n");
            encontrado = true;
        }
        atual = atual->prox;
    }

    if (!encontrado) {
        printf("Nenhum filme encontrado no gênero '%s'.\n", genero);
    }
}


void menu() {
    printf("\n=============== Menu de Opções ===============\n");
    printf("1. Adicionar Filme\n");
    printf("2. Remover Filme\n");
    printf("3. Catálogo de Filmes\n");
    printf("4. Buscar Filme por nome\n");
    printf("5. Buscar Filme por gênero\n");
    printf("6. Sair\n");
    printf("==============================================\n\n");
}

int main() {
    LISTA lista;
    inicializarLista(&lista);
    int opcao;
    setlocale(LC_ALL, "Portuguese");

   do {
        menu();
        printf("Digite a opção desejada: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1:
                adicionarFilme(&lista);
                break;
            case 2: {
                int id;
                printf("Digite o ID do filme a ser removido: ");
                scanf("%d", &id);
                getchar();
                removerFilme(&lista, id);
                break;
            }
            case 3:
                exibirLista(&lista);
                break;
                
            case 4: {
                printf("=============== Buscar Filme por nome  ===============\n\n");
                if (tamanho(&lista) == 0) {
                printf("Lista vazia - sem elementos para Buscar!\n\n");
                } else {
                    char nome[50];
                    printf("Digite o nome do Filme: ");
                    scanf("%s", nome);
                    buscarFilmePorNome(&lista, nome);
                    }
            }    
        
        case 5: {
            printf("=============== Buscar Filme por genero  ===============\n\n");
            if (tamanho(&lista) == 0) {
              printf("Lista vazia - sem elementos para Buscar!\n\n");
            } else {
                char genero[50];
                printf("Digite o nome do genero: ");
                scanf("%s", genero);
                buscarFilmePorGenero(&lista, genero);
                }   
            }   
             
        case 6:
            printf("Saindo...\n");
            break;
            
        default:
            printf("Opção inválida! Tente novamente.\n");
        }
    } while (opcao != 6);

    return 0;
}



