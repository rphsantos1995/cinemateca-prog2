# Universidade Federal do Rio de Janeiro
## Ciência da Computação

## RELATÓRIO DO TRABALHO DE PROGRAMAÇÃO DE COMPUTADORES II
### Cinemateca virtual

### Rio de Janeiro
### 4 de dezembro de 2024

**Autores:**

- João Manhães - 123485432
- Sara Mendes - 120172103
- Rodrigo Reis - 123585711
- Raphael Pereira - 123623802

## Sumário:

- A - Descrição resumida do problema
- B - Pseudocódigo do projeto
- C - Descrição dos casos de teste projetados
- D - Testes realizados e resultados obtidos
- E - Dificuldades encontradas
- F - Conclusão

---

## A. Descrição resumida do problema

Nosso projeto consiste em criar um programa que gerencia uma lista de filmes. Ele mantém uma lista encadeada, onde cada filme possui um ID, título, gênero, duração e nota. A lista é inicializada a partir de um arquivo binário ("catalogo.bin") que contém os filmes previamente salvos. O programa permite as seguintes operações:

- **Adicionar filme:** Insere um novo filme na lista com um ID único.
- **Exibir Tamanho da Lista:** Mostra o número de filmes na lista.
- **Remover filme:** Remove um produto da lista pelo ID.
- **Listar filmes:** Exibe todos os filmes na lista, ordenados por título.
- **Buscar filmes:** Procura um filme pelo genero ou id e exibe o(s) resultado(s).

## B. Pseudocódigo do projeto

### 1. Constantes e variáveis globais:
- **`Definir constantes:`**
  - verdadeiro = 1
  - falso = 0
- **`Definir variável global:`**
  - globalID = 0

### 2. Tipos de Dados:
- **Definindo tipos:**
  - FILME (ID, titulo, genero, duração e nota)
  - ELEMENTO (reg, prox)
  - LISTA (inicio)

### 3. Funções:

#### 3.1 `inicializarLista(lista)`
- abrir arquivo "catalogo.bin" para leitura
- se o arquivo existe:
  - enquanto ler o filme do arquivo:
    - criar novo elemento
    - atribuir filme para o elemento
    - adicionar o elemento no início da lista
  - fechar arquivo

#### 3.2 `tamanho(lista)`
- inicializar contador tam = 0
- para cada elemento na lista:
- incrementar +1 em tam
- retornar tam

#### 3.3 `exibirLista(lista)`
- ordena os elementos da lista com bubbleSortTitulo(lista)
- para cada um dos elementos na lista:
- imprimir detalhes do filme

#### 3.4 `atualizarCatalogo(lista)`
- abrir arquivo "catalogo.bin" para escrita
- para cada um dos elementos na lista
- escrever filme no arquivo
- fechar arquivo

#### 3.5 `adicionarFilme(lista)`
- criar novo elemento
- atribuir ID único ao filme
- salvar globalID
- registrar entrada do filme
- adicionar filme ao início da lista
- atualizar arquivo bin com atualizarCatalogo(LISTA* l)

#### 3.6 `removerFilme(lista, id)`
- encontrar elemento com o ID correspondente
- se elemento encontrado:
  - remover elemento da lista
  - registrar saída do produto
  - atualizar arquivo do catalogo
- senão:
  - imprimir "Filme não encontrado!"

#### 3.7 `buscarFilmePorNome(lista, titulo)`
- para cada elemento na lista:
  - se titulo do filme coincide:
    - imprimir detalhes do filme
  - se não encontrado:
    - imprimir "Nenhum filme encontrado com o nome"

#### 3.8 `buscarFilmePorGenero(lista, genero)`
- para cada elemento na lista:
  - se genero do filme coincide:
    - imprimir detalhes do filme
  - se não encontrado:
    - imprimir "Nenhum filme encontrado no gênero"

#### 3.9 `bubbleSortTitulo(lista)`
- se lista vazia:
  - retornar
- repetir até que não haja trocas:
  - para cada par de elementos consecutivos na lista:
    - se ordem alfabetica do primeiro for anterior ao segundo:
    - trocar elementos

