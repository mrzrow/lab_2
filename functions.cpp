#include <iostream>
#include <fstream>

const int STR_LENGTH = 201;
char expression[STR_LENGTH];
char symbols[100];
int numbers[100];
int top_s = 0; int top_n = 0;
int exp_pointer = 0;

void usage() {
    std::cout << "\nUSAGE: ./prog [ --forward ] [ --reverse ] [ --help ]\n";
    std::cout << "              [ --file <file_name> <form=(--forward, --reverse)> ]\n";
    std::cout << "\n------------------------------------Flags meaning-----------------------------------\n\n";
    std::cout << "--forward  ------>  enter mathematical expression in normalized form" << std::endl;
    std::cout << "--reverse  ------>  enter mathematical expression in reverse polish notation form" << std::endl;
    std::cout << "--file     ------>  read mathematical expression form file (from console by default)";
    std::cout << "\n\n";
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

int get_full_num() {
    int a = expression[exp_pointer++] - '0';
    while (is_digit(expression[exp_pointer])) 
        a = a * 10 + expression[exp_pointer++] - '0';
    return a;
}

int next_char() {
    while (!is_op(expression[exp_pointer]) &&
           !is_digit(expression[exp_pointer])) {
        if (!expression[exp_pointer])
            return 1;
        exp_pointer++;
    }
    return 0;
}

int use_op(int a, int b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;    
    }
    return 1;
}

int division_by_zero(int b, char op) {
    if (!b and op == '/')
        return 1;
    return 0;
}

int count() {
    char op = symbols[--top_s];
    int a = numbers[--top_n];
    int b = numbers[--top_n];
    if (division_by_zero(a, op)) {
        std::cerr << "\n##### Division by zero #####\n";
        exit(1);
    }
    int answer = use_op(b, a, op);
    return answer; 
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
    char token = expression[0];
    int result;
    int curr_num;
    while ((token = expression[exp_pointer++])) {
        if (is_digit(token)) {
            curr_num = token - '0';
            while (is_digit(expression[exp_pointer])) {
                token = expression[exp_pointer++];
                curr_num = curr_num * 10 + token - '0';
            }
            numbers[top_n++] = curr_num;
        }
        else if (is_op(token)) {
            while (top_s != 0 && 
                   preceden(token, symbols[top_s - 1])) {
                result = count();
                numbers[top_n++] = result;
            }
            symbols[top_s++] = token;
        }
        else if (token == '(')
            symbols[top_s++] = token;
        else if (token == ')'){
            while (symbols[top_s - 1] != '(') {
                result = count();
                numbers[top_n++] = result;
            }
            top_s--;
        }
    }
    while (top_s != 0) {
        result = count();
        numbers[top_n++] = result;
    }  
    std::cout << std::endl << "Answer: " 
              << numbers[--top_n] << std::endl;
    return 0;
}


int reverse() {
    int a, b;
    char op;
    next_char();
    a = get_full_num();
    next_char();
    
    while (true) {
        b = get_full_num();
        next_char();
        op = expression[exp_pointer++];

        if (division_by_zero(b, op)) {
            std::cerr << "\n##### Division by zero #####\n";
            exit(1);
        }
        a = use_op(a, b, op);
        if (next_char())
            break;
    }

    std::cout << std::endl << "Answer: " 
              << a << std::endl;
    return 0;
}

