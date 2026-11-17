#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_RESERVAS 10
#define CAPACIDADE_MAXIMA 10



typedef struct TReserva{
    char nome_cliente[50];
    int numero_pessoas;
    char data[20];
    char hora[10];
} TReserva;

// Soma as pessoas já reservadas numa data e hora (ignora a reserva "ignorar"; usa -1 para não ignorar nenhuma)
int PessoasNaDataHora(TReserva reservas[], int numReservas, char* data, char* hora, int ignorar) {
    int total = 0;

    for (int i = 0; i < numReservas; i++) {
        if (i != ignorar &&
            strcmp(reservas[i].data, data) == 0 &&
            strcmp(reservas[i].hora, hora) == 0) {
            total += reservas[i].numero_pessoas;
        }
    }

    return total;
}
// Adiciona uma reserva se houver lugar
void AdicionarReserva(TReserva reservas[], int* numReservas) {
    if (*numReservas < MAX_RESERVAS) {

        TReserva nova; //variavel temporaria só é guardada no array se couber

        printf("Nome do cliente: ");
        scanf("%49s", &nova.nome_cliente);

        printf("Numero de pessoas: ");
        scanf("%d", &nova.numero_pessoas);

        printf("Data da reserva (dd/mm/aaaa): ");
        scanf("%10s", &nova.data);

        printf("Hora da reserva (hh:mm): ");
        scanf("%9s", &nova.hora);

        int ocupadas = PessoasNaDataHora(reservas, *numReservas, nova.data, nova.hora, -1);

        // Recusa se passar a capacidade
        if (ocupadas + nova.numero_pessoas > CAPACIDADE_MAXIMA) {
            printf("Nao ha lugares suficientes. Ja ha %d pessoas nessa data e hora (capacidade %d).\n", ocupadas, CAPACIDADE_MAXIMA);
            printf("Reserva nao adicionada.\n");
        }
        else {
            reservas[*numReservas] = nova;   // guarda a reserva no array
            (*numReservas)++;
            printf("Reserva adicionada com sucesso.\n");
        }
    }
    else {
        printf("Limite de reservas atingido.\n");
    }
}
// Remove uma reserva pelo número da listagem
void  RemoverReserva(TReserva reservas[], int *numReservas) {
    int numero_reserva;
    printf("Digite o numero da reserva que deseja cancelar: ");
    scanf("%d", &numero_reserva);

    if (numero_reserva > 0 && numero_reserva <= *numReservas) {
        // Move as reservas para preencher a posição da reserva cancelada
        for (int i = numero_reserva - 1; i < *numReservas - 1; i++) {
            reservas[i] = reservas[i + 1];
        }
        (*numReservas)--;
        printf("Reserva cancelada com sucesso!\n");
    }
    else {
        printf("Numero de reserva invalido!\n");
    }
}
// Muda uma reserva, procurando pelo nome do cliente
void MudarReserva(TReserva reservas[], int numReservas, char* nome_cliente) {
    int indice = -1;
    for (int i = 0; i < numReservas; i++) { // Verifica se o nome do cliente é igual ao nome fornecido.
        if (strcmp(reservas[i].nome_cliente, nome_cliente) == 0) {
            indice = i;
            break;
        }
    }
        if (indice != -1) {
            // lemos os novos valores para variaveis temporarias e so os aplicamos se couberem na capacidade.
            int novas_pessoas;
            char nova_data[20];
            char nova_hora[10];

            printf("Numero de pessoas: ");
            scanf("%d", &novas_pessoas);

            printf("Data da reserva (dd/mm/aaaa): ");
            scanf("%19s", nova_data);

            printf("Hora da reserva (hh:mm): ");
            scanf("%9s", nova_hora);

            // Ignora a própria reserva na soma
            int ocupadas = PessoasNaDataHora(reservas, numReservas, nova_data, nova_hora, indice);

            if (ocupadas + novas_pessoas > CAPACIDADE_MAXIMA) {
                printf("Nao ha lugares suficientes. Ja ha %d pessoas nessa data e hora (capacidade %d).\n", ocupadas, CAPACIDADE_MAXIMA);
                printf("Reserva nao modificada.\n");
            }
            else {
                reservas[indice].numero_pessoas = novas_pessoas;
                strcpy(reservas[indice].data, nova_data);
                strcpy(reservas[indice].hora, nova_hora);
                printf("Reserva modificada com sucesso.\n");
            }
        }
        else {
            printf("Nome nao encontrado. Nenhuma reserva modificada.\n");
        }
    }

void MostrarReserva(TReserva reserva) {
    printf("Nome do cliente: %s\n", reserva.nome_cliente);
    printf("Numero de pessoas: %d\n", reserva.numero_pessoas);
    printf("Data da reserva: %s\n", reserva.data);
    printf("Hora da reserva: %s\n", reserva.hora);
}

