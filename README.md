# FORMARQ
Projeto da disciplina ILP010 - Linguagem de Programação - no 2º semestre do curso de Análise e desenvolvimento de sistemas na FATECSP.  
Este projeto é um conversor de arquivos, ou seja, haverá um arquivo de entrada em um determinado formato, o arquivo será lido, e convertido em outro formato. São três tipos de conversão:  
### Invert
Cada caractere lido no arquivo de entrada será o complemento de um no arquivo de saída, isto é, quando este tipo de conversão for realizado duas vezes o arquivo voltará a forma original (arquivo de entrada). Seja qual for a extensão do arquivo de entrada, o arquivo gerado possuirá o mesmo nome, mas com a extensão ".inv". Caso o arquivo de entrada já possuir a extensão ".inv", será gerado o arquivo ".dnv". Exemplo:  
Arquivo de entrada|Arquivo de saída
:---:|:---:
dados.dat|dados.inv
arquivo.txt|arquivo.inv
dados.inv|dados.dnv
### Cript
Será necessário adicionar um parâmetro que funcionará como chave(senha). Cada caractere lido realizará uma operação XOR com um caractere da chave, o resultado será impresso no arquivo de saída com a extensão ".crp", se o arquivo de entrada possuir essa extensão será gerado o arquivo ".drp". Por exemplo:  
dados.txt --> dados.crp
dados.crp --> dados.drp
___
Conteúdo da entrada: BOM DIAA!!
Chave: LUA

Entrada|Chave|Saída
:---:|:---:|:---:
'B'|'L'|'B'^'L'
'O'|'U'|'O'^'U'
'M'|'A'|'M'^'A'
' '|'L'|' '^'L'
'D'|'U'|'D'^'U'
'I'|'A'|'I'^'A'
'A'|'L'|'A'^'L'
'A'|'U'|'A'^'U'
'!'|'A'|'M'^'A'
'!'|'L'|'M'^'L'
### Unix to Dos
Em arquivos texto no DOS, o '\n' é representado pelo par de caracteres CR/LF, isto é, 0x0D seguido por 0x0A, enquanto que no UNIX, basta o caracter LF, isto é, 0x0A. Neste modo, os arquivos texto para UNIX deverão ser convertidos para o padrão DOS, ou seja, sempre que for lido um 0x0A, inserir antes um 0x0D. O arquivo gerado possuíra a extensão ".dos". Por exemplo:
Entrada(dados.unx)|Saída(dados.dos)
:---:|:---:
0x0A|0x0D 0x0A
### Dos to Unix
A conversão inversa do Unix to Dos. O arquivo gerado possuíra a extensão ".unx".