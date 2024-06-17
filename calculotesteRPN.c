#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <time.h>

#define MAX_EXPR 9 // Número máximo de expressões

// Definição da estrutura para armazenar expressões e resultados
typedef struct {
    char expressao[50]; // String para armazenar a expressão original
    double resultado;   // Resultado da avaliação da expressão
} ExpressaoResultado;

// Definição da estrutura de Pilha
typedef struct {
    double itens[MAX_EXPR];
    int topo;
} Pilha;

// Protótipos de função
void inicializar(Pilha *p);
void empilhar(Pilha *p, double valor);
double desempilhar(Pilha *p);
double executar_operacao(char operador, double op1, double op2);
double executar_funcao(char *funcao, double op);
double avaliar_posfixa(char *expressao);
void imprimir_resultado_colorido(char *expressao, double resultado, int indice_cor);
void imprimir_passos_avaliacao(char *expressao);
int escolher_operacao();

int main() {
    ExpressaoResultado expressoes[MAX_EXPR]; // Array para armazenar as expressões e resultados

    // Definições das expressões de exemplo
    char expressao1[] = "3 4 2 * 1 5 - 2 3 ^ ^ / +";
    char expressao2[] = "7 2 * 4 +";
    char expressao3[] = "8 5 2 4 + * +";
    char expressao4[] = "6 2 / 3 + 4 *";
    char expressao5[] = "9 5 2 8 * 4 + * +";
    char expressao6[] = "2 3 + log 5 /";
    char expressao7[] = "10 log 3 ^ 2 +";
    char expressao8[] = "45 60 + 30 cos *";
    char expressao9[] = "0.5 45 sen 2 ^ +";

    // Armazenamento das expressões e resultados
    strcpy(expressoes[0].expressao, expressao1);
    expressoes[0].resultado = avaliar_posfixa(expressao1);

    strcpy(expressoes[1].expressao, expressao2);
    expressoes[1].resultado = avaliar_posfixa(expressao2);

    strcpy(expressoes[2].expressao, expressao3);
    expressoes[2].resultado = avaliar_posfixa(expressao3);

    strcpy(expressoes[3].expressao, expressao4);
    expressoes[3].resultado = avaliar_posfixa(expressao4);

    strcpy(expressoes[4].expressao, expressao5);
    expressoes[4].resultado = avaliar_posfixa(expressao5);

    strcpy(expressoes[5].expressao, expressao6);
    expressoes[5].resultado = avaliar_posfixa(expressao6);

    strcpy(expressoes[6].expressao, expressao7);
    expressoes[6].resultado = avaliar_posfixa(expressao7);

    strcpy(expressoes[7].expressao, expressao8);
    expressoes[7].resultado = avaliar_posfixa(expressao8);

    strcpy(expressoes[8].expressao, expressao9);
    expressoes[8].resultado = avaliar_posfixa(expressao9);

    srand(time(NULL)); // Semente para gerar números aleatórios

    // Impressão das expressões e resultados com cores diferentes
    for (int i = 0; i < MAX_EXPR; i++) {
        int indice_cor = rand() % 6; // Gera um número aleatório entre 0 e 5 (6 cores diferentes)
        printf("-----\n");
        printf("Expressao %d: %s\n", i + 1, expressoes[i].expressao);
        imprimir_resultado_colorido(expressoes[i].expressao, expressoes[i].resultado, indice_cor);
    }

    // Escolher expressão para avaliar
    int escolha = escolher_operacao();
    printf("-----\n");
    printf("Expressao escolhida: %s\n", expressoes[escolha].expressao);

    // Imprimir passos da avaliação posfixa
    printf("Passos da avaliacao:\n");
    imprimir_passos_avaliacao(expressoes[escolha].expressao);

    return 0;
}

// Função para inicializar a pilha
void inicializar(Pilha *p) {
    p->topo = -1;
}

// Função para empilhar um valor na pilha
void empilhar(Pilha *p, double valor) {
    if (p->topo < MAX_EXPR - 1) {
        p->itens[++(p->topo)] = valor;
    } else {
        printf("Estouro da pilha\n");
        exit(1);
    }
}

// Função para desempilhar um valor da pilha
double desempilhar(Pilha *p) {
    if (p->topo >= 0) {
        return p->itens[(p->topo)--];
    } else {
        printf("Subfluxo da pilha\n");
        exit(1);
    }
}

