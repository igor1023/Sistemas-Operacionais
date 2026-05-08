// Compilar: gcc -Wall conta_alternancia.c -o conta_alternancia -lpthread
// Executar: ./conta_alternancia

#include <stdio.h>
#include <pthread.h>
#include <unistd.h> // Necessário para usleep

#define NUM_THREADS 2
int saldo = 100;
int vez = 0;

// como temos que tratar o id da thread e o valor dela para somar
// à conta, e a funcao pthread_create aceita apenas um argumento,
// criei um tipo de dados para tanto (Arg):
typedef struct{

    int id, valor;

} Arg;

void* enter(int id){

    // se nao é minha vez, eu aguardo
    while(vez != id);

    return NULL;
}

void* leave(){

    // atualizo a vez (senha da fila circular)
    vez = (vez + 1) % NUM_THREADS;

    return NULL;
}

void* depositar(void * Args_t) {

    Arg* Args = (Arg*) Args_t;
    int id = Args->id;
    enter(id);

    int valor = Args->valor;
    int temp = saldo; // Passo 1: Leitura

    // Estou for¸cando a troca de contexto aqui:
    // A thread pausa por alguns microssegundos,
    // dando chance para a outra thread ler o mesmo saldo original.
    usleep(100);

    temp += valor; // Passo 2: Soma
    saldo = temp; // Passo 3: Escrita

    leave();
    return NULL;
}

int main() {

    // vou trabalhar que a thread i tem os argumentos i
    pthread_t threads[NUM_THREADS];
    Arg args[NUM_THREADS] = { {0, 30}, {1, 50} };
    
    int i;
    for(i = 0; i < NUM_THREADS; i++)
        if(pthread_create(&threads[i], NULL, depositar, (void*) &args[i]) != 0){
            perror("Erro ao criar thread");
            return 1;
        }

    for(i = 0; i < NUM_THREADS; i++)
        pthread_join(threads[i], NULL);
    
    printf("Saldo final esperado: 180\n");
    printf("Saldo final obtido: %d\n", saldo);
    return 0;
}