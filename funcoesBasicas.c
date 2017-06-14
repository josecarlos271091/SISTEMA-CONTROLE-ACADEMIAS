#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "funcoesBasicas.h"

// Objetivo: Le numero inteiro
// Parâmetros: endereco de memoria  da string  mensagem 
// Retorna: numero inteiro
int leInt(char *msn) 
{
	int ret = 0,valor;

	do
	{
		printf(msn);
		fflush(stdin);
		ret = scanf("%d", &valor);
		fflush(stdin);
		
		if(ret == 0)
		{
			printf("Erro ao ler o numero.\n");
			getch();
			system("cls");	
		}		
		
	}while(ret == 0);
    return valor; 	

}

// Objetivo: Le e validar numero inteiro
// Parâmetros: Endereco de memoria  da string  mensagem e mensagem de erro
//			   valor minimo e valor maximo.
// Retorna: Numero inteiro
int leValidaInt(char *msn, char *msnErro, int valorMin, int valorMax) 
{
    int valor;
	
	do
	{
	
		valor =leInt(msn);
		if(valor < valorMin || valor > valorMax)
		{
			printf(msnErro);
			getch();
			system("cls");	
		}
	
	}while(valor < valorMin || valor > valorMax);
    return valor;

}

// Objetivo: Le e numero float
// Parâmetros: endereco de memoria  da string  mensagem
// Retorna: numero real
float leFloat(char *msn) 
{
    float valor;
	int ret = 0;

	do
	{
		printf(msn);
		fflush(stdin);
		ret = scanf("%f", &valor);
		fflush(stdin);
		
		if(ret == 0)
		{
			printf("Erro ao ler o numero.\n");
			getch();
			system("cls");	
		}		
		
	}while(ret == 0);
	return valor;

}

// Objetivo: Le e validar numero float
// Parâmetros: endereco de memoria  da string  mensagem e mensagem de erro valor minimo e valor maximo.
// Retorna: numero real
float leValidaFloat(char *msn, char *msnErro, float valorMin, float valorMax) 
{
    float valor;
	do
	{
	
		valor = leFloat(msn);	
		if(valor < valorMin || valor > valorMax)
		{
			printf(msnErro);
			getch();
			system("cls");	
		}
	
	}while(valor < valorMin || valor > valorMax);
    return valor; 
}

// Objetivo: Le e validar um texto
// Parâmetros: endereco de memoria  da string  mensagem, mensagem de erro e do texto quantidade de caracteres a serem lidos 
// Retorna: nenhum
void leValidaTexto(char *msn, char *msnErro, char *texto, int tam)
{
	do
	{
	
		printf(msn);
		fflush(stdin);
		fgets(texto, tam, stdin);
		fflush(stdin);
		
		if(texto[strlen(texto)-1] == '\n')
     	{
	      	texto[strlen(texto)-1] = '\0';
    	}
		system("cls");

		if(strlen(texto) ==0)
		{
			printf(msnErro);
			getch();
			system("cls");
		}
		
	}while(strlen(texto) ==0);
	
}

// Objetivo: Ler uma opcao 
// Parâmetros: endereco de memoria  da string  mensagem, mensagem de erro e das opcoes validas
// Retorna: opcao valida
char leValidaOpcao(char *msn, char *msnErro, char *opcoesValidas)
{
	char opcao;
    do
	{
		printf(msn);
		fflush(stdin);
	    opcao = toupper(getch());
		fflush(stdin);
		system("cls");

		if(strchr(opcoesValidas,opcao)==NULL)
		{
			printf(msnErro);
			getch();
			system("cls");
		}
		
	}while(strchr(opcoesValidas,opcao)==NULL);    
	return opcao;
}

//Objetivo: Transforma String em minuscula..
//Parâmetros: Referencia ao Vetor String.
//Retorno: Void
void strlower(char *str)
{
	int cont;
	for(cont=0;cont<strlen(str);cont++)
	str[cont] = tolower(str[cont]);
}

//Objetivo: Transforma String em Maiuscula.
//Parâmetros: Referencia ao Vetor String.
//Retorno: Void
void strupper(char *str)
{
	int cont;
	for(cont=0;cont<strlen(str);cont++)
	str[cont] = toupper(str[cont]);
}

//Objetivo: Verificar se existe numero repetido em um vetor.
//Parametro: Referencia ao vetor e a posicao que deve ser verificado 
//Retorno: 0 para se nao existe e 1 para se existe numero repetido
int verificaRepetido(int *valores, int posicao)
{
	int cont,flag=0;
	for(cont=0;cont<posicao;cont++)
	{
		if(valores[posicao]==valores[cont])
		{
			printf("Valor Inserido ja existe no sistema ...\n");
			flag=1;
			break;
		}
	}
	return flag;
}

// Objetivo: Tirar o \n de uma string
// Parâmetros: endereco de memoria  da string  texto
// Retorna: Nada
void tiraTerminador(char *texto)
{

	if(texto[strlen(texto)-1] == '\n')
	{
		texto[strlen(texto)-1] = '\0';
	}
		
}

// Objetivo: Tira todos os brancos a esquerda de uma string 
// Parâmetros: endereço de memória da string a ser modificada
// Retorno: nenhum
void tiraBrEsq(char *str)
{
	char *pStr;    
    pStr = str;
    while(*pStr == ' ' && *pStr != '\0')
        pStr++;
    strcpy(str,pStr);   
}


