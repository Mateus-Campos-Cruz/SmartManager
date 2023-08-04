#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CLIENTES 100
#define MAX_PRODUTOS 100
#define MAX_PEDIDOS 100

// Definição das structs
typedef struct {
    int id;
    char nome[50];
    char endereco[100];
    char telefone[15];
} Cliente;

typedef struct {
    int codigo;
    char descricao[50];
    float preco;
} Produto;

typedef struct {
    int numero;
    int cliente_id;
    int produto_codigo;
    int quantidade;
} Pedido;

// Variáveis globais
Cliente *clientes = NULL;
Produto *produtos = NULL;
Pedido *pedidos = NULL;

int num_clientes = 0;
int num_produtos = 0;
int num_pedidos = 0;

// Função para limpar o buffer do teclado
void limpar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Função para adicionar um cliente
void adicionar_cliente() {
    if (num_clientes < MAX_CLIENTES) {
        Cliente cliente;

        printf("Digite o nome do cliente: ");
        fgets(cliente.nome, sizeof(cliente.nome), stdin);
        cliente.nome[strcspn(cliente.nome, "\n")] = '\0';

        printf("Digite o endereco do cliente: ");
        fgets(cliente.endereco, sizeof(cliente.endereco), stdin);
        cliente.endereco[strcspn(cliente.endereco, "\n")] = '\0';

        printf("Digite o telefone do cliente: ");
        fgets(cliente.telefone, sizeof(cliente.telefone), stdin);
        cliente.telefone[strcspn(cliente.telefone, "\n")] = '\0';

        cliente.id = num_clientes + 1;

        clientes = (Cliente *)realloc(clientes, (num_clientes + 1) * sizeof(Cliente));
        clientes[num_clientes] = cliente;
        num_clientes++;

        printf("Cliente adicionado com sucesso!\n");
    } else {
        printf("Numero maximo de clientes atingido.\n");
    }
}

// Função para adicionar um produto
void adicionar_produto() {
    if (num_produtos < MAX_PRODUTOS) {
        Produto produto;

        printf("Digite o codigo do produto: ");
        scanf("%d", &produto.codigo);
        limpar_buffer();

        printf("Digite a descricao do produto: ");
        fgets(produto.descricao, sizeof(produto.descricao), stdin);
        produto.descricao[strcspn(produto.descricao, "\n")] = '\0';

        printf("Digite o preco do produto: ");
        scanf("%f", &produto.preco);
        limpar_buffer();

        produtos = (Produto *)realloc(produtos, (num_produtos + 1) * sizeof(Produto));
        produtos[num_produtos] = produto;
        num_produtos++;

        printf("Produto adicionado com sucesso!\n");
    } else {
        printf("Numero maximo de produtos atingido.\n");
    }
}

// Função para fazer um pedido
void fazer_pedido() {
    if (num_clientes == 0 || num_produtos == 0) {
        printf("Nao ha clientes ou produtos cadastrados.\n");
        return;
    }

    if (num_pedidos < MAX_PEDIDOS) {
        Pedido pedido;
        int cliente_id, produto_codigo;

        printf("Digite o ID do cliente que esta fazendo o pedido: ");
        scanf("%d", &cliente_id);
        limpar_buffer();

        // Verifica se o ID do cliente é válido
        if (cliente_id < 1 || cliente_id > num_clientes) {
            printf("ID de cliente invalido.\n");
            return;
        }

        printf("Digite o codigo do produto: ");
        scanf("%d", &produto_codigo);
        limpar_buffer();

        // Verifica se o código do produto é válido
        int produto_index = -1;
        for (int i = 0; i < num_produtos; i++) {
            if (produtos[i].codigo == produto_codigo) {
                produto_index = i;
                break;
            }
        }

        if (produto_index == -1) {
            printf("Codigo de produto invalido.\n");
            return;
        }

        printf("Digite a quantidade: ");
        scanf("%d", &pedido.quantidade);
        limpar_buffer();

        if (pedido.quantidade <= 0) {
            printf("Quantidade invalida.\n");
            return;
        }

        pedido.numero = num_pedidos + 1;
        pedido.cliente_id = cliente_id;
        pedido.produto_codigo = produto_codigo;

        pedidos = (Pedido *)realloc(pedidos, (num_pedidos + 1) * sizeof(Pedido));
        pedidos[num_pedidos] = pedido;
        num_pedidos++;

        printf("Pedido adicionado com sucesso!\n");
    } else {
        printf("Numero maximo de pedidos atingido.\n");
    }
}

// Função para exibir os clientes cadastrados
void exibir_clientes() {
    printf("---- CLIENTES CADASTRADOS ----\n");
    for (int i = 0; i < num_clientes; i++) {
        printf("ID: %d\n", clientes[i].id);
        printf("Nome: %s\n", clientes[i].nome);
        printf("Endereco: %s\n", clientes[i].endereco);
        printf("Telefone: %s\n", clientes[i].telefone);
        printf("-----------------------\n");
    }
}

