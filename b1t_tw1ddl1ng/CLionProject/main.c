#include <stdio.h>

int normal_xor(int a, int b) {
    return a ^ b;
}

int obfuscated_xor(int a, int b) {
    return !((!(!a || b) || !(a && !b)) &&
             (!(!a && b) || (a && !b)) &&
             ((!a && b) || !(a && !b))
    );
}

int main() {
    int test1 = 10, test2 = 5;

    printf("Normal: %d\n", normal_xor(test1, test2));
    printf("Obfuscated: %d\n", obfuscated_xor(test1, test2));

    return 0;
}
