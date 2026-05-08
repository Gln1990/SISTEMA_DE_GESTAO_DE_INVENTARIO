#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h> // Para aceitar acentos

#define MAX_EQUIPAMENTOS 50

// 1. Definição da Estrutura
typedef struct {
    int id;
    char modelo[50];
    char numSerie[30];
    int status; // 1: Disponível, 2: Manutenção, 3: Alocado
} Notebook;

// 2. Protótipos das Funções (Avisando o C que elas existem)
void cadastrar(Notebook lista[], int *total);
void listar(Notebook lista[], int total);
void buscar(Notebook lista[], int total);
void alterarStatus(Notebook lista[], int total);

int main() {
    // Configura o terminal para aceitar acentos (útil para o portfólio no Brasil)
    setlocale(LC_ALL, "Portuguese");

    Notebook inventario[MAX_EQUIPAMENTOS];
    int totalEquipamentos = 0;
    int opcao;

    do {
        printf("\n========================================");
        printf("\n   SISTEMA DE GESTÃO DE INVENTÁRIO");
        printf("\n========================================");
        printf("\n1. Cadastrar Novo Notebook");
        printf("\n2. Listar Todo Inventário");
        printf("\n3. Buscar por Número de Série");
        printf("\n4. Alterar Status de Equipamento");
        printf("\n0. Sair");
        printf("\n----------------------------------------");
        printf("\nEscolha uma opção: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                cadastrar(inventario, &totalEquipamentos);
                break;
            case 2:
                listar(inventario, totalEquipamentos);
                break;
            case 3:
                buscar(inventario, totalEquipamentos);
                break;
            case 4:
                alterarStatus(inventario, totalEquipamentos);
                break;
            case 0:
                printf("\nEncerrando o sistema...\n");
                break;
            default:
                printf("\n[AVISO] Opção inválida!\n");
        }
    } while(opcao != 0);

    return 0;
}

// --- Implementação das Funções ---

void cadastrar(Notebook lista[], int *total) {
    if (*total >= MAX_EQUIPAMENTOS) {
        printf("\n[ERRO] Limite de armazenamento atingido!\n");
        return;
    }

    lista[*total].id = *total + 1;

    printf("\nDigite o modelo (ex: Lenovo L14): ");
    scanf(" %[^\n]s", lista[*total].modelo);

    printf("Digite o número de série: ");
    scanf(" %s", lista[*total].numSerie);

    lista[*total].status = 1; // Padrão: Disponível

    (*total)++;
    printf("\n[SUCESSO] Notebook cadastrado com ID: %d\n", lista[*total-1].id);
}

void listar(Notebook lista[], int total) {
    if (total == 0) {
        printf("\n[INFO] Nenhum equipamento cadastrado ainda.\n");
        return;
    }

    printf("\n%-4s | %-20s | %-15s | %s", "ID", "MODELO", "SÉRIE", "STATUS");
    printf("\n------------------------------------------------------------");
    for (int i = 0; i < total; i++) {
        printf("\n%03d  | %-20s | %-15s | ", lista[i].id, lista[i].modelo, lista[i].numSerie);

        if(lista[i].status == 1) printf("Disponível");
        else if(lista[i].status == 2) printf("Manutenção");
        else printf("Alocado");
    }
    printf("\n");
}

void buscar(Notebook lista[], int total) {
    char termo[30];
    int encontrado = 0;

    printf("\nDigite o S/N para busca: ");
    scanf(" %s", termo);

    for (int i = 0; i < total; i++) {
        if (strcmp(lista[i].numSerie, termo) == 0) {
            printf("\n[LOCALIZADO] ID: %d | Modelo: %s | Status Atual: %d",
                    lista[i].id, lista[i].modelo, lista[i].status);
            encontrado = 1;
            break;
        }
    }
    if (!encontrado) printf("\n[AVISO] Equipamento não encontrado.\n");
}

void alterarStatus(Notebook lista[], int total) {
    int idBusca, novoStatus;
    printf("\nDigite o ID do notebook para alterar o status: ");
    scanf("%d", &idBusca);

    for (int i = 0; i < total; i++) {
        if (lista[i].id == idBusca) {
            printf("Status atual: %d", lista[i].status);
            printf("\nNovo Status (1-Disp, 2-Manut, 3-Alocado): ");
            scanf("%d", &novoStatus);
            lista[i].status = novoStatus;
            printf("\n[OK] Status atualizado!");
            return;
        }
    }
    printf("\n[ERRO] ID não encontrado.");
}
