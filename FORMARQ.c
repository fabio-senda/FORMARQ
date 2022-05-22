#include <stdio.h>
#include <locale.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

void invert(char *nomearq, FILE *arq, char *ext){
    char c;
    int invertido;
    FILE *saida;
    if(!strcmp(ext, ".INV") || !strcmp(ext,".inv")){
        strcat(nomearq, ".dnv");
    }else{
        strcat(nomearq, ".inv");
    }
    saida = fopen(nomearq, "w");
    if(saida == NULL){
        printf("|=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-|\n");
        printf("|              Falha ao criar o arquivo                |\n");
        printf("|=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-|\n");
        exit(1);
    }
    c = fgetc(arq);
    while(c != EOF){
        invertido = ~c;
        fputc(invertido, saida);
        c = fgetc(arq);
    }
    fclose(saida);
    printf("|=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-|\n");
    printf("|           O arquivo %s foi criado        \n", nomearq);
    printf("|=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-|\n");
}

void cript(char *nomearq, FILE *arq, char *ext, char *chave){
    char c;
    int i;
    FILE *saida;
    if(!strcmp(ext, ".CRP") || !strcmp(ext,".crp")){
        strcat(nomearq, ".drp");
    }else{
        strcat(nomearq, ".crp");
    }
    saida = fopen(nomearq, "w");
    if(saida == NULL){
        printf("|=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-|\n");
        printf("|              Falha ao criar o arquivo                |\n");
        printf("|=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-|\n");
        exit(1);
    }
    c = fgetc(arq);
    while(c != EOF){
        for(i = 0; chave[i] != '\0' ; i++){
            c = c ^ chave[i];
            fputc(c, saida);
            c = fgetc(arq);
            if(c == EOF){
                break;
            }
        }
    }
    fclose(saida);
    printf("|=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-|\n");
    printf("|           O arquivo %s foi criado        \n", nomearq);
    printf("|=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-|\n");
}

void dostounix(){

}

void unixtodos(){

}

int tiraExtensao(char *s){
    int i;
    for(i = 0; s[i] != '\0'; i++)
        if(s[i] == '.'){
            s[i] = '\0';
            return i;
        }
    return 0;
}

int main(int argc, char **argv[]){
    setlocale(LC_ALL, "portuguese");
    FILE *entrada;
    char *narquivo, tipo, *chave, *extensao;;

    narquivo = malloc(20);
    if(narquivo == NULL){
        printf("|  Memória insuficiente       ");
        exit(1);
    }
    if(argc >= 2)
        strcpy(narquivo, argv[1]);
    else {
        printf("--------------------------------------------------------\n");
        printf("|  Forneça o nome do arquivo: ");
        gets(narquivo);
    }
    free(narquivo);

    entrada = fopen(narquivo, "r");
    if(entrada == NULL){
        printf("|=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
        printf("|  Não foi possível localizar o arquivo <%s> \n", narquivo);
        printf("--------------------------------------------------------\n");
        exit(1);
    }

    if(argc >= 3)
            tipo = argv[3];
    else{
        printf("--------------------------------------------------------\n");
        printf("|                                                      |\n");
        printf("|   I -> O tipo de conversão deve ser o Invert.        |\n");
		printf("|   C -> O tipo de conversão deve ser o Cript.         |\n");
		printf("|   D -> Arquivo texto UNIX, gerar arquivo texto DOS.  |\n");
		printf("|   U -> Arquivo texto DOS, gerar arquivo texto UNIX.  |\n");
        printf("|                                                      |\n");
		printf("--------------------------------------------------------\n");
		printf("|     Escolha um tipo de conversão de arquivo          |\n");
        printf("|       (LETRA MAIUSCULA PLEASE): ");
		tipo = getche();
		printf("                    |\n");
		printf("--------------------------------------------------------");
    }


    extensao = malloc(5);
    if(extensao == NULL){
        printf("|  Memória insuficiente       ");
        exit(1);
    }
    strcpy(extensao, strchr(narquivo,'.'));
    free(extensao);
    tiraExtensao(narquivo);

    voltaaquimeu:
    switch(tipo){
        case 'I':
            invert(narquivo, entrada, extensao);
            break;

        case 'C':
            chave = malloc(20);
            if(argc >= 4)
                strcpy(chave, argv[4]);
            else{
                printf("\n|     Digite a chave: ");
                scanf("%s", chave);
            }
            free(chave);
            cript(narquivo, entrada, extensao, chave);
            break;

        case 'D':
            break;

        case 'U':
            break;

        default:
            while(tipo!='I' && tipo!='C' && tipo!='D' && tipo!='U'){
                printf("\n|  Tipo de conversão inválida! Digite novamente: ");
                tipo = getche();
                printf("     |");
            }
            printf("\n|------------------------------------------------------|");
            goto voltaaquimeu;
            break;
    }

    fclose(entrada);
    return 0;
}