void ListarReservas(TReserva reservas[], int numReservas) {
    for (int i = 0; i < numReservas; i++) {
        printf("Reserva %d:\n", i + 1);
        MostrarReserva(reservas[i]);
        printf("\n");
    }
}
// Guarda as reservas num ficheiro binário
void GuardarReservas(TReserva reservas[], int numReservas, const char* arquivo) {
    FILE* fp = fopen(arquivo, "wb");
    if (fp != NULL) {
        fwrite(reservas, sizeof(TReserva), numReservas, fp);
        fclose(fp);
        printf("Reservas guardadas com sucesso.\n");
    }
    else {
        printf("Erro ao abrir o arquivo para escrita.\n");
    }
}
// Lê as reservas do ficheiro e devolve quantas leu
int CarregarReservas(TReserva reservas[], const char* arquivo) {
    FILE* fp = fopen(arquivo, "rb");
    int numReservasLidas = 0;

    if (fp != NULL) {
        while (numReservasLidas < MAX_RESERVAS &&   // O limite MAX_RESERVAS evita escrever fora do array
            fread(&reservas[numReservasLidas], sizeof(TReserva), 1, fp) == 1) {
            numReservasLidas++;
        }
        fclose(fp);
    }

    return numReservasLidas;
}

// Ordena as reservas por data (bubble sort)
void OrdenarReservasPorData(TReserva reservas[], int numReservas) {
    for (int i = 0; i < numReservas - 1; i++) {
        for (int j = 0; j < numReservas - i - 1; j++) {
            // Convertendo as datas para um formato dd/mm/aaaa
            int dia1, mes1, ano1, dia2, mes2, ano2;
            sscanf(reservas[j].data, "%d/%d/%d", &dia1, &mes1, &ano1);
            sscanf(reservas[j + 1].data, "%d/%d/%d", &dia2, &mes2, &ano2);

            if (ano1 > ano2 || (ano1 == ano2 && (mes1 > mes2 || (mes1 == mes2 && dia1 > dia2)))) {
                // Troca as reservas se estiverem fora de ordem
                TReserva temp = reservas[j];
                reservas[j] = reservas[j + 1];
                reservas[j + 1] = temp;
            }
        }
    }
}

// Função para pesquisar reservas por nome do cliente
void PesquisarReservaPorNome(TReserva reservas[], int numReservas, char* nome_cliente) {
    
    int encontradas = 0;

    for (int i = 0; i < numReservas; i++) {
        if (strcmp(reservas[i].nome_cliente, nome_cliente) == 0) {
            MostrarReserva(reservas[i]);
            printf("------------------------------\n");
            encontradas = 1;
        }
    }

    if (!encontradas) {
        printf("Nenhuma reserva encontrada para o cliente '%s'.\n", nome_cliente);
    }
}


// Calcula a ocupação (%) numa data e hora especifica
void CalcularOcupacao(TReserva reservas[], int numReservas, char* data , char* hora) {

    int pessoas = PessoasNaDataHora(reservas, numReservas, data, hora, -1);

    double ocupacao = ((double)pessoas / CAPACIDADE_MAXIMA) * 100;

    printf("Ocupacao para %s as %s: %d pessoas (%.2f%%)\n", data, hora, pessoas, ocupacao);
}

int main() {
    TReserva reservas[MAX_RESERVAS];
    int numReservas = 0;
    int opcao;
    char nome_cliente[50];
    char data_calculo[20];
    char hora_calculo[10];
    const char* arquivo = "reservas_restaurante.dat";

    do {
        printf("\nMENU\n");
        printf("[1] Adicionar Reserva\n");
        printf("[2] Remover Reserva\n");
        printf("[3] Mudar Reserva\n");
        printf("[4] Listar Reservas\n");
        printf("[5] Guardar Reservas no Ficheiro\n");
        printf("[6] Ler do ficheiro e Listar Todas as Reservas\n");
        printf("[7] Ordenar por Data e Listar\n");
        printf("[8] Pesquisar Reservas por Nome do Cliente\n");
        printf("[9] Calcular Ocupacao do Restaurante\n");
        printf("[0] Sair\n");

        printf("Escolha uma opcao: ");
        // Se escrever letras, limpa o buffer e volta ao menu
        if (scanf("%d", &opcao) != 1) {
            while (getchar() != '\n');
            opcao = -1;
        } 

        switch (opcao) {
        case 1:
            AdicionarReserva(reservas, &numReservas);
            break;
        case 2:
            RemoverReserva(reservas, &numReservas);
            break;
        case 3:
            printf("Nome do cliente da reserva a ser modificada: ");
            scanf("%49s", nome_cliente);
            MudarReserva(reservas, numReservas, nome_cliente);
            break;
        case 4:
            ListarReservas(reservas, numReservas);
            break;
        case 5:
            GuardarReservas(reservas, numReservas, arquivo);
            break;
        case 6:
            numReservas = CarregarReservas(reservas, arquivo);
            ListarReservas(reservas, numReservas);
            break;
        case 7:
            OrdenarReservasPorData(reservas, numReservas);
            ListarReservas(reservas, numReservas);
            break;
        case 8:
            printf("Digite o nome do cliente: ");
            scanf("%49s", nome_cliente);
            PesquisarReservaPorNome(reservas, numReservas, nome_cliente);
            break;
        case 9:
            printf("Digite a data (dd/mm/aaaa): ");
            scanf("%19s", data_calculo);
            printf("Digite a hora (hh:mm): ");
            scanf("%9s", hora_calculo);
            CalcularOcupacao(reservas, numReservas, data_calculo, hora_calculo);
            break;
        case 0:
            printf("Saindo do programa.\n");
            break;
        default:
            printf("Opçao invalida. Tente novamente.\n");
        }
    } while (opcao != 0);

    return 0;
}

