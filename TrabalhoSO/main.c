#include "escalonador.h"

//Davi Matheus Garcia Pedroza - 160070040
//Pedro Lisias Viana Arcoverde Alves - 190036559
//Weliton Cesar Pereira Barreto - 200044532


int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Uso: %s <numeroCores> <arquivo_de_entrada>\n", argv[0]);
        exit(1);
    }

    numeroCores = atoi(argv[1]);
    if (numeroCores < 1 || numeroCores > 4) {
        printf("Número de cores deve ser entre 1 e 4.\n");
        exit(1);
    }

    coresLivres = numeroCores;

    if (!lerArquivo(argv[2])) {
        printf("Erro na leitura do arquivo\n");
        exit(1);
    }

    escalonador();

    return 0;
}