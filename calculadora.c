#include "calculadora.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

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
            printf("Operador não suportado: %c\n", operador);
            exit(1);
    }
}

// Função para executar funções matemáticas
double executar_funcao(char *funcao, double op) {
    if (strcmp(funcao, "raiz") == 0) return sqrt(op);
    else if (strcmp(funcao, "sen") == 0) return sin(op * M_PI / 180.0);    // Conversão para radianos
    else if (strcmp(funcao, "cos") == 0) return cos(op * M_PI / 180.0);    // Conversão para radianos
    else if (strcmp(funcao, "tg") == 0) return tan(op * M_PI / 180.0);     // Conversão para radianos
    else if (strcmp(funcao, "log") == 0) return log10(op);
    else {
        printf("Função não suportada: %s\n", funcao);
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