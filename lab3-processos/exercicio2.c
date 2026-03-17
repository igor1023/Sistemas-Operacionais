/*
Exercício 2: Status de Término
Investigue WIFEXITED(status) e WEXITSTATUS(status) e modifique o exercício anterior para calcular
5!, com cada processo realizando uma multiplicação e retornando o resultado parcial.
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(){

    int pid, status;
    int resp = 1;
    int i = 5;

    // a cada laço no while, cria-se um novo filho
    // e cada filho faz uma multiplicacao
    while(i > 0){

        pid = fork();

        if(pid == -1) { // erro

            perror("Fork A falhou");
            exit(-1);

        }
        else if(pid == 0){ // é filho

            // o filho faz a sua multiplicaco e a retorna
            return resp *= i;
            
        }
        else{ // é pai

            wait(&status); // aguarda o filho processar
            if(WIFEXITED(status)){

                i--;
                // o pai pega o valor "resp *= i" calculado pelo filho por meio do WEXITSTATUS
                resp = WEXITSTATUS(status);

            }

        }

    }

    printf("5! = %d\n", resp);
    exit(0);
}