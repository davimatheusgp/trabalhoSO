#include <stdio.h>
#include <unistd.h>

int main() {
    long i;
    for (i = 0; i < 8000000000; i++);
    return 0;
}