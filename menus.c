#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

#include "menus.h"
#include "apresentaDadosAcademia.h"
#include "biblioteca.h"
#include "frequentadores.h"
#include "series.h"
#include "atividades.h"
#include "relatorios.h"

#define NOME_ARQ_SERIES "series.txt"
#define NOME_ARQ_FREQ "frequentadores.txt"
#define NOME_ARQ_AT "atividades.txt"

void menuPrincipal()
{
	char opcao;
	
	//Menu principal funcionalidades
	do
	{
		apresentaDadosAcademia();
		
		printf("MENU PRINCIPAL:\n\n");
		opcao = leValidaOpcao("[F]->FREQUENTADOR\n[S]->SERIE\n[A]->ATIVIDADE\n[R]->RELATORIOS\n[E]->ENCERRAR O PROGRAMA\nOpcao desejada: ","\nOpcao invalida!","FSARE");
		switch(opcao)
		{
			case 'F':
				apresentaDadosAcademia();
				submenuFrequentador();
				system("cls");
			break;
			
			case 'S':
				apresentaDadosAcademia();
				submenuSerie();
				system("cls");
			break;
			
			case 'A':
				apresentaDadosAcademia();
				submenuAtividade();
				system("cls");
			break;
			
			case 'R':
				apresentaDadosAcademia();
				submenuRelatorios();
				system("cls");
			break;
			
			case 'E':
			break;	
		}
	}while(opcao!='E');
}

//Objetivo: Submenu para frequentador
//Parametros: Endereco da string nomeAcademia e enderecoAcademia
//Retorno: void
void submenuFrequentador()
{
	char opcao;
	do
	{
		printf("MENU FREQUENTADOR:\n\n");
		opcao = leValidaOpcao("[C]->Cadastrar Frequentador\n[A]->Alterar Frequentador\n[E]->Excluir Frequentador\n[R]->Retornar ao Menu principal\nOpcao desejada: ","\nOpcao invalida!","CAER");
		switch(opcao)
		{
			case 'C':
				printf("CADASTRAR\n\n");
				leDados(NOME_ARQ_FREQ);
				system("cls");
			break;
			
			case 'A':
				printf("ALTERAR\n\n");
				alteraDadosFreq(NOME_ARQ_FREQ);
				system("cls");
			break;
			
			case 'E':
				printf("EXCLUIR\n\n");
				excluiFreq(NOME_ARQ_FREQ);
				system("cls");
			break;
			
			case 'R':
				return;
			break;	
		}
	}while(opcao!='R');
}

//Objetivo: Submenu para Serie
//Parametros: Endereco da string nomeAcademia e enderecoAcademia
//Retorno: void
void submenuSerie()
{
	char opcao;
	do
	{
		printf("MENU SERIE:\n\n");
		opcao = leValidaOpcao("[C]->Cadastrar Serie\n[A]->Alterar Serie\n[E]->Excluir Serie\n[R]->Retornar ao Menu principal\nOpcao desejada: ","\nOpcao invalida!","CAER");
		opcao = toupper(opcao);
		switch(opcao)
		{
			case 'C':
				printf("CADASTRAR\n\n");
				leSerie(NOME_ARQ_SERIES);
				system("cls");
			break;
			
			case 'A':
				printf("ALTERAR\n\n");
				alteraDadosSerie(NOME_ARQ_SERIES);
				getch();
				system("cls");
			break;
			
			case 'E':
				printf("EXCLUIR\n\n");
				excluiSerie(NOME_ARQ_SERIES);
				getch();
				system("cls");
			break;
			
			case 'R':
				return;
			break;	
		}
	}while(opcao!='R');
}

//Objetivo: Submenu para Atividade
//Parametros: Endereco da string nomeAcademia e enderecoAcademia
//Retorno: void
void submenuAtividade()
{
	char opcao;
	do
	{
		printf("MENU ATIVIDADE:\n\n");
		opcao = leValidaOpcao("[C]->Cadastrar Atividade\n[E]->Excluir Atividade\n[R]->Retornar ao Menu principal\nOpcao desejada: ","\nOpcao invalida!","CER");
		opcao = toupper(opcao);
		switch(opcao)
		{
			case 'C':
				printf("CADASTRAR\n\n");
				leAtividade(NOME_ARQ_AT);
				system("cls");
			break;
			
			case 'E':
				printf("EXCLUIR\n\n");
				excluiAtividade(NOME_ARQ_AT);
				system("cls");
			break;
			
			case 'R':
				return;
			break;	
		}
	}while(opcao!='R');
}

//Objetivo: Submenu para Relatorios
//Parametros: Endereco da string nomeAcademia e enderecoAcademia
//Retorno: void
void submenuRelatorios()
{
	char opcao;
	do
	{
		printf("MENU RELATORIOS:\n\n");
		opcao = leValidaOpcao("[1]->R1: Listar todos os registros ja cadastrados\n[2]->R2: Pesquisar frequentadores pelo nome\n[3]->R3: Mostrar os frequentadores que executaram pelo menos uma vez uma serie de exercicio\n[4]->R4: Dado um frequentador, informar todas as atividades desenvolvidas por ele na academia em datas (de ... ate...)\n[5]->R5: Listar todos os frequentadores que utilizaram a academia em uma faixa de datas (de ... ate...)\n[6]->R6: Pesquisar todos os frequentadores que nao frequentam a academia a uma quantidade de dias\n[R]->Retornar ao Menu principal\nOpcao desejada: ","\nOpcao invalida!","123456R");
		opcao = toupper(opcao);
		switch(opcao)
		{
			case '1':
				apresentaR1();
				system("cls");
			break;
			
			case '2':
				apresentaR2();
				system("cls");
			break;
			
			case '3':
				apresentaR3();
				system("cls");
			break;
			
			case '4':
				apresentaR4();
				system("cls");
			break;
			
			case '5':
				apresentaR5();
				system("cls");
			break;
			
			case '6':
				apresentaR6();
				system("cls");
			break;
			
			case 'R':
				return;
			break;	
		}
	}while(opcao!='R');
}
