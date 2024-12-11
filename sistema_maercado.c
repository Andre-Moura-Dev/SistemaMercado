#include <stdio.h>
#include <string.h>

#define MAX_PRODUTOS 50 //Definição do máximo de produtos
#define MAX_CARRINHO 50 // Definição do máximo de produtos no carrinho

typedef struct {
    int codigo;
    char nome[30];
    float preco;
} Produto;

typedef struct {
    Produto produto;
    int quantidade;
} ItemCarrinho;

Produto produtos[MAX_PRODUTOS];
ItemCarrinho carrinho[MAX_CARRINHO];
int numProdutos = 0;
int numItensCarrinho = 0;

//Funções Para Gerenciamento do sistema
void menu();
void cadastrarProduto();
void listarProdutos();
void comprarProduto();
void visualizarCarrinho();
void fecharPedido();
int temNoCarrinho(int codigo);
Produto* pegarProdutoPorCodigo(int codigo);
void infoProduto(Produto prod);

int main() {
    menu();
    return 0;
}

void menu() {
    int opcao;
    do {
        printf("\n=== Menu do Supermercado ===\n");
        printf("1. Cadastrar Produto\n");
        printf("2. Listar Produtos\n");
        printf("3. Comprar Produto\n");
        printf("4. Visualizar Carrinho\n");
        printf("5. Fechar Pedido\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: cadastrarProduto(); break;
            case 2: listarProdutos(); break;
            case 3: comprarProduto(); break;
            case 4: visualizarCarrinho(); break;
            case 5: fecharPedido(); break;
            case 0: printf("Saindo do sistema...\n"); break;
            default: printf("Opcao invalida! Tente novamente.\n");
        }
    } while (opcao != 0);
}

void cadastrarProduto() {
    if (numProdutos >= MAX_PRODUTOS) {
        printf("Limite de produtos atingido!\n");
        return;
    }
    Produto p;
    printf("Codigo do produto: ");
    scanf("%d", &p.codigo);
    printf("Nome do produto: ");
    scanf(" %[^\n]", p.nome);
    printf("Preco do produto: ");
    scanf("%f", &p.preco);

    produtos[numProdutos++] = p;
    printf("Produto cadastrado com sucesso!\n");
}

void listarProdutos() {
    printf("\n=== Produtos Cadastrados ===\n");
    for (int i = 0; i < numProdutos; i++) {
        infoProduto(produtos[i]);
    }
}

void infoProduto(Produto prod) {
    printf("Codigo: %d, Nome: %s, Preco: %.2f\n", prod.codigo, prod.nome, prod.preco);
}

void comprarProduto() {
    int codigo;
    printf("Digite o codigo do produto que deseja comprar: ");
    scanf("%d", &codigo);
    Produto* p = pegarProdutoPorCodigo(codigo);

    if (p) {
        int index = temNoCarrinho(codigo);
        if (index != -1) {
            carrinho[index].quantidade++;
        } else {
            ItemCarrinho item;
            item.produto = *p;
            item.quantidade = 1;
            carrinho[numItensCarrinho++] = item;
        }
        printf("Produto adicionado ao carrinho.\n");
    } else {
        printf("Produto nao encontrado.\n");
    }
}

void visualizarCarrinho() {
    printf("\n=== Carrinho ===\n");
    if (numItensCarrinho == 0) {
        printf("Carrinho vazio.\n");
        return;
    }
    for (int i = 0; i < numItensCarrinho; i++) {
        printf("Produto: %s, Preco: %.2f, Quantidade: %d\n", carrinho[i].produto.nome, carrinho[i].produto.preco, carrinho[i].quantidade);
    }
}

void fecharPedido() {
    float total = 0;
    printf("\n=== Fatura ===\n");
    for (int i = 0; i < numItensCarrinho; i++) {
        float subtotal = carrinho[i].produto.preco * carrinho[i].quantidade;
        printf("Produto: %s, Quantidade: %d, Subtotal: %.2f\n", carrinho[i].produto.nome, carrinho[i].quantidade, subtotal);
        total += subtotal;
    }
    printf("Valor Total: %.2f\n", total);
    numItensCarrinho = 0; // Esvaziar carrinho
    printf("Pedido finalizado com sucesso!\n");
}

int temNoCarrinho(int codigo) {
    for (int i = 0; i < numItensCarrinho; i++) {
        if (carrinho[i].produto.codigo == codigo) {
            return i; // Retorna o índice do item no carrinho
        }
    }
    return -1; // Produto não está no carrinho
}

Produto* pegarProdutoPorCodigo(int codigo) {
    for (int i = 0; i < numProdutos; i++) {
        if (produtos[i].codigo == codigo) {
            return &produtos[i]; // Retorna o produto pelo seu código
        }
    }
    return NULL; // Produto não encontrado
}