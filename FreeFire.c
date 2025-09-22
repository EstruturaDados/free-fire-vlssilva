#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Definição da struct Item para representar cada objeto coletado na mochila.
// Campos: nome (até 29 caracteres + null), tipo (até 19 caracteres + null), quantidade (inteiro positivo).
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// Vetor global para armazenar até 10 itens no inventário.
// Variável global para rastrear o número atual de itens cadastrados.
Item inventario[10];
int totalItens = 0;

// Função para inserir um novo item no inventário.
// Verifica se há espaço (máximo 10 itens) antes de adicionar.
// Usa scanf para ler strings (assumindo nomes e tipos sem espaços) e inteiro.
void inserirItem() {
    if (totalItens >= 10) {
        printf("Inventario cheio! Nao e possivel adicionar mais itens.\n");
        return;
    }
    
    Item novoItem;
    printf("Digite o nome do item (max 29 caracteres): ");
    scanf("%s", novoItem.nome);
    printf("Digite o tipo do item (ex: arma, municao, cura): ");
    scanf("%s", novoItem.tipo);
    printf("Digite a quantidade: ");
    scanf("%d", &novoItem.quantidade);
    
    // Validação básica: quantidade deve ser positiva.
    if (novoItem.quantidade <= 0) {
        printf("Quantidade invalida! Item nao adicionado.\n");
        return;
    }
    
    inventario[totalItens] = novoItem;
    totalItens++;
    printf("Item '%s' adicionado com sucesso!\n", novoItem.nome);
}

// Função para remover um item do inventário por nome.
// Realiza busca sequencial para encontrar o índice do item.
// Se encontrado, remove shiftando os itens subsequentes e decrementa totalItens.
void removerItem() {
    if (totalItens == 0) {
        printf("Inventario vazio! Nao ha itens para remover.\n");
        return;
    }
    
    char nomeBuscar[30];
    printf("Digite o nome do item a remover: ");
    scanf("%s", nomeBuscar);
    
    int indice = -1;
    // Busca sequencial para encontrar o item pelo nome.
    for (int i = 0; i < totalItens; i++) {
        if (strcmp(inventario[i].nome, nomeBuscar) == 0) {
            indice = i;
            break;
        }
    }
    
    if (indice == -1) {
        printf("Item '%s' nao encontrado no inventario.\n", nomeBuscar);
        return;
    }
    
    // Remove o item shiftando os elementos subsequentes.
    for (int i = indice; i < totalItens - 1; i++) {
        inventario[i] = inventario[i + 1];
    }
    
    totalItens--;
    printf("Item '%s' removido com sucesso!\n", nomeBuscar);
}

// Função para listar todos os itens no inventário.
// Percorre o vetor sequencialmente e exibe nome, tipo e quantidade de cada item.
// Chamada após operações de inserção e remoção para fornecer feedback.
void listarItens() {
    if (totalItens == 0) {
        printf("Inventario vazio!\n");
        return;
    }
    
    printf("\n--- LISTAGEM DO INVENTARIO (%d itens) ---\n", totalItens);
    for (int i = 0; i < totalItens; i++) {
        printf("Item %d: Nome: %s | Tipo: %s | Quantidade: %d\n",
               i + 1, inventario[i].nome, inventario[i].tipo, inventario[i].quantidade);
    }
    printf("---------------------------------------\n\n");
}

// Função para buscar um item no inventário por nome usando busca sequencial.
// Localiza o item e exibe seus dados se encontrado.
// Não remove ou altera o inventário, apenas consulta.
void buscarItem() {
    if (totalItens == 0) {
        printf("Inventario vazio! Nao ha itens para buscar.\n");
        return;
    }
    
    char nomeBuscar[30];
    printf("Digite o nome do item a buscar: ");
    scanf("%s", nomeBuscar);
    
    int encontrado = 0;
    // Busca sequencial para localizar o item pelo nome.
    for (int i = 0; i < totalItens; i++) {
        if (strcmp(inventario[i].nome, nomeBuscar) == 0) {
            printf("\n--- ITEM ENCONTRADO ---\n");
            printf("Nome: %s | Tipo: %s | Quantidade: %d\n",
                   inventario[i].nome, inventario[i].tipo, inventario[i].quantidade);
            printf("----------------------\n\n");
            encontrado = 1;
            break;  // Para de buscar após encontrar o primeiro (assumindo nomes únicos).
        }
    }
    
    if (!encontrado) {
        printf("Item '%s' nao encontrado no inventario.\n\n", nomeBuscar);
    }
}

int main() {
    int opcao;
    
    printf("=== SISTEMA DE INVENTARIO - MOCHILA DE LOOT ===\n");
    printf("Bem-vindo! Gerencie seus itens coletados no jogo.\n\n");
    
    // Menu principal em loop while para permitir múltiplas operações.
    while (1) {
        printf("Escolha uma opcao:\n");
        printf("1 - Cadastrar novo item\n");
        printf("2 - Remover item\n");
        printf("3 - Listar todos os itens\n");
        printf("4 - Buscar item por nome\n");
        printf("0 - Sair do jogo\n");
        printf("Opcao: ");
        scanf("%d", &opcao);
        
        switch (opcao) {
            case 1:
                inserirItem();
                listarItens();  // Listagem após inserção.
                break;
            case 2:
                removerItem();
                listarItens();  // Listagem após remoção.
                break;
            case 3:
                listarItens();  // Listagem direta.
                break;
            case 4:
                buscarItem();   // Busca exibe o item; listagem opcional, mas não obrigatória aqui.
                break;
            case 0:
                printf("Saindo do sistema. Boa sorte no jogo!\n");
                exit(0);  // Encerra o programa.
            default:
                printf("Opcao invalida! Tente novamente.\n\n");
        }
    }
    
    return 0;
}
