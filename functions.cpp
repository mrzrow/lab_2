#include <iostream>

int reverse() {
    int a, b;
    char op;
    std::cin >> a;
    
    while (std::cin >> b) {
        std::cin >> op;
        if (op == '+')
            a = a + b;
        else if (op == '-')
            a = a - b; 
        else if (op == '*')
            a = a * b;
        else
            a = a / b;
    }
    std::cout << std::endl << a << std::endl;
    return 1;
}

