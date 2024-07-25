#include <stdio.h>
#include <unistd.h>
int main(){
    long i;
    for(i = 0; i < 16000000000; i++);
    return 0;
}