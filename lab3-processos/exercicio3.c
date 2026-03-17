/*
Exercício 3: Terminal Embrionário
Implemente um terminal que leia caminhos completos de programas e execute-os usando fork() e
execve(). Utilize wait() ou não dependendo se o comando termina com &. O laço deve continuar
até que o usuário digite sair.
*/
// Bloqueia entrada se NÃO tiver & => usa wait
// Libera entrada se tiver &

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#define MAX 256

bool entrada_valida(char entrada[], bool* ecomercial);

// vou pegar a entrada, o que for caminho joga para A, se tiver & joga em B
bool entrada_valida(char entrada[], bool* ecomercial){

    char *caminho = &entrada[0];
    *ecomercial = false; //assumo que nao tem &

    int i = strlen(entrada) - 1;
    while(i >= 0){

        if(caminho[i] == '&'){

            *ecomercial = true;
            
            i--;
            while(i >= 0 && caminho[i] == ' ') // remover espaços
                i--;

            caminho[++i] = '\0';
            break;

        }
        i--;
    }

    // false: caminho invalido
    // true: com caminho valido
    return caminho[0] != '\0';
}

int main(int argc, char** argv){

    char entrada[MAX];
    bool ecomercial = false;

    while(true){

        printf("> ");
        fgets(entrada, MAX, stdin);
        entrada[strlen(entrada)-1] = '\0'; // remove a quebra de linha

        // pegar a entrada com uma string apenas e separar com ponteiros

        if(!entrada_valida(entrada, &ecomercial))
            exit(-1);

        if(strcmp(entrada, "sair") == 0)
            break;

        // neste ponto, a entrada é diferente de "sair"
        // e ja sabemos se tem ou nao tem '&'

        int pid, status;
        pid = fork();

        if(pid == -1){ // erro

            perror("Erro PID");
            exit(-1);

        }
        else if(pid == 0){ // filho

            execve(entrada, NULL, NULL);
            exit(1);
        }
        else {
            
            // se nao tem &, entao usa WAIT
            if(!ecomercial)
                wait(&status);
        }

    }

    exit(0);
}