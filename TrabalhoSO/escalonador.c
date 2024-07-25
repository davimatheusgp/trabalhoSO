#include "escalonador.h"

//Davi Matheus Garcia Pedroza - 160070040
//Pedro Lisias Viana Arcoverde Alves - 190036559
//Weliton Cesar Pereira Barreto - 200044532


processo *processos[50];
int numeroProcessos = 0;
int numeroCores;
int coresLivres;
time_t makespanIniciocio;

bool lerArquivo(char *arquivo) {
    FILE *file = fopen(arquivo, "rt");
    if (file == NULL) {
        return false;
    }

    char linha[50];
    int num, numeroDependencias;
    char tempo[20], dependencias[10];

    while (fgets(linha, 50, file) != NULL) {
        sscanf(linha, "%d %s %s", &num, tempo, dependencias);

        int dep[10];
        numeroDependencias = 0;
        char *token = strtok(dependencias, ",");
        while (token && strcmp(token, "#") != 0) {
            dep[numeroDependencias++] = atoi(token);
            token = strtok(NULL, ",");
        }

        inserirProcesso(num, tempo, dep, numeroDependencias);
    }
    fclose(file);
    return true;
}

void inserirProcesso(int num, char *tempo, int *dependencias, int numeroDependencias) {
    processo *novo = (processo *)malloc(sizeof(processo));
    if (novo == NULL) {
        exit(1);
    }

    novo->num = num;
    strcpy(novo->tempo, tempo);
    novo->numeroDependencias = numeroDependencias;
    for (int i = 0; i < numeroDependencias; i++) {
        novo->dependencias[i] = dependencias[i];
    }
    novo->status = 0;
    novo->pid = 0;
    novo->tempoInicio = 0;
    novo->tempoFinal = 0;
    novo->proximo = NULL;

    processos[numeroProcessos++] = novo;
}

void executarProcesso(processo *proc) {
    pid_t pid_filho = fork();
    if (pid_filho == -1) {
        printf("Erro na criação do processo: %d\n", proc->num);
        exit(EXIT_FAILURE);
    }

    if (pid_filho == 0) { /* Filho executando */
        execl(proc->tempo, proc->tempo, (char *)NULL);
        printf("aqui");
    } else { /* Pai executando */
        proc->pid = pid_filho;
        proc->status = 1;
        printf("aqui2");
        if (makespanIniciocio == 0) {
            time(&makespanIniciocio);
        }
        time(&proc->tempoInicio);
        printf("processo %d executando\n", proc->num);
    }
}

bool verificarDependencias(processo *proc) {
    for (int i = 0; i < proc->numeroDependencias; i++) {
        for (int j = 0; j < numeroProcessos; j++) {
            if (processos[j]->num == proc->dependencias[i] && processos[j]->status != 2) {
                return false;
            }
        }
    }
    return true;
}

void matarZumbie() {
    int status;
    for (int i = 0; i < numeroProcessos; i++) {
        if (processos[i]->status == 1) {
            pid_t resultado = waitpid(processos[i]->pid, &status, WNOHANG);
            if (resultado == processos[i]->pid) {
                processos[i]->status = 2;
                time(&processos[i]->tempoFinal);
                coresLivres++;
            }
        }
    }
}

void escalonador() {
    time_t makespanFinal;

    while (1) {
        for (int i = 0; i < numeroProcessos; i++) {
            if (processos[i]->status == 0 && verificarDependencias(processos[i]) && coresLivres > 0) {
                executarProcesso(processos[i]);
                coresLivres--;
            }
        }

        matarZumbie();

        bool todosExecutados = true;
        for (int i = 0; i < numeroProcessos; i++) {
            if (processos[i]->status != 2) {
                todosExecutados = false;
                break;
            }
        }

        if (todosExecutados) {
            time(&makespanFinal);
            printf("\n\nMAKESPAN: %ld segundos\n\n", makespanFinal - makespanIniciocio);
            for (int i = 0; i < numeroProcessos; i++) {
                printf("Processo: %d - Tempo de execução: %ld segundos\n", processos[i]->num, processos[i]->tempoFinal - makespanIniciocio);
            }
            break;
        }
    }
}