#include <iostream>

int is_digit(char a) {
    if (a >= '0' and a <= '9')
        return 1;
    return 0;
}

int is_op(char a) {
    if (a == '+' || a == '-' || 
        a == '*' || a == '/')
        return 1;
    return 0;
}

int use_op(int a, int b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;    
    }
    return -1;
}

int preceden(char a, char b) {
    if ((a == '*' || a == '/') &&
        (b == '*' || b == '/'))
        return 1;
    else if ((b == '*' || b == '/') &&
             (a == '+' || a == '-'))
        return 1;
    else if ((a == '+' || a == '-') &&
             (b == '+' || b == '-'))
        return 1;
    return 0;
}

int forward() {
    char symbols[100];
    int numbers[100];
    int top_s = 0; int top_n = 0;
    char token;
    char op;
    int a, b;
    while (std::cin >> token) {
        if (is_digit(token))
            numbers[top_n++] = token - '0';
        else if (is_op(token)) {
            while (top_s != 0 && 
                   preceden(token, symbols[top_s - 1])) {
                op = symbols[--top_s];
                a = numbers[--top_n];
                b = numbers[--top_n];
                numbers[top_n++] = use_op(b, a, op);
            }
            symbols[top_s++] = token;
        }
        else if (token == '(')
            symbols[top_s++] = token;
        else if (token == ')'){
            while (symbols[top_s - 1] != '(') {
                a = numbers[--top_n];
                b = numbers[--top_n];
                op = symbols[--top_s];
                numbers[top_n++] = use_op(b, a, op);
            }
            top_s--;
        }
    }
    while (top_s != 0) {
        op = symbols[--top_s];
        a = numbers[--top_n];
        b = numbers[--top_n];
        numbers[top_n++] = use_op(b, a, op);
    }  
    std::cout << std::endl << numbers[--top_n] << std::endl;
    return 0;
}


int reverse() {
    int a, b;
    char op;
    std::cin >> a;
    
    while (std::cin >> b) {
        std::cin >> op;
        a = use_op(a, b, op);    }

    std::cout << std::endl << a << std::endl;
    return 0;
}

