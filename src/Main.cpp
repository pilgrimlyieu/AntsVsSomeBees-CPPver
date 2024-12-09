#include "AntRemover.h"
#include "FireAnt.h"
#include "Utilities.h"
#include <iostream>

int main(int argc, char *argv[]) {
    Ant *a = new Ant();
    Ant *b = new Ant();
    a->storeAnt(b);
    return 0;
}