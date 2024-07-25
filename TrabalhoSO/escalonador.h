#include "tipo.h"

//Davi Matheus Garcia Pedroza - 160070040
//Pedro Lisias Viana Arcoverde Alves - 190036559
//Weliton Cesar Pereira Barreto - 200044532


bool lerArquivo(char *);
void inserirProcesso(int num, char *tempo, int *dependencias, int numeroDependencias);
void escalonador();
void executarProcesso(processo *proc);
bool verificarDependencias(processo *proc);
void matarZumbie();