#ifndef CALCULADORA_H
#define CALCULADORA_H

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

// Funções de manipulação da pilha
void inicializar(Pilha *p);
void empilhar(Pilha *p, double valor);
double desempilhar(Pilha *p);

// Funções para executar operações e funções matemáticas
double executar_operacao(char operador, double op1, double op2);
double executar_funcao(char *funcao, double op);

// Função para avaliar uma expressão pós-fixada
double avaliar_posfixa(char *expressao);

// Função para imprimir o resultado colorido
void imprimir_resultado_colorido(char *expressao, double resultado, int indice_cor);

#endif