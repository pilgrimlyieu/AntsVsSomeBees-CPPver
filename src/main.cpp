int main(int argc, char *argv[]) {
    // Test clang-tidy
    int *leak = new int[100];
    leak = nullptr;
}