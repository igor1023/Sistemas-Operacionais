// Aluno: Igor da Silva
// Lab 02 - Uso de Chamadas de Sistema

// gcc -Wall ish.c -o ish
// ./ish

#include<stdio.h>
#include<stdbool.h>
#include<string.h>
#include<unistd.h>
#include<linux/limits.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<dirent.h>
#include<time.h>

#define MAX_CHAR 256

// basta chamar o comando mycwd
int my_cwd(){ //man 3 cwd

    char cwd[PATH_MAX];
    if(getcwd(cwd, sizeof(cwd)) != 0)
        printf("%s\n", cwd);
    
    else {
        perror("getcwd() error");
        return 1;
    }

    return 0;
}

// basta chamar o comando mymkdir nome_do_diretorio
int my_mkdir(){ // man 2 mkdir

    char in[MAX_CHAR];

    // nome do diretorio está salvo no buffer
    // pois scanf pega a primeira string antes
    // de um ' ', \n etc.
    scanf("%s", in);

    if(mkdir(in, 0700) != 0){

        perror("mkdir() error");
        return 1;
        
    }

    return 0;

}

// basta chamar o comando myrmdir nome_do_diretorio
int my_rmdir(){

    char in[MAX_CHAR];

    // nome do diretorio está salvo no buffer
    // pois scanf pega a primeira string antes
    // de um ' ', \n etc.
    scanf("%s", in);

    if(rmdir(in) != 0){
        printf("Diretório %s não encontrado\n", in);
        return 1;
    }

    return 0;

}

// man chdir da unistd.h
// basta chamar mycd nome_do_diretorio
// ou mycd . para permanecer no diretorio atual
// ou mycd .. para voltar um nivel no diretorio
int my_cd(){

    char in[MAX_CHAR];
    scanf("%s", in);

    if(chdir(in) != 0){

        printf("Diretório \x1b[1;32m%s\x1b[0m não encontrado\n", in);
        return 1;

    }

    return 0;

}

// basta chamar o comando mystat nome_do_diretorio
int my_stat(){

    struct stat statbuf;

    char in[MAX_CHAR];

    // nome do diretorio está salvo no buffer
    // pois scanf pega a primeira string antes
    // de um ' ', \n etc.
    scanf("%s", in);

    if(stat(in, &statbuf) != 0){

        printf("Diretório \x1b[1;32m%s\x1b[0m não encontrado\n", in);
        return 1;

    }
    
    printf("    Arquivo: %s\n", in);
    printf("     Blocos: %ld\n", statbuf.st_blocks);
    
    time_t acess_time = statbuf.st_atime;
    printf("     Acesso: %s", ctime(&acess_time));
    
    printf("    Tamanho: %ld\n", statbuf.st_size);

    time_t modified_time = statbuf.st_ctime;
    printf("Modificação: %s", ctime(&modified_time));

    return 0;
}

//opendir, readdir e closedir
// usa biblioteca dirent.h
// basta chamar o comando myls
int my_ls(){

    struct dirent *dir;
    DIR *d; // recebe o resultado de opendir

    // Eu e o colega Tiago descobrimos que o "." pega o diretorio atual
    d = opendir("."); // abre o diretorio atual
    
    if(d != NULL)
        while( (dir = readdir(d)) != NULL )
            printf("%s\n", dir->d_name);

    else {
        printf("Error com myls.");
        return 1;
    }

    return 0;

}

// basta chamar o comando help para visualizar comandos aceitos
void my_help(){

    printf("\x1b[1;39m=== COMANDOS DISPONÍVEIS ===\n\x1b[0m");
    printf("\x1b[1;39mmycd\nmycwd\nmyls\nmymkdir\nmyrmdir\nmystat\n\x1b[0m");
    printf("\x1b[1;39m============================\n\x1b[0m");

}

// Preferi deixar o padrão do shell parecido com o do linux.
// O procedimento abaixo pega a pasta mais "funda" do caminho.
// Com um ponteiro, percorro a string do ultimo caractere para a 
// esquerda até encontrar /, então eu obtenho a ultima
// pasta após a ultima barra;
// Então no shell, na linha veremos ish + nome da pasta mais "recente"
char * corta_string(char path[]){

    int len = strlen(path) - 1;
    char * ptr = &path[len];

    for(; len >= 0; len--){

        if(*ptr == '/'){
            ptr++;
            return ptr;
        }
        else ptr--;

    }

    // se nao tiver '/' no texto, retorno o proprio path
    return path;
}

int main(int argc, char **argv){
    
    char in[MAX_CHAR] = "";
    char path[MAX_CHAR] = "";

    while(true){

        // para personalizar o campo do usuario com o caminho
        // vou concatenar as strings correspondentes
        getcwd(path, sizeof(path));
        strcpy(path, corta_string(path));
        
        // também busquei sobre como colorir o printf
        // https://gist.github.com/fnky/458719343aabd01cfb17a3a4f7296797
        printf("\x1b[1;32mish: \x1b[0m");
        printf("\x1b[1;34m~%s$ \x1b[0m", path);
        scanf("%s", in); // nao pega quebra de linha
        
        if(strcmp(in, "exit") == 0) // se forem iguais
            break;
        
        else if(strcmp(in, "mycwd") == 0)
            my_cwd();
        
        else if(strcmp(in, "mymkdir") == 0)
            my_mkdir();
        
        else if(strcmp(in, "myrmdir") == 0)
            my_rmdir();
        
        else if(strcmp(in, "mycd") == 0)
            my_cd();
        
        else if(strcmp(in, "mystat") == 0)
            my_stat();
        
        else if(strcmp(in, "myls") == 0)
            my_ls();
        
        else if(strcmp(in, "help") == 0)
            my_help();
            
        else {

            printf("\x1b[1;31m%s\x1b[0m: Comando inválido!\n", in);
            printf("Digite \x1b[1;4;37mhelp\x1b[0m para ajuda ou \x1b[1;4;37mexit\x1b[0m para sair\n");


        }
    }

    return 0;
}