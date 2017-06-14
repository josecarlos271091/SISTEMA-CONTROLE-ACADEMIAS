#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#define TAM_NOME_ACADEMIA 20
#define TAM_ENDERECO 50
#define TAM_DADOS 90

#include "biblioteca.h"
#include "funcoesBasicas.h"
#include "apresentaDadosAcademia.h"

//Objetivo: Ler e apresentar o nome e o endereco da academia, obtendo os dados do arquivo Academia.txt,
//			caso o arquivo existir, se nao le os dados e escreve no arquivo
//Parametros:Nenhum
//Retorno:Nenhum

void apresentaDadosAcademia()
{
	char nomeAcademia[TAM_NOME_ACADEMIA], enderecoAcademia[TAM_ENDERECO], dados[TAM_DADOS];
	
	if(verificaArquivoExistente("Academia.txt") == 0)
	{
		
		
		FILE *arq = abreArquivo("Academia.txt","wt");
		
		//Solicitando Nome e Endereco da Academia
		leValidaTexto("Hola!, Por Favor Informe o Nome da Academia: ","Dados Invalidos!, Digite corretamente!",nomeAcademia,TAM_NOME_ACADEMIA);
		leValidaTexto("Certo!, Agora Por Favor Informe o Endereco: ","Dados Invalidos!, Digite corretamente!",enderecoAcademia,TAM_ENDERECO);
		
		//Escrevendo no Arquivo
		fprintf(arq,"Academia: %-20s\tEndereco: %-50s",nomeAcademia,enderecoAcademia);
		system("cls");
		fclose(arq);
		
		//Imprimindo na Tela o nome e endereco da Academia
		printf("Academia: %-20s\tEndereco: %-50s\n\n",nomeAcademia,enderecoAcademia);
	}
	else if(verificaArquivoExistente("Academia.txt") == 1)
	{
		FILE *arq = abreArquivo("Academia.txt","rt");
		if((fgets(dados,TAM_DADOS,arq))!=NULL)
	    {
		    printf("%s\n\n",dados);
	    }
		fclose(arq);
		
	}
	else
		printf("Academia: ####### Endereco: ######\n\n");
	
}

