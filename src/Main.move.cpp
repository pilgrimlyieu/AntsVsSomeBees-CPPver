#include "FireAnt.h"
#include "Utilities.h"
#include <iostream>

int main(int argc, char *argv[]) {
    int b;
    cin >> b;
    while (b--) {
        cout << b << endl;
    }
    std::cout << format("Hello, %s!", "world") << std::endl;
}