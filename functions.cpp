#include <iostream>

int check_op(char op, int a, int b) {     
    if (op == '+')
        a = a + b;
    else if (op == '-')
        a = a - b; 
    else if (op == '*')
        a = a * b;
    else
        a = a / b;

    return a;
}

int forward() {
    int a, b;
    char op;
    std::cin >> a;
    
    while (std::cin >> op) {
        std::cin >> b;
        a = check_op(op, a, b);
    }
    
    std::cout << std::endl << a << std::endl;
    return 0;
}

int reverse() {
    int a, b;
    char op;
    std::cin >> a;
    
    while (std::cin >> b) {
        std::cin >> op;
        a = check_op(op, a, b);
    }

    std::cout << std::endl << a << std::endl;
    return 0;
}

