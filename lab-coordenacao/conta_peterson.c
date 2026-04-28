// Compilar: gcc conta_peterson.c -o conta_peterson -lpthread
// Executar: ./conta_peterson

#include <stdio.h>
#include <pthread.h>
#include <unistd.h> // Necessário para usleep

#define NUM_THREADS 2
int saldo = 100;
int vez = 0;

// como temos que tratar o valor dela para somar e se a thread deseja operar
// à conta, e a funcao pthread_create aceita apenas um argumento,
// criei um tipo de dados para tanto (Arg):
typedef struct{

    int valor, desejo, id; //desejo é 0 ou 1

} Arg;

Arg args[NUM_THREADS] = { {50, 0, 0}, {30, 0, 1} };

void* enter(int id){

    int outra = 1 - id; // indica a outra thread
    args[id].desejo = 1; // a thread deseja acesso à area

    vez = outra;
    // enquano for a vez da OUTRA e a OUTRA desejar acessar
    // a área, eu aguardo
    while((vez == outra) && args[outra].desejo);

    return NULL;
}

void* leave(int id){

    args[id].desejo = 0; // thread nao quer mais usar a area

    return NULL;
}

void* depositar(void* arg_t) {

    Arg arg = *(Arg*) arg_t;

    enter(arg.id);

    int temp = saldo; // Passo 1: Leitura
    // Estou for¸cando a troca de contexto aqui:
    // A thread pausa por alguns microssegundos,
    // dando chance para a outra thread ler o mesmo saldo original.
    usleep(100);

    temp += arg.valor; // Passo 2: Soma
    saldo = temp; // Passo 3: Escrita

    leave(arg.id);
    return NULL;
}

int main() {

    pthread_t t1, t2;
    
    pthread_create(&t1, NULL, depositar, (void*) &args[0]);
    pthread_create(&t2, NULL, depositar, (void*) &args[1]);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("Saldo final esperado: 180\n");
    printf("Saldo final obtido: %d\n", saldo);
    
    return 0;
}