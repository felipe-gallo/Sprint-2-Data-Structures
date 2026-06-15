#include <stdio.h>

#define MAX 10
#define LIMITE_POTENCIA 50

typedef struct {
    int id;
    char nomeCliente[40];
    char veiculo[40];
    int tipoRecarga;
    float bateriaAtual;
    float bateriaDesejada;
    float potencia;
    float energia;
    float valor;
    int hora;
    int ativa;
} Sessao;

Sessao sessoes[MAX];
int total = 0;

float calcularPotenciaTotal() {
    float soma = 0;

    for (int i = 0; i < total; i++) {
        if (sessoes[i].ativa == 1) {
            soma += sessoes[i].potencia;
        }
    }

    return soma;
}

float calcularTarifa(int hora, int tipoRecarga, float potenciaTotal) {
    float tarifa = 1.20;

    if (hora >= 18 && hora <= 21) {
        tarifa += 0.50;
    }

    if (potenciaTotal > 40) {
        tarifa += 0.30;
    }

    if (tipoRecarga == 2) {
        tarifa += 0.40;
    }

    return tarifa;
}

void controlarPotencia() {
    float potenciaTotal = calcularPotenciaTotal();

    if (potenciaTotal > LIMITE_POTENCIA) {
        printf("\nA potencia total passou do limite permitido.");
        printf("\nPotencia atual: %.2f kW", potenciaTotal);
        printf("\nReduzindo a potencia das sessoes ativas...\n");

        for (int i = 0; i < total; i++) {
            if (sessoes[i].ativa == 1) {
                sessoes[i].potencia = sessoes[i].potencia * 0.8;
            }
        }

        printf("Potencia reduzida com sucesso.\n");
    } else {
        printf("\nPotencia dentro do limite.\n");
    }
}

void simularIntegracao(int i) {
    printf("\n--- Simulacao OCPP/MODBUS ---\n");
    printf("Enviando dados da sessao...\n");
    printf("ID_SESSAO: %d\n", sessoes[i].id);
    printf("CLIENTE: %s\n", sessoes[i].nomeCliente);
    printf("VEICULO: %s\n", sessoes[i].veiculo);
    printf("TIPO_RECARGA: %s\n", sessoes[i].tipoRecarga == 1 ? "NORMAL" : "RAPIDA");
    printf("POTENCIA: %.2f kW\n", sessoes[i].potencia);
    printf("ENERGIA: %.2f kWh\n", sessoes[i].energia);
    printf("VALOR: R$ %.2f\n", sessoes[i].valor);
    printf("STATUS: %s\n", sessoes[i].ativa == 1 ? "CARREGANDO" : "FINALIZADA");
    printf("Resposta da plataforma: dados recebidos com sucesso.\n");
}

void iniciarSessao() {
    if (total >= MAX) {
        printf("\nLimite de sessoes atingido.\n");
        return;
    }

    int i = total;

    sessoes[i].id = total + 1;
    sessoes[i].ativa = 1;

    printf("\nNome do cliente: ");
    scanf(" %[^\n]", sessoes[i].nomeCliente);

    printf("Nome/modelo do veiculo: ");
    scanf(" %[^\n]", sessoes[i].veiculo);

    printf("\nTipo de recarga:");
    printf("\n1 - Normal");
    printf("\n2 - Rapida");
    printf("\nEscolha: ");
    scanf("%d", &sessoes[i].tipoRecarga);

    if (sessoes[i].tipoRecarga == 1) {
        sessoes[i].potencia = 11;
    } else if (sessoes[i].tipoRecarga == 2) {
        sessoes[i].potencia = 22;
    } else {
        printf("\nTipo de recarga invalido.\n");
        return;
    }

    printf("\nHorario da recarga (0 a 23): ");
    scanf("%d", &sessoes[i].hora);

    printf("Bateria atual do veiculo (0 a 100): ");
    scanf("%f", &sessoes[i].bateriaAtual);

    printf("Bateria desejada (0 a 100): ");
    scanf("%f", &sessoes[i].bateriaDesejada);

    if (sessoes[i].hora < 0 || sessoes[i].hora > 23) {
        printf("\nHorario invalido.\n");
        return;
    }

    if (sessoes[i].bateriaAtual < 0 || sessoes[i].bateriaAtual > 100 ||
        sessoes[i].bateriaDesejada < 0 || sessoes[i].bateriaDesejada > 100) {
        printf("\nValor de bateria invalido.\n");
        return;
    }

    if (sessoes[i].bateriaDesejada <= sessoes[i].bateriaAtual) {
        printf("\nA bateria desejada precisa ser maior que a atual.\n");
        return;
    }

    sessoes[i].energia = (sessoes[i].bateriaDesejada - sessoes[i].bateriaAtual) * 0.6;

    float potenciaTotal = calcularPotenciaTotal() + sessoes[i].potencia;
    float tarifa = calcularTarifa(sessoes[i].hora, sessoes[i].tipoRecarga, potenciaTotal);

    sessoes[i].valor = sessoes[i].energia * tarifa;

    total++;

    printf("\nSessao iniciada com sucesso!\n");
    printf("Potencia definida automaticamente: %.2f kW\n", sessoes[i].potencia);

    controlarPotencia();
    simularIntegracao(i);
}

