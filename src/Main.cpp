#include "AntRemover.h"
#include "FireAnt.h"
#include "Utilities.h"
#include <iostream>

int main(int argc, char *argv[]) {
    int b;
    std::cin >> b;
    while (b--) {
        std::cout << b << std::endl;
    }
    std::cout << string_format("Hello, %s!", "world") << std::endl;
}