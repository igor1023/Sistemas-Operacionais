/*
Exercício 1: Árvore de Processos
Implemente um programa que crie uma árvore de 3 processos com chamadas encadeadas de fork().
Cada processo deve imprimir "Eu sou o processo XXX, filho de YYY"usando getpid() e getppid(),
e os wait() devem garantir a ordem: C antes de B, B antes de A. Use sleep(1) entre as mensagens.
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

// Processo A = pai
// Processo B = filho
// Processo C = neto

int main(){

    int pid_A, pid_B, status;
    pid_A = fork();

    if(pid_A == -1) { // erro

        perror("Fork A falhou");
        exit(-1);

    }
    else if(pid_A == 0) { // filho

        pid_B = fork();
        if(pid_B == -1) {

            perror("Fork B falhou");
            exit(-1);

        }
        else if(pid_B == 0){ // filho do filho = neto

            printf("Processo neto\t pid: %d\t pid filho (pai do neto): %d\n", getpid(), getppid());
            sleep(1);
            exit(0); // mata o processo neto

        }
        
        wait(&status); // aguarda o processo filho terminar para dar continuacao no processo pai
        printf("Processo filho\t pid: %d\t pid pai: %d\n", getpid(), getppid());
        sleep(1);
        exit(0); // mata o processo filho (pai do neto)
    }
    else { // pai

        wait(&status);
        printf("processo pai\t pid: %d\t pid avô (pai do pai - bash): %d\n", getpid(), getppid());
        exit(0); // mata o processo pai (pai do filho)
    }

    exit(0);

}