// Função para exibir os produtos cadastrados
void exibir_produtos() {
    printf("---- PRODUTOS CADASTRADOS ----\n");
    for (int i = 0; i < num_produtos; i++) {
        printf("Codigo: %d\n", produtos[i].codigo);
        printf("Descricao: %s\n", produtos[i].descricao);
        printf("Preco: R$ %.2f\n", produtos[i].preco);
        printf("-----------------------\n");
    }
}

// Função para exibir os pedidos realizados
void exibir_pedidos() {
    printf("---- PEDIDOS REALIZADOS ----\n");
    for (int i = 0; i < num_pedidos; i++) {
        printf("Numero do Pedido: %d\n", pedidos[i].numero);
        printf("ID do Cliente: %d\n", pedidos[i].cliente_id);
        printf("Codigo do Produto: %d\n", pedidos[i].produto_codigo);
        printf("Quantidade: %d\n", pedidos[i].quantidade);
        printf("-----------------------\n");
    }
}

// Função para exibir o menu
void exibir_menu() {
    printf("------ MENU ------\n");
    printf("1. Adicionar Cliente\n");
    printf("2. Adicionar Produto\n");
    printf("3. Fazer Pedido\n");
    printf("4. Exibir Clientes\n");
    printf("5. Exibir Produtos\n");
    printf("6. Exibir Pedidos\n");
    printf("7. Sair\n");
    printf("-------------------\n");
}

// Função para salvar os dados em arquivos binários
void salvar_dados() {
    FILE *arquivo_clientes = fopen("clientes.dat", "wb");
    if (arquivo_clientes) {
        fwrite(&num_clientes, sizeof(int), 1, arquivo_clientes);
        fwrite(clientes, sizeof(Cliente), num_clientes, arquivo_clientes);
        fclose(arquivo_clientes);
    }

    FILE *arquivo_produtos = fopen("produtos.dat", "wb");
    if (arquivo_produtos) {
        fwrite(&num_produtos, sizeof(int), 1, arquivo_produtos);
        fwrite(produtos, sizeof(Produto), num_produtos, arquivo_produtos);
        fclose(arquivo_produtos);
    }

    FILE *arquivo_pedidos = fopen("pedidos.dat", "wb");
    if (arquivo_pedidos) {
        fwrite(&num_pedidos, sizeof(int), 1, arquivo_pedidos);
        fwrite(pedidos, sizeof(Pedido), num_pedidos, arquivo_pedidos);
        fclose(arquivo_pedidos);
    }
}

// Função para carregar os dados dos arquivos binários
void carregar_dados() {
    FILE *arquivo_clientes = fopen("clientes.dat", "rb");
    if (arquivo_clientes) {
        fread(&num_clientes, sizeof(int), 1, arquivo_clientes);
        clientes = (Cliente *)malloc(num_clientes * sizeof(Cliente));
        fread(clientes, sizeof(Cliente), num_clientes, arquivo_clientes);
        fclose(arquivo_clientes);
    }

    FILE *arquivo_produtos = fopen("produtos.dat", "rb");
    if (arquivo_produtos) {
        fread(&num_produtos, sizeof(int), 1, arquivo_produtos);
        produtos = (Produto *)malloc(num_produtos * sizeof(Produto));
        fread(produtos, sizeof(Produto), num_produtos, arquivo_produtos);
        fclose(arquivo_produtos);
    }

    FILE *arquivo_pedidos = fopen("pedidos.dat", "rb");
    if (arquivo_pedidos) {
        fread(&num_pedidos, sizeof(int), 1, arquivo_pedidos);
        pedidos = (Pedido *)malloc(num_pedidos * sizeof(Pedido));
        fread(pedidos, sizeof(Pedido), num_pedidos, arquivo_pedidos);
        fclose(arquivo_pedidos);
    }
}

// Função para liberar a memória alocada pelas structs
void liberar_memoria() {
    free(clientes);
    free(produtos);
    free(pedidos);
}

int main() {
    carregar_dados();

    int opcao;

    while (1) {
        system("cls"); // Para Windows
        //system("clear"); // Para Linux/Mac

        // Configuração de cores
        printf("\033[0m"); // Volta para cor padrão do terminal

        exibir_menu();

        printf("Digite a opcao desejada: ");
        scanf("%d", &opcao);
        limpar_buffer();

        switch (opcao) {
            case 1:
                adicionar_cliente();
                break;
            case 2:
                adicionar_produto();
                break;
            case 3:
                fazer_pedido();
                break;
            case 4:
                exibir_clientes();
                break;
            case 5:
                exibir_produtos();
                break;
            case 6:
                exibir_pedidos();
                break;
            case 7:
                salvar_dados();
                liberar_memoria();
                printf("Saindo do programa...\n");
                exit(0);
            default:
                printf("Opcao invalida.\n");
                break;
        }

        // Pausa para visualização dos resultados
        printf("\nPressione ENTER para continuar...\n");
        limpar_buffer();
    }

    return 0;
}
