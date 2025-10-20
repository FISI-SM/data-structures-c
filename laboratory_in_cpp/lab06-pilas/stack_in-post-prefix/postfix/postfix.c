/**
 * To compile:
 * gcc -Wall -o postfix postfix.c
 * */

#include "stackd.h"
#include <assert.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE_EXPRESSION 100
#define TRUE 1
#define FALSE 0

// Prototipos de funciones
int evaluate_postfix(char *expression, int *result);
int evaluate_operator(int operator_symbol, int first_operand, int second_operand, int *result);

int main(void) {
    // Expresión postfija asignada directamente (sin ingreso por teclado)
    // Equivale a: 5 + ((1 + 2) * 4) - 3 = 14
    char expression[MAX_SIZE_EXPRESSION] = "5 1 2 + 4 * + 3 -";
    int value;

    // Mostrar la expresión que se va a evaluar
    printf("Expresion postfija: %s\n", expression);

    // Evaluar la expresión postfija
    if (!evaluate_postfix(expression, &value))
        return 1;

    // Mostrar el resultado final
    printf("Resultado: %d\n", value);

    return 0;
}

// -----------------------------------------------------------
// Evalúa una expresión en notación postfija (postfix / RPN)
// -----------------------------------------------------------
int evaluate_postfix(char *expression, int *result) {
    int i = 0;
    stackd operand_stack;  // Pila para operandos
    assert(result != NULL && expression != NULL);

    // Inicializar la pila
    if (!stackd_init(&operand_stack, 0))
        return FALSE;

    // Recorremos toda la cadena de la expresión
    while (expression[i] != '\0') {
        // Ignorar espacios
        while (isspace((unsigned char)expression[i]))
            i++;

        if (expression[i] == '\0')
            break;

        // Si encontramos un número
        if (isdigit((unsigned char)expression[i])) {
            char *endptr = NULL;
            int val = (int)strtol(&expression[i], &endptr, 10);

            // Validar conversión
            if (&expression[i] == endptr) {
                printf("syntax error.\n");
                stackd_deinit(&operand_stack);
                return FALSE;
            }

            // Empilar número
            if (!stackd_push(&operand_stack, val)) {
                printf("stack error.\n");
                stackd_deinit(&operand_stack);
                return FALSE;
            }

            // Avanzar índice al final del número leído
            i = (int)(endptr - expression);
            continue;
        }

        // Si encontramos un operador válido
        if (strchr("+-*/^", expression[i]) != NULL) {
            // Verificar que haya al menos dos operandos
            if (stackd_empty(&operand_stack)) {
                printf("malformed expression.\n");
                stackd_deinit(&operand_stack);
                return FALSE;
            }
            int b = stackd_pop(&operand_stack);

            if (stackd_empty(&operand_stack)) {
                printf("malformed expression.\n");
                stackd_deinit(&operand_stack);
                return FALSE;
            }
            int a = stackd_pop(&operand_stack);

            int val;
            // Aplicar el operador
            if (!evaluate_operator(expression[i], a, b, &val)) {
                printf("domain or operator error.\n");
                stackd_deinit(&operand_stack);
                return FALSE;
            }

            // Apilar el resultado parcial
            if (!stackd_push(&operand_stack, val)) {
                printf("stack error.\n");
                stackd_deinit(&operand_stack);
                return FALSE;
            }

            i++;
            continue;
        }

        // Si el token no se reconoce
        printf("unknown token: '%c'\n", expression[i]);
        stackd_deinit(&operand_stack);
        return FALSE;
    }

    // Si la pila queda vacía, hay error
    if (stackd_empty(&operand_stack)) {
        printf("syntax error.\n");
        stackd_deinit(&operand_stack);
        return FALSE;
    }

    // El resultado final debe ser el único elemento restante
    *result = stackd_pop(&operand_stack);

    // Si queda algo más, la expresión estaba mal formada
    if (!stackd_empty(&operand_stack)) {
        printf("malformed expression.\n");
        stackd_deinit(&operand_stack);
        return FALSE;
    }

    // Liberar recursos de la pila
    stackd_deinit(&operand_stack);
    return TRUE;
}

// -----------------------------------------------------------
// Aplica el operador sobre dos operandos enteros
// -----------------------------------------------------------
int evaluate_operator(int operator_symbol, int first_operand, int second_operand, int *result) {
    assert(result != NULL);

    switch (operator_symbol) {
        case '+':  // Suma
            *result = first_operand + second_operand;
            return TRUE;
        case '-':  // Resta
            *result = first_operand - second_operand;
            return TRUE;
        case '*':  // Multiplicación
            *result = first_operand * second_operand;
            return TRUE;
        case '/':  // División (verifica división por cero)
            if (second_operand == 0)
                return FALSE;
            *result = first_operand / second_operand;
            return TRUE;
        case '^': {  // Potencia entera
            int res = 1;
            for (int i = 0; i < second_operand; i++)
                res *= first_operand;
            *result = res;
            return TRUE;
        }
        default:
            return FALSE;  // Operador desconocido
    }
}
