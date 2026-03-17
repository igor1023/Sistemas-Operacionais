/*
Exercício 3: Terminal Embrionário
Implemente um terminal que leia caminhos completos de programas e execute-os usando fork() e
execve(). Utilize wait() ou não dependendo se o comando termina com &. O laço deve continuar
até que o usuário digite sair.
*/
// se NAO tiver & => usa wait

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include<stdbool.h>
#include<string.h>

int main(int argc, char** argv){

    char caminho[256];
    char and[5];

    while(true){

        printf("> ");
        scanf("%s %s", caminho, and);

        // pegar a entrada com uma string apenas e separar com ponteiros

        if(strcmp(caminho, "sair") == 0)
            break;

        printf("entrou com %s %s\n", caminho, and);

    }

    exit(0);
}