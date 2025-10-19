#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#define BLANK ' '
#define TAB '\t'

long int evaluate_prefix();
long int pop();
int isempty();
int white_space_clear(char ch);
long int evaluate_prefix();
void infix_to_prefix();
int prior(char ch);
void push(long int ch);
long int pop();
char infix[100], prefix[100];
long int stk[100];
int top;

int main()
{
    int length_of_exp;
    long int final_result;
    top = -1;
    scanf("%d", &length_of_exp);
    scanf("%s", infix);
    infix_to_prefix();
    printf("%s ", prefix);
    final_result = evaluate_prefix();
    printf("%ld", final_result);
    return 0;
}

void infix_to_prefix()
{
    int i, j, p, n;
    char next;
    char ch;
    char _temp;
    n = strlen(infix);
    p = 0;
    for (i = n - 1; i >= 0; i--)
    {
        ch = infix[i];
        if (!white_space_clear(ch))
        {
            switch (ch)
            {
            case ')':
                push(ch);
                break;
            case '(':
                while ((next = pop()) != ')')
                    prefix[p++] = next;
                break;
            case '+':
            case '-':
            case '*':
            case '/':
            case '%':
            case '^':
                while (!isempty() && prior(stk[top]) > prior(ch))
                    prefix[p++] = pop();
                push(ch);
                break;
            default:
                prefix[p++] = ch;
            }
        }
    }
    while (!isempty())
        prefix[p++] = pop();
    prefix[p] = '\0';
    for (i = 0, j = p - 1; i < j; i++, j--)
    {
        _temp = prefix[i];
        prefix[i] = prefix[j];
        prefix[j] = _temp;
    }
}

int prior(char ch)
{
    switch (ch)
    {
    case ')':
        return 0;
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
    case '%':
        return 2;
    case '^':
        return 3;
    default:
        return 0;
    }
}

void push(long int ch)
{
    if (top > 100)
    {
        printf("stk overflow\n");
        exit(1);
    }
    else
    {
        top = top + 1;
        stk[top] = ch;
    }
}

long int pop()
{
    if (top == -1)
    {
        printf("stk underflow \n");
        exit(2);
    }
    return (stk[top--]);
}
int isempty()
{
    if (top == -1)
        return 1;
    else
        return 0;
}

int white_space_clear(char ch)
{
    if (ch == BLANK || ch == TAB || ch == '\0')
        return 1;
    else
        return 0;
}

long int evaluate_prefix()
{
    long int a, b, _temp, res_;
    int i;

    for (i = strlen(prefix) - 1; i >= 0; i--)
    {
        if (prefix[i] <= '9' && prefix[i] >= '0')
            push(prefix[i] - 48);
        else
        {
            b = pop();
            a = pop();
            switch (prefix[i])
            {
            case '+':
                _temp = b + a;
                break;
            case '-':
                _temp = b - a;
                break;
            case '*':
                _temp = b * a;
                break;
            case '/':
                _temp = b / a;
                break;
            case '%':
                _temp = b % a;
                break;
            case '^':
                _temp = pow(b, a);
            }
            push(_temp);
        }
    }
    res_ = pop();
    return res_;
}