void listarSessoes() {
    if (total == 0) {
        printf("\nNenhuma sessao cadastrada.\n");
        return;
    }

    printf("\n--- Sessoes cadastradas ---\n");

    for (int i = 0; i < total; i++) {
        printf("\nID: %d\n", sessoes[i].id);
        printf("Cliente: %s\n", sessoes[i].nomeCliente);
        printf("Veiculo: %s\n", sessoes[i].veiculo);
        printf("Tipo de recarga: %s\n", sessoes[i].tipoRecarga == 1 ? "Normal" : "Rapida");
        printf("Horario: %dh\n", sessoes[i].hora);
        printf("Bateria: %.1f%% ate %.1f%%\n", sessoes[i].bateriaAtual, sessoes[i].bateriaDesejada);
        printf("Potencia: %.2f kW\n", sessoes[i].potencia);
        printf("Energia estimada: %.2f kWh\n", sessoes[i].energia);
        printf("Valor estimado: R$ %.2f\n", sessoes[i].valor);
        printf("Status: %s\n", sessoes[i].ativa == 1 ? "Ativa" : "Finalizada");
    }
}

void finalizarSessao() {
    int id;

    printf("\nDigite o ID da sessao que deseja finalizar: ");
    scanf("%d", &id);

    for (int i = 0; i < total; i++) {
        if (sessoes[i].id == id) {
            if (sessoes[i].ativa == 1) {
                sessoes[i].ativa = 0;
                printf("\nSessao finalizada com sucesso.\n");
                printf("Valor final: R$ %.2f\n", sessoes[i].valor);
                simularIntegracao(i);
            } else {
                printf("\nEssa sessao ja foi finalizada.\n");
            }
            return;
        }
    }

    printf("\nSessao nao encontrada.\n");
}

void gerarRelatorio() {
    float energiaTotal = 0;
    float valorTotal = 0;
    int ativas = 0;

    printf("\n--- Relatorio geral ---\n");

    for (int i = 0; i < total; i++) {
        energiaTotal += sessoes[i].energia;
        valorTotal += sessoes[i].valor;

        if (sessoes[i].ativa == 1) {
            ativas++;
        }
    }

    printf("Total de sessoes: %d\n", total);
    printf("Sessoes ativas: %d\n", ativas);
    printf("Energia total estimada: %.2f kWh\n", energiaTotal);
    printf("Valor total estimado: R$ %.2f\n", valorTotal);
    printf("Potencia atual em uso: %.2f kW\n", calcularPotenciaTotal());
}

int main() {
    int opcao;

    do {
        printf("\n===== SISTEMA DE GERENCIAMENTO DE RECARGA =====\n");
        printf("1 - Iniciar nova recarga\n");
        printf("2 - Ver sessoes cadastradas\n");
        printf("3 - Finalizar recarga\n");
        printf("4 - Gerar relatorio\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                iniciarSessao();
                break;
            case 2:
                listarSessoes();
                break;
            case 3:
                finalizarSessao();
                break;
            case 4:
                gerarRelatorio();
                break;
            case 0:
                printf("\nSistema encerrado.\n");
                break;
            default:
                printf("\nOpcao invalida.\n");
        }

    } while (opcao != 0);

    return 0;
}