#### 3.10 `menu()`
- imprimir as opções do menu

### 4. Main
- Inicializa variável lista tipo LISTA
- Inicializa a lista
- Inicializa a variável opcao
- Define fomatação de data pra pt-br
- Abre o menu

Se o usuário escolher:
1. Adicionar filme
	* Ler titulo, genero, duração e nota
	* inserir ou alterar filme na lista
2. Remover filme
	* Ler id do filme
	* remover filme da lista pelo `ID`
3. Exibir lista de filmes
4. Buscar filme por titulo
	* Ler titulo do filme
	* buscar filme pelo titulo
5. Buscar filme por genero
	* Ler genero do filme
	* buscar filme pelo genero
6. Sair do programa

## C. Descrição dos casos de teste projetados

### Teste adicionar filme
Ao selecionar a opção 1 (adicionar filme) o usuário deverá digitar o titulo do filme, genero, ano, duração e nota. Após isso o item deverá ser adicionado à lista que está ordenada por titulo junto com o seu ID próprio. Se a duração ou a nota for diferente de um numero, exibe a mensagem de filme não adicionado e encerra a chamada da função.

### Teste remover filme
Ao selecionar a opção 2 (remover filme) o usuário deverá digitar o ID do produto a ser removido. Após isso o item será removido da lista. Se o catalago não tiver o id do filme, deverá ser exibido em tela "filme não encontrado".

### Teste listar filmes
Ao selecionar a opção 3 (listar filmes) deverão ser listados todos os filmes do catalogo ordenados pelo título na lista, junto ao seu ID, genero, duração, ano e nota. Se o catalogo estiver vazio, não aparece nada.

### Teste buscar filme por titulo
Ao selecionar a opção 4 (buscar filme por titulo) o usuário deverá digitar o nome do filme a ser buscado. Após isso deverá ser mostrado o filme com suas informações. Se o filmenão for encontrado, deverá aparecer que o "Nenhum filme encontrado com o nome".

### Teste buscar filme por genero
Ao selecionar a opção 5 (buscar filme por genero) o usuário deverá digitar o genero a ser buscado. Após isso deverá ser mostrado o(s) filme(s) relativo(s) ao genero com suas informações. Se o genero não for encontrado, deverá aparecer que o "Nenhum filme encontrado no gênero".

## D. Testes realizados e resultados obtidos

Durante os testes de adição de filmes, obtivemos resultados satisfatórios. Os filmes foram adicionados à lista ordenados por titulo e com IDs únicos. Nos testes de remoção, também obtivemos os resultados esperados: os filmes foram removidos da lista, mantendo-a ordenada e descartando o ID correspondente. Quando o catalogo estava vazio, o programa retornou a mensagem "Lista vazia - sem elementos para remover".

Nos testes para retornar o tamanho da lista, os resultados foram positivos. O programa retornou o tamanho correto da lista, inclusive quando estava vazia (ou seja, 0). Nos testes de listagem de filmes, os resultados também foram positivos. Os filmes foram listados em ordem alfabética com suas informações.

Nos testes de busca, o programa respondeu corretamente. Quando digitado o nome de um filme presente no catalogo, retornou o filme relativo ao título ou o(s) filme(s) relativo(s) ao genero procurado. Quando o filme não estava no catalogo, retornou "filme não encontrado". Quando o catalogo estava vazio, a mensagem foi "sem elementos para buscar".

Nos testes de encerramento do programa, os resultados também foram positivos. O programa salvou corretamente o arquivo de catalogo.

## E. Dificuldades encontradas

A maior dificuldade que enfrentamos foi a mudança de tema num curto prazo tendo que adaptar o escopo do projeto que já estava em desenvolvimento. 

## F. Conclusão

O desenvolvimento deste programa de gerenciamento de catalogo tem como objetivo proporcionar uma solução eficaz para a administração de filmes. Através de uma lista encadeada, o programa permite a inserção, remoção, exibição e busca de filmes de forma eficiente e organizada.

O programa oferece uma maneira prática e automatizada reduzindo a possibilidade de erros humanos e aumentando a eficiência na gestão dos filmes catalogados. 
