#include <stdio.h>
#include <locale.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

void verificaAloc(char *arq){
	if(arq == NULL){
        printf("|  Memória insuficiente       ");
        exit(1);
    }
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

void invert(char *nomearq, FILE *arq, char *ext){
    char c;
    int invertido;
    FILE *saida;
    
    // Concatena o nome do arquivo com a extensao correta
    if(!strcmp(ext, ".INV") || !strcmp(ext,".inv")){
        strcat(nomearq, ".dnv");
    }else{
        strcat(nomearq, ".inv");
    }
    
    // Abre o arquivo de saída
    saida = fopen(nomearq, "w");
    if(saida == NULL){
        printf("|              Falha ao criar o arquivo                |\n");
        printf("|=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-|\n");
        exit(1);
    }
    
    // Lê o arquivo de entrada
    c = fgetc(arq);
    while(c != EOF){
    	// Inverte o caractere lido e escreve no arquivo de saída
        invertido = ~c;
        fputc(invertido, saida);
        c = fgetc(arq);
    }
    
    // Fecha o arquivo de saída
    fclose(saida);
    printf("|           O arquivo %s foi criado        \n", nomearq);
    printf("|=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-|\n");
}

void cript(char *nomearq, FILE *arq, char *ext, char *chave){
    char c;
    int i;
    FILE *saida;
    
    // Concatena o nome do arquivo com a extensão correta
    if(!strcmp(ext, ".CRP") || !strcmp(ext,".crp")){
        strcat(nomearq, ".drp");
    }else{
        strcat(nomearq, ".crp");
    }
    
    // Abre o arquivo de saída
    saida = fopen(nomearq, "w");
    if(saida == NULL){
        printf("|              Falha ao criar o arquivo                |\n");
        printf("|=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-|\n");
        exit(1);
    }
    
    // Lê o arquivo de entrada
    c = fgetc(arq);
    while(c != EOF){
    	// Faz a operação bit a bit XOR entre o caractere lido e cada caractere da chave
        for(i = 0; chave[i] != '\0' ; i++){
            c = c ^ chave[i];
            // Escreve no arquivo de saída
            fputc(c, saida);
            c = fgetc(arq);
            if(c == EOF){
                break;
            }
        }
    }
    
    // Fecha o arquivo de saída
    fclose(saida);
    printf("|           O arquivo %s foi criado        \n", nomearq);
    printf("|=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-|\n");
}

void UnixToDos(char *nomearq, FILE *arq){
	FILE *saida;
	char c;
	
	// Concatena o nome do arquivo com a extensão
    strcat(nomearq, ".dos");
    // Abre o arquivo de saída
    saida = fopen(nomearq, "w");
    if(saida == NULL){
        printf("|              Falha ao criar o arquivo                |\n");
        printf("|=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-|\n");
        exit(1);
    }
    
    // Lê o arquivo de entrada escreve no arquivo de saída com o \n formatado em arquivo DOS
    c = fgetc(arq);
    while(c != EOF){
        if (c == 0x0A){
            fputc(0x0D, saida);
    	}
    	fputc(c, saida);
        c = fgetc(arq);
    }
    
    // Fechar o arquivo de saída
    fclose(saida);
    printf("|           O arquivo %s foi criado        \n", nomearq);
    printf("|=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-|\n");
}

void DosToUnix(char *nomearq, FILE *arq){
	FILE *saida;
	char c;
	
	// Concatena o nome do arquivo com a extensão
    strcat(nomearq, ".unx");
    
    // Abre o arquivo
    saida = fopen(nomearq, "w");
    if(saida == NULL){
        printf("|              Falha ao criar o arquivo                |\n");
        printf("|=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-|\n");
        exit(1);
    }
    
    // Lê o arquivo de entrada e escreve no arquivo de saída com o \n formatado em arquivo Unix
    c = fgetc(arq);
    while(c != EOF){
        if (c != 0x0D){
            fputc(c, saida);
    	}
        c = fgetc(arq);
    }
    
    // Fecha o arquivo de saída
    fclose(saida);
    printf("|           O arquivo %s foi criado        \n", nomearq);
    printf("|=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-|\n");
}



int main(int argc, char *argv[]){
    setlocale(LC_ALL, "portuguese");
    FILE *entrada;
    char *narquivo, tipo, *chave, *extensao;;
	
	// Aloca memória para o nome do arquivo
    narquivo = (char*) malloc(20);
    verificaAloc(narquivo);
    
    // Aloca memória para a extensão
    extensao = (char*) malloc(4);
    verificaAloc(extensao);
    
    // Recebe o nome do arquivo digitado na linha de comando ou pede o nome do arquivo
    do{
	    if(argc >= 2)
	        strcpy(narquivo, argv[1]);
	    else {
	    	do{
	        	printf("--------------------------------------------------------\n");
	        	printf("|  Forneça o nome do arquivo: ");
	        	gets(narquivo);
			}while(strchr(narquivo,'.') == NULL);
	    }
	}while(strlen(strchr(narquivo, '.')) > 4);
	
    // Copia a extensao do nome do arquivo na variável extensão
    strcpy(extensao, strchr(narquivo,'.'));
	
	// Abre o arquivo
    entrada = fopen(narquivo, "r");
    if(entrada == NULL){
        printf("|=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
        printf("|  Não foi possível localizar o arquivo <%s> \n", narquivo);
        printf("--------------------------------------------------------\n");
        exit(1);
    }
    
    // Tira a extensão do nome do arquivo
	tiraExtensao(narquivo);
	
	// Recebe o tipo de conversão digitado na linha de comando ou pede o tipo de conversão
    if(argc >= 3)
            tipo = argv[3][0];
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
		printf("--------------------------------------------------------\n");
    }
	
    voltaaquimeu:
    
    // Faz a rotina de acordo com a escolha do tipo de conversão
    switch(tipo){
    	// Cria um arquivo complemento de 1 do arquivo de entrada
        case 'I':
            invert(narquivo, entrada, extensao);
            break;
		
		// Cria um arquivo criptografado do arquivo de entrada
        case 'C':
            chave = (char*) malloc(20);
            verificaAloc(chave);
            if(argc >= 4)
                strcpy(chave, argv[4]);
            else{
                printf("|     Digite a chave: ");
                scanf("%s", chave);
                printf("|=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-|\n");
            }
            cript(narquivo, entrada, extensao, chave);
            free(chave);
            break;
            
		// Converte um arquivo Unix para um arquivo Dos
        case 'D':
        	UnixToDos(narquivo, entrada);
            break;

		// Converte um arquivo Dos para um arquivo Unix
        case 'U':
        	DosToUnix(narquivo, entrada);
            break;

		// Se o usuário for burro e escolher um tipo inválido, pede para digitar até ser um tipo válido
        default:
            while(tipo!='I' && tipo!='C' && tipo!='D' && tipo!='U'){
                printf("|  Tipo de conversão inválida! Digite novamente: ");
                tipo = getche();
                printf("     |\n");
            }
            printf("|=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-|\n");
            goto voltaaquimeu;
            break;
    }
	
	// Libera espaço alocado
	free(narquivo);
	free(extensao);
	
	// Fechar o arquivo de entrada
    fclose(entrada);
    return 0;
}