// Função para executar operações aritméticas básicas
double executar_operacao(char operador, double op1, double op2) {
    switch (operador) {
        case '+': return op1 + op2;
        case '-': return op1 - op2;
        case '*': return op1 * op2;
        case '/': return op1 / op2;
        case '^': return pow(op1, op2);
        default:
            printf("Operador nao suportado: %c\n", operador);
            exit(1);
    }
}

// Funcao para executar funcoes matematicas
double executar_funcao(char *funcao, double op) {
    if (strcmp(funcao, "raiz") == 0) return sqrt(op);
    else if (strcmp(funcao, "sen") == 0) return sin(op * M_PI / 180.0);    // Conversão para radianos
    else if (strcmp(funcao, "cos") == 0) return cos(op * M_PI / 180.0);    // Conversão para radianos
    else if (strcmp(funcao, "tg") == 0) return tan(op * M_PI / 180.0);     // Conversão para radianos
    else if (strcmp(funcao, "log") == 0) return log10(op);
    else {
        printf("Função nao suportada: %s\n", funcao);
        exit(1);
    }
}

// Função para avaliar uma expressão pós-fixada
double avaliar_posfixa(char *expressao) {
    Pilha pilha;
    inicializar(&pilha);
    char *token = strtok(expressao, " ");
    while (token != NULL) {
        if (isdigit(token[0]) || (token[0] == '-' && isdigit(token[1]))) {
            empilhar(&pilha, atof(token));
        } else if (strlen(token) == 1 && strchr("+-*/^", token[0])) {
            double op2 = desempilhar(&pilha);
            double op1 = desempilhar(&pilha);
            empilhar(&pilha, executar_operacao(token[0], op1, op2));
        } else {
            double op = desempilhar(&pilha);
            empilhar(&pilha, executar_funcao(token, op));
        }
        token = strtok(NULL, " ");
    }
    return desempilhar(&pilha);
}

// Função para imprimir o resultado colorido
void imprimir_resultado_colorido(char *expressao, double resultado, int indice_cor) {
    // Cores disponíveis
    char *cores[] = {"\033[0;35m", "\033[0;33m", "\033[0;31m", "\033[0;36m", "\033[0;32m", "\033[0;34m"};

    // Escolha da cor com base no índice
    printf("%sResultado: %.2lf\n\033[0m", cores[indice_cor], resultado);
}

// Função para imprimir os passos da avaliação posfixa
void imprimir_passos_avaliacao(char *expressao) {
    Pilha pilha;
    inicializar(&pilha);
    char *token = strtok(expressao, " ");
    int passo = 1;
    while (token != NULL) {
        printf("Pilha: [");
        for (int i = 0; i <= pilha.topo; i++) {
            printf("%.2lf", pilha.itens[i]);
            if (i < pilha.topo) {
                printf(", ");
            }
        }
        printf("]\n");

        if (isdigit(token[0]) || (token[0] == '-' && isdigit(token[1]))) {
            empilhar(&pilha, atof(token));
            printf("Passo %d: Empilhado %.2lf\n", passo, atof(token));
        } else if (strlen(token) == 1 && strchr("+-*/^", token[0])) {
            double op2 = desempilhar(&pilha);
            double op1 = desempilhar(&pilha);
            double resultado = executar_operacao(token[0], op1, op2);
            empilhar(&pilha, resultado);
            printf("Passo %d: %.2lf %c %.2lf = %.2lf, Empilhado %.2lf\n", passo, op1, token[0], op2, resultado, resultado);
        } else {
            double op = desempilhar(&pilha);
            double resultado = executar_funcao(token, op);
            empilhar(&pilha, resultado);
            printf("Passo %d: %s(%.2lf) = %.2lf, Empilhado %.2lf\n", passo, token, op, resultado, resultado);
        }
        token = strtok(NULL, " ");
        passo++;
    }
    printf("Pilha final: [");
    for (int i = 0; i <= pilha.topo; i++) {
        printf("%.2lf", pilha.itens[i]);
        if (i < pilha.topo) {
            printf(", ");
        }
    }
    printf("]\n");
}

// Função para permitir ao usuário escolher uma expressão
int escolher_operacao() {
    int escolha;
    printf("Escolha uma expressao para avaliar (de 1 a %d): ", MAX_EXPR);
    scanf("%d", &escolha);
    while (escolha < 1 || escolha > MAX_EXPR) {
        printf("Escolha invalida. Escolha uma expressao de 1 a %d: ", MAX_EXPR);
        scanf("%d", &escolha);
    }
    return escolha - 1;
}
