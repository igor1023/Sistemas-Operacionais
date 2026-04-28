// Testei a Solução Trivial
// Compilar: gcc conta_trivial.c -o conta_trivial -lpthread
// Executar: ./conta_trivial

#include <stdio.h>
#include <pthread.h>
#include <unistd.h> // Necessário para usleep

int saldo = 100;
int busy = 0; // flag: 0 => livre e 1 => ocupado

void* enter(){

    while(busy);

    // se agora está livre (0),
    // eu marco com 1 para dizer que está ocupado,
    // pois agora eu vou ocupar agora
    busy = 1;
    return NULL;
}

void* leave(){

    // como eu já terminei, estava ocupado por mim;
    // agora eu marco que está livre (0) para outra thread operar
    busy = 0;
    return NULL;
}

void* depositar(void* arg) {
    
    enter();

    int valor = *(int*)arg;

    int temp = saldo; // Passo 1: Leitura
    
    // Estou forcando a troca de contexto aqui:
    // A thread pausa por alguns microssegundos,
    // dando chance para a outra thread ler o mesmo saldo original.
    usleep(100);

    temp += valor; // Passo 2: Soma
    saldo = temp; // Passo 3: Escrita
    
    leave();

    return NULL;
}

int main() {

    pthread_t t1, t2;
    int v1 = 50, v2 = 30;

    pthread_create(&t1, NULL, depositar, &v1);
    pthread_create(&t2, NULL, depositar, &v2);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("Saldo final esperado: 180\n");
    printf("Saldo final obtido: %d\n", saldo);
    return 0;
}