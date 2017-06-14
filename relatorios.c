#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

#include "apresentaDadosAcademia.h"
#include "biblioteca.h"
#include "funcoesBasicas.h"
#include "frequentadores.h"
#include "series.h"

#define NOME_ARQ_SERIES "series.txt"
#define NOME_ARQ_FREQ "frequentadores.txt"
#define NOME_ARQ_AT "atividades.txt"

//Objetivo: Apresentar Relatorio R1 (Listar todos os registros cadastrados, ou consulta a traves de chave unica)
//Parametros: nenhum
//Retorno: Nenhum
void apresentaR1()
{
	char opcao;
	opcao = leValidaOpcao("[1]-Consulta de Todos os Registros\n[2]-Consulta a traves de chave unica\n","Opcao Invalida!","12R");
	switch(opcao)
	{
		case '1':
				apresentaDadosAcademia();
				printf("\nFREQUENTADORES:\n\n");
				apresentaOrdenadosFrequentadores(NOME_ARQ_FREQ);
				printf("\nSERIES:\n\n");
				apresentaDadosSeries(NOME_ARQ_SERIES);
				printf("\nATIVIDADES:\n\n");
				apresentaDadosAtividades(NOME_ARQ_AT);
				getch();
				system("cls");
			break;
			
			case '2':
				apresentaDadosMat(NOME_ARQ_FREQ);
				apresentaDadosSerieID(NOME_ARQ_SERIES);
				apresentaDadosAtividadeChave(NOME_ARQ_AT);
				system("cls");
			break;
			
			case 'R':
				return;
			break;
	}
	
}

//Objetivo: Apresentar Relatorio R2 (Pesquisar frequentadores pelo nome(substring), em caso de varios nomes apresentar em ordenada alfabeticamente)
//Parametros: nenhum
//Retorno: Nenhum
void apresentaR2()
{
	pesquisaFrequentadores(NOME_ARQ_FREQ);
}

//Objetivo: Apresentar Relatorio R3 (Mostrar os frequentadores que executaram pelo menos uma vez uma serie de exercicio)
//Parametros: nenhum
//Retorno: Nenhum
void apresentaR3()
{
	apresentaFrequentadoresExecSerie(NOME_ARQ_FREQ);
}

//Objetivo: Apresentar Relatorio R4 (Dado um frequentador, informar todas as atividades desenvolvidas por ele na academia em datas (de ... ate...) (dia/mes/ano))
//Parametros: nenhum
//Retorno: Nenhum
void apresentaR4()
{
	informaAtivFreq(NOME_ARQ_FREQ);
}

//Objetivo: Apresentar Relatorio R5 (Listar todos os frequentadores que utilizaram a academia em uma faixa de datas (de ... ate...) (dia/mes/ano))
//Parametros: Nenhum
//Retorno: Nenhum
void apresentaR5()
{
	utilizaAcademiaFreq();
}

//Objetivo: Apresentar Relatorio R6 (Pesquisar todos os frequentadores que nao frequentam a academia a uma quantidade de dias a ser fornecida pelo usuario)
//Parametros: Nenhum
//Retorno: Nenhum
void apresentaR6()
{
	naoUtilizaAcademiaFreq();
}

	
