// Arquivo referencia

#include <stdio.h>
#include <pthread.h>
#include <unistd.h> // Necessário para usleep

int saldo = 100;

void* depositar(void* arg) {
    int valor = *(int*)arg;

    int temp = saldo; // Passo 1: Leitura
    // Estou for¸cando a troca de contexto aqui:
    // A thread pausa por alguns microssegundos,
    // dando chance para a outra thread ler o mesmo saldo original.
    usleep(100);

    temp += valor; // Passo 2: Soma

    saldo = temp; // Passo 3: Escrita
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