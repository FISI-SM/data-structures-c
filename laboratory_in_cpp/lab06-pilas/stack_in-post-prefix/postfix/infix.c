#include "stacki.h"
#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define MAX_SIZE_EXPRESSION 256
#define TRUE 1
#define FALSE 0

int convert_infix_to_postfix(char *infix_expr, char *postfix_expr);
int has_precedence(int operator1, int operator2);

// ============================================================
// Ejemplo principal con expresión ya asignada
// ============================================================
int main(void) {
    char infix_expr[MAX_SIZE_EXPRESSION];
    char postfix_expr[MAX_SIZE_EXPRESSION];

    // Ejemplo: expresión infija clásica
    // Equivale a: (5 + (1 + 2) * 4) - 3
    strcpy(infix_expr, "(5 + (1 + 2) * 4) - 3");

    // Mostrar la expresión infija
    printf("Expresión infija: %s\n", infix_expr);

    // Convertir a postfija
    if (convert_infix_to_postfix(infix_expr, postfix_expr)) {
        printf("Expresión postfija: %s\n", postfix_expr);
    } else {
        printf("Error al convertir expresión.\n");
        return 1;
    }

    return 0;
}

// ============================================================
// Convierte una expresión infija a postfija (algoritmo de Shunting Yard)
// ============================================================
int convert_infix_to_postfix(char *infix_expr, char *postfix_expr) {
    int i = 0, p = 0;
    stacki operators_stack;

    if (infix_expr == NULL || postfix_expr == NULL) return FALSE;
    if (!stacki_init(&operators_stack, 0)) return FALSE;

    while (infix_expr[i] != '\0') {
        while (isspace((unsigned char)infix_expr[i])) i++;
        if (infix_expr[i] == '\0') break;

        // Si es un número, lo copiamos directamente a la salida
        if (isdigit((unsigned char)infix_expr[i])) {
            while (isdigit((unsigned char)infix_expr[i])) {
                postfix_expr[p++] = infix_expr[i++];
            }
            postfix_expr[p++] = ' ';
            continue;
        }

        // Si es un operador o paréntesis
        if (strchr("+-*/^()", (unsigned char)infix_expr[i]) != NULL) {
            int sym = (int)infix_expr[i];

            // Si es '(' → apilarlo
            if (sym == '(') {
                if (!stacki_push(&operators_stack, sym)) {
                    stacki_deinit(&operators_stack);
                    return FALSE;
                }
                i++;
                continue;
            }

            // Si es ')' → desapilar hasta encontrar '('
            if (sym == ')') {
                int matched = FALSE;
                while (!stacki_empty(&operators_stack)) {
                    int top = stacki_stacktop(&operators_stack);
                    if (top == '(') {
                        stacki_pop(&operators_stack);
                        matched = TRUE;
                        break;
                    }
                    postfix_expr[p++] = (char)stacki_pop(&operators_stack);
                    postfix_expr[p++] = ' ';
                }
                if (!matched) { // no se encontró el '(' correspondiente
                    stacki_deinit(&operators_stack);
                    return FALSE;
                }
                i++;
                continue;
            }

            // Si es un operador (+, -, *, /, ^)
            while (!stacki_empty(&operators_stack)) {
                int top = stacki_stacktop(&operators_stack);
                if (!has_precedence(top, sym)) break;
                postfix_expr[p++] = (char)stacki_pop(&operators_stack);
                postfix_expr[p++] = ' ';
            }
            if (!stacki_push(&operators_stack, sym)) {
                stacki_deinit(&operators_stack);
                return FALSE;
            }
            i++;
            continue;
        }

        // Símbolo no reconocido → error
        stacki_deinit(&operators_stack);
        return FALSE;
    }

    // Vaciar los operadores restantes
    while (!stacki_empty(&operators_stack)) {
        int op = stacki_pop(&operators_stack);
        if (op == '(') {
            stacki_deinit(&operators_stack);
            return FALSE;
        }
        postfix_expr[p++] = (char)op;
        postfix_expr[p++] = ' ';
    }

    // Quitar espacio final si lo hay
    if (p > 0 && postfix_expr[p - 1] == ' ') p--;
    postfix_expr[p] = '\0';

    stacki_deinit(&operators_stack);
    return TRUE;
}

// ============================================================
// Funciones auxiliares de precedencia de operadores
// ============================================================
static int prec(int op) {
    switch (op) {
        case '+': case '-': return 1;
        case '*': case '/': return 2;
        case '^': return 3;
        default: return -1;
    }
}

int has_precedence(int operator1, int operator2) {
    assert(strchr("+-*/^(", operator1) != NULL && strchr("+-*/^()", operator2) != NULL);
    if (operator1 == '(') return FALSE;
    int p1 = prec(operator1), p2 = prec(operator2);
    if (p1 < 0 || p2 < 0) return FALSE;
    if (operator2 == '^') return (p1 > p2); // ^ es asociativo a la derecha
    return (p1 >= p2);
}
