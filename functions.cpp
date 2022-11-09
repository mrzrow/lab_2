#include <iostream>
#include <fstream>

const int STR_LENGTH = 201;
char expression[STR_LENGTH];

void usage() {
    std::cout << "\nUSAGE: ./prog [ --forward ] [ --reverse ] [ --help ]\n";
    std::cout << "              [ --file <file_name> <form=(--forward, --reverse)> ]\n";
    std::cout << "\n------------------------------------Flags meaning-----------------------------------\n\n";
    //std::cout << "./prog < '--file' = from console by default > < 'file_name' > < FLAG[ --forward, --reverse ] >" << std::endl;
    std::cout << "--forward  ------>  enter mathematical expression in normalized form" << std::endl;
    std::cout << "--reverse  ------>  enter mathematical expression in reverse polish notation form" << std::endl;
    std::cout << "--file     ------>  read mathematical expression form file (from console by default)";
    std::cout << std::endl;
}

void read_from_cin() {
    std::cin.read(expression, STR_LENGTH - 1);
    int s = std::cin.gcount();
    expression[s] = '\0';
}

int read_from_file(char *in_name) {
    std::ifstream in_f;
    in_f.open(in_name);
    char sym;
    int i = 0;
    if (in_f.is_open()) {
        while (in_f >> sym)
            expression[i++] = sym;
        in_f.close();
        return 0;
    }
    return 1;
}

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
    int exp_pointer = 0;
    char token = expression[0];
    char op;
    int a, b;
    while ((token = expression[exp_pointer++])) {
        if (is_digit(token)) {
            a = token - '0';
            while (is_digit(expression[exp_pointer])) {
                token = expression[exp_pointer++];
                a = a * 10 + token - '0';
            }
            numbers[top_n++] = a;
        }
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
    std::cout << std::endl << "Answer: " << numbers[--top_n] << std::endl;
    return 0;
}


int reverse() {
    int a, b;
    char op;
    int exp_pointer = 0;
    a = expression[exp_pointer++] - '0';
    while (is_digit(expression[exp_pointer])) {
        a = a * 10 + expression[exp_pointer++] - '0';
    }
    
    while (expression[exp_pointer]) {
        if (!is_digit(expression[exp_pointer])) {
            exp_pointer++;
            continue;
        }
        b = expression[exp_pointer++] - '0';
        while (is_digit(expression[exp_pointer]))
            b = b * 10 + expression[exp_pointer++] - '0';

        while (!is_op(expression[exp_pointer])) 
            exp_pointer++;
        op = expression[exp_pointer++];

        a = use_op(a, b, op);
    }

    std::cout << std::endl << "Answer: " << a << std::endl;
    return 0;
}

