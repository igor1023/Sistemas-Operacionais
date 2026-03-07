// Aluno: Igor da Silva
// Lab 01 - Implementação de Chamadas de Sistema

// gcc -Wall copy.c -o copy
// strace ./copy arquivo.txt

#include<fcntl.h>
#include<stdio.h>
#include<unistd.h>

#define SIZE 128

// buffersize trabalharemos com o SIZE
// buffer é o tamanho do bloco de bytes a ser lido
int myopen(const char *filename, int flags, size_t buffersize){
    //return open(filename, flags)
    int fd = 0;
    
    // r = 64 bits; e = 32 bits
    // movimentao : parametros saida : parametros entrada
    __asm__("mov %0, %%rdi" : : "r"(filename));
    __asm__("mov %0, %%esi" : : "r"(flags));
    __asm__("mov %0, %%rdx" : : "r"(buffersize));
    __asm__("mov $2, %rax");
    __asm__("syscall");
    __asm__("mov %%eax, %0" : "=r"(fd) :); // lendo o valor do ax e colocando no parametro 0 (abrido fd como leitura)

    return fd;
}

int myread(int fd, void *buf, size_t count){
    
    //return read(fd, buf, count);
    __asm__("mov %0, %%edi" : : "r"(fd));
    __asm__("mov %0, %%rsi" : : "r"(buf));
    __asm__("mov %0, %%rdx" : : "r"(count));
    __asm__("mov $0, %rax");
    __asm__("syscall");
    __asm__("mov %%eax, %0" : "=r"(fd) :);

    return fd;

}

int mywrite(int fd, void *buf, size_t count){
    //return write(fd, buf, count);
    __asm__("mov %0, %%edi" : : "r"(fd));
    __asm__("mov %0, %%rsi" : : "r"(buf));
    __asm__("mov %0, %%rdx" : : "r"(count));
    __asm__("mov $1, %rax");
    __asm__("syscall");
    __asm__("mov %%eax, %0" : "=r"(fd) :);

    return fd;

}

int myclose(int fd){
    //return close(fd);
    __asm__("mov %0, %%edi" : : "r"(fd));
    __asm__("mov $3, %rax");
    __asm__("syscall");
    __asm__("mov %%eax, %0" : "=r"(fd));

    return fd;
}

int main(int argc, char **argv){
    
    int fd;
    char buf[SIZE];
    size_t readCount;

    if(argc != 2){

        fprintf(stderr, "Uso correto: %s <nome_do_arquivo>\n", argv[0]);
        return 1;

    }
    
    // pega o arquivo e coloca na RAM => fd é o endereco do arquivo
    fd = myopen(argv[1], O_RDONLY, SIZE);
    if(fd < 0){

        // retorna erro do sistema operacional
        perror("file open");
        return 1;

    }

    while((readCount = myread(fd, buf, SIZE)) > 0){

        if((mywrite(STDOUT_FILENO, buf, readCount)) != readCount){

            perror("write");
            return 1;

        }

    }

    myclose(fd);
    putchar('\n');

    return 0;
}