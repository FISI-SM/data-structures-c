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

int evaluate_postfix(char *expression, int *result);
int evaluate_operator(int operator_symbol, int first_operand, int second_operand, int *result);

int main(void) {
    char expression[MAX_SIZE_EXPRESSION];
    int value;
    if (fgets(expression, sizeof(expression), stdin) == NULL) return 1;
    size_t n = strlen(expression);
    if (n > 0 && expression[n - 1] == '\n') expression[n - 1] = '\0';
    if (!evaluate_postfix(expression, &value)) return 1;
    printf("%d\n", value);
    return 0;
}

int evaluate_postfix(char *expression, int *result) {
    int i = 0;
    stackd operand_stack;
    assert(result != NULL && expression != NULL);
    if (!stackd_init(&operand_stack, 0)) return FALSE;

    while (expression[i] != '\0') {
        while (isspace((unsigned char)expression[i])) i++;
        if (expression[i] == '\0') break;

        if (isdigit((unsigned char)expression[i])) {
            char *endptr = NULL;
            int val = (int)strtol(&expression[i], &endptr, 10);
            if (&expression[i] == endptr) {
                printf("syntax error.\n");
                stackd_deinit(&operand_stack);
                return FALSE;
            }
            if (!stackd_push(&operand_stack, val)) {
                printf("stack error.\n");
                stackd_deinit(&operand_stack);
                return FALSE;
            }
            i = (int)(endptr - expression);
            continue;
        }

        if (strchr("+-*/^", expression[i]) != NULL) {
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
            if (!evaluate_operator(expression[i], a, b, &val)) {
                printf("domain or operator error.\n");
                stackd_deinit(&operand_stack);
                return FALSE;
            }
            if (!stackd_push(&operand_stack, val)) {
                printf("stack error.\n");
                stackd_deinit(&operand_stack);
                return FALSE;
            }
            i++;
            continue;
        }

        printf("unknown token: '%c'\n", expression[i]);
        stackd_deinit(&operand_stack);
        return FALSE;
    }

    if (stackd_empty(&operand_stack)) {
        printf("syntax error.\n");
        stackd_deinit(&operand_stack);
        return FALSE;
    }

    *result = stackd_pop(&operand_stack);

    if (!stackd_empty(&operand_stack)) {
        printf("malformed expression.\n");
        stackd_deinit(&operand_stack);
        return FALSE;
    }

    stackd_deinit(&operand_stack);
    return TRUE;
}

int evaluate_operator(int operator_symbol, int first_operand, int second_operand, int *result) {
    assert(result != NULL);
    switch (operator_symbol) {
        case '+':
            *result = first_operand + second_operand;
            return TRUE;
        case '-':
            *result = first_operand - second_operand;
            return TRUE;
        case '*':
            *result = first_operand * second_operand;
            return TRUE;
        case '/':
            if (second_operand == 0) return FALSE;
            *result = first_operand / second_operand;
            return TRUE;
        case '^': {
            int res = 1;
            for (int i = 0; i < second_operand; i++) res *= first_operand;
            *result = res;
            return TRUE;
        }
        default:
            return FALSE;
    }
}
