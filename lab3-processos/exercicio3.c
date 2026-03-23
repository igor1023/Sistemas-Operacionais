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

// vou analisar a entrada e verificar se tem '&' => modifica por referência
// retorna:
//      false: caminho invalido (string vazia)
//      true: com caminho valido (string com pelo menos um caractere)
bool entrada_valida(char entrada[], bool* ecomercial){

    int i = strlen(entrada);

    if(i == 0) // string vazia
        return false;

    // se termina com & => ativa true em *ecomercial
    // depois remove o '&'
    // depois retira os espaços entre & e o caminho
    // por fim a string 'entrada' é somente o diretorio
    if(entrada[i - 1] == '&'){

        *ecomercial = true;
        entrada[i - 1] = '\0';

        // decremento o i até encontrar o primeiro espaço a partir do caminho
        for(i = strlen(entrada) - 1; i > 1 && entrada[i] == ' '; i--);
        entrada[++i] = '\0';

    }

    return strlen(entrada) >= 1;

}

int main(int argc, char** argv){

    while(true){

        char entrada[MAX] = " ";
        bool ecomercial = false; // suponho que inicialmente não há &
        
        printf("> ");
        fgets(entrada, MAX, stdin);
        entrada[strlen(entrada) - 1] = '\0'; // remove a quebra de linha

        if(strcmp(entrada, "sair") == 0)
            break;

        // pegar a entrada com uma string apenas e separar com ponteiros
        if(!entrada_valida(entrada, &ecomercial))
            continue; // nao encerra

        // neste ponto, a entrada é diferente de "sair"
        // e ja sabemos se tem ou nao tem '&'
        int pid, status;
        pid = fork();

        if(pid == -1){ // erro

            perror("Erro PID");
            exit(-1);

        }
        else if(pid == 0){ // filho

            char *newargv[] = { NULL };            
            static char *newenviron[] = { NULL };
            execve(entrada, newargv, newenviron);
            perror("Erro no execve");
            exit(1);

        }
        else { // pai
            
            // se nao tem &, entao usa WAITPID
            if(!ecomercial)
                waitpid(pid, &status, 0);

            /*
            Obs.: eu estava utilizando o wait, porém quando eu aplicava:
            /usr/bin/ls   => funcionava
            /usr/bin/ls & => não funcionava
            /usr/bin/ls   => comportamento era como se tivesse &
            então usei o waitpid aguarda o filho cujo ID do processo é igual ao PID e funcionou
            */
        }

    }

    exit(0);
}