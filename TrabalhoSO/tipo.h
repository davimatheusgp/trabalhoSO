#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <signal.h>

typedef struct Processo {
    int num;
    char tempo[50];
    int dependencias[10];
    int numeroDependencias;
    pid_t pid;
    long tempoInicio;
    long tempoFinal;
    int status;
    struct Processo *proximo;
} processo;

extern processo *processos[50];
extern int numeroProcessos;
extern int numeroCores;
extern int coresLivres;
extern time_t makespanIniciocio;