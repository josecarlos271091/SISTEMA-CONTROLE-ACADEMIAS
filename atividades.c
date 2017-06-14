#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

#include "atividades.h"
#include "series.h"
#include "frequentadores.h"
#include "estruturas.h"
#include "biblioteca.h"
#include "funcoesBasicas.h"
#include "apresentaDadosAcademia.h"

#define NOME_ARQ_SERIES "series.txt"
#define NOME_ARQ_FREQ "frequentadores.txt"
#define NOME_ARQ_ATIV "atividades.txt"
#define MIN_MATRICULA 0
#define MAX_MATRICULA 50000
#define MIN_ID 1
#define MAX_ID 99999

//Objetivo: Cadastrar uma nova atividade
//Parametros: Nenhum
//Retorno: Nenhum
void leAtividade(char *nomeArq)
{
	FILE *ArqFreq, *ArqSerie, *ArqAtiv;
	int matricula, idSerie, nroFreq, nroSerie, flag , dia, mes, ano, hora, minutos, segundos;
	Atividade atividade;
	Frequentador frequentador;
	Serie serie;
	
	//Abrindo arquivos de frequentadores e series em modo leitura
	ArqFreq = abreArquivo(NOME_ARQ_FREQ,"rb");	
	ArqSerie = abreArquivo(NOME_ARQ_SERIES,"rb");

	//Ler id de frequentador e id de serie para criar atividade
	apresentaOrdenadosFrequentadores(NOME_ARQ_FREQ);
	printf("\n");
	apresentaDadosSeries(NOME_ARQ_SERIES);
	
	matricula = leValidaInt("Informe Matricula do Frequentador: ","Dados Invalidos!, Digite Novamente ",MIN_MATRICULA,MAX_MATRICULA);
	nroFreq = obtemNroFreq(matricula,NOME_ARQ_FREQ);
	if(nroFreq == 0)
	{
		printf("Frequentador nao existe!\n");
		getch();
		return;
	}
	else
	{
		frequentador = obtemDadosFreq(nroFreq,NOME_ARQ_FREQ,&flag);
		if(flag == 0)
		{
			printf("Erro ao carregar dados do frequentador!\n");
			getch();
			return;
		}
		
		idSerie = leValidaInt("Informe ID da Serie: ","Dados Invalidos!, Digite Novamente ",MIN_ID,MAX_ID);
		nroSerie = obtemNroSerie(idSerie,NOME_ARQ_SERIES);
		if(nroSerie == 0)
		{	
			printf("Serie nao existe!\n");
			getch();
			return;
		}
		else
		{
			serie = obtemDadosSerie(nroSerie,NOME_ARQ_SERIES,&flag);
			if(flag == 0)
			{
				printf("Erro ao carregar dados da serie!\n");
				getch();
				return;
			}
		}	
	}
	//Criando e adicionando dados de  arquivo de atividades
	
	atividade.matricula = frequentador.matricula;
	atividade.id = serie.id;
	
	obtemDataHoraAtual(&dia, &mes,&ano,&hora, &minutos, &segundos);
	
	atividade.dataInicio = transformaDataInt(dia,mes,ano);
	atividade.hora = hora;
	atividade.minutos = minutos;
	atividade.segundos = segundos;
	
	//Verificando se um frequentador repite a mesma serie no mesmo dia
	if(obtemNroAtividade(atividade.id, atividade.matricula, atividade.dataInicio, nomeArq) != 0)
	{
		printf("O frequentador nao pode repetir a mesma serie no mesmo dia!\n");
		getch();
		return;
	}
	
	//Gravando Dados em Arquivo
	ArqAtiv = abreArquivo(nomeArq,"ab");
	if(ArqAtiv != NULL) 
	{
		if(fwrite(&atividade,sizeof(Atividade),1,ArqAtiv)==1) {
			printf("Dados salvos com sucesso.\n");
			getch();
		}else{
			printf("Erro ao gravar dados no arquivo.\n");
			getch();
		}
		system("cls");
		fclose(ArqAtiv);
	}else{
		printf("\nNão foi possivel abrir o arquivo.\n");
		getch();
	}

	//Fechando os arquivos
	fclose(ArqFreq);
	fclose(ArqSerie);
	
}

//	Objetivo: Apresentar os dados de todas as Atividades.
//	Parâmetros: Endereco de memoria do nome do arquivo.
//	Retorno: Nenhum.
void apresentaDadosAtividades(char *nomeArq)
{
	FILE *arq;
	Atividade atividade;
	int dia, mes, ano;
	
	arq = fopen(nomeArq,"rb");
	if(arq!=NULL){
		printf("%-20.20s %-10.10s %-10.10s %-10.10s\n","MATRICULA FREQ","ID SERIE","DATA","HORA");
		while(!feof(arq)){
			if(fread(&atividade,sizeof(Atividade),1,arq)==1)
			{
				transformaIntData(atividade.dataInicio,&dia,&mes,&ano);
				printf("%-20d %-10d %02d/%02d/%d %2.2d:%2.2d:%2.2d\n", atividade.matricula, atividade.id,dia,mes,ano, atividade.hora, atividade.minutos, atividade.segundos);
			}
		}
		getch();
		fclose(arq);
	}
}

//  Objetivo: Dado um número da atividade obter os seus dados
//  Parâmetros: número da atividade, endereço de memória com o nome do arquivo
//			    endereço do flag (0 - erro, 1 - correto)
//  Retorno: Estrutura com os dados da Atividade
Atividade obtemDadosAtividade(int nroAtividade, char *nomeArq, int *flag)
{
	FILE *arq;
	Atividade atividade;

	arq = fopen (nomeArq, "rb");

	if (arq == NULL){
		printf("Nao foi possivel abrir o arquivo");
		*flag = 0;
	} else {
		*flag = 1;
		if(fseek(arq, sizeof(Atividade)*(nroAtividade-1), SEEK_SET) != 0) {
			printf("erro a posicionar arquivo\n");
			*flag = 0;
			getch();
		} else {
			if (fread(&atividade, sizeof(Atividade), 1, arq)!=1){
				printf("erro ao ler a Atividade\n");
				*flag = 0;
				getch();
			}
		}
		fclose(arq);
	}

	return atividade;
}

//	Objetivo: Obter posicao de uma atividade no arquivo.
//	Parâmetros: ID da serie, matricula do frequentador e dataInicio endereco de memoria do nome do arquivo.
//	Retorno:0 - nao existe, N - nro da atividade
int obtemNroAtividade(int id,int matricula,int dataInicio, char *nomeArq)
{
	FILE *arq;
	int cont = 0, flag =0;
	Atividade atividade;

	arq = fopen(nomeArq,"rb");
	if(arq != NULL) {
		while(!feof(arq)) {

			if(fread(&atividade,sizeof(Atividade),1,arq)==1){
				cont++;
				if(atividade.id == id && atividade.matricula == matricula && atividade.dataInicio == dataInicio) {
					flag = cont;
					break;
				}
			}
		}
		fclose(arq);
	}
	return flag;
}

// Objetivo: Excluir uma atividade
// Parâmetros: Endereco ao nome do arquivo
// Retorno: Nenhum
void excluiAtividade(char *nomeArq)
{
	int id,matricula, dataInicio, numAtividade, flag, existeErro;
    char opcao;
    Atividade atividade;
    FILE *arq, *arqAux;
	
	system("cls");
    apresentaDadosAtividades(nomeArq);
    id = leValidaInt("\nInforme o ID da Serie: ", "ID INVALIDO!!", MIN_ID, MAX_ID);
    matricula = leValidaInt("Informe Matricula Frequentador: ","MATRIUCLA INVALIDA!!",MIN_MATRICULA,MAX_MATRICULA);
    dataInicio = leValidaData("Informe Data de Inicio: ");
    
    numAtividade = obtemNroAtividade(id,matricula,dataInicio,nomeArq);
    
    if(numAtividade == 0){
        printf("Atividade nao cadastrada...");
    }else{
        system("cls");
        printf("\n Atividade n%c %02d", 167, numAtividade);
        atividade = obtemDadosAtividade(numAtividade, nomeArq, &flag);
        if(flag == 1){
            printf("\n\tMATRICULA: %d\n\tID: %d\n\t", atividade.matricula, atividade.id);
            opcao = leValidaOpcao("Confirma a Atividade <S/N> ? ", "ERRO", "SN");
            if (opcao == 'S'){
                system("cls");
                existeErro = 0;
            	if((arq = abreArquivo(nomeArq, "rb")) != NULL){
            		if((arqAux = abreArquivo("atividadeTemp.txt", "wb")) != NULL){
            			while(!feof(arq)){
            				if(fread(&atividade, sizeof(Atividade), 1, arq) == 1){
            					if (atividade.id != id || atividade.matricula != matricula || atividade.dataInicio != dataInicio){
            						if(fwrite(&atividade, sizeof(Atividade), 1, arqAux) != 1){
            							printf("Erro ao gravar os dados no arquivo auxiliar.\n");
            							existeErro = 1;
            							break;
									}
								}
							}
						}
						fclose(arqAux);
					}else
						existeErro = 1;
					fclose(arq);
				}else
					existeErro = 1;          
            
	            if (existeErro == 1){
					printf("Não foi possivel remover a atividade...\n");
				}else{
					if(remove(nomeArq) == 0){
						if(rename("atividadeTemp.txt", nomeArq) == 0){
							printf("Atividade excluida com sucesso!\n");
						}else{
							printf("Erro ao renomear o arquivo\n");
						}
					}else{
						printf("Erro ao remover o arquivo\n");
					}
				}	
			}
        }
    }
    getch();
}

//	Objetivo: Verificar se existe frequentador com atividade cadastrada
//	Parâmetros: Matricula do frequentador e endereco de memoria do nome do arquivo.
//	Retorno:0 - nao existe, N - nro da atividade
int verificaFrequentadorAtividade(int matricula, char *nomeArq)
{
	FILE *arq;
	int cont = 0, flag =0;
	Atividade atividade;

	arq = fopen(nomeArq,"rb");
	if(arq != NULL) {
		while(!feof(arq)) {

			if(fread(&atividade,sizeof(Atividade),1,arq)==1){
				cont++;
				if(atividade.matricula == matricula) 
				{
					flag = cont;
					break;
				}
			}
		}
		fclose(arq);
	}
	return flag;
}

//	Objetivo: Verificar se existe uma serie com atividade cadastrada
//	Parâmetros: ID da serie e endereco de memoria do nome do arquivo.
//	Retorno:0 - nao existe, N - nro da atividade
int verificaSerieAtividade(int id, char *nomeArq)
{
	FILE *arq;
	int cont = 0, flag =0;
	Atividade atividade;

	arq = fopen(nomeArq,"rb");
	if(arq != NULL) {
		while(!feof(arq)) {

			if(fread(&atividade,sizeof(Atividade),1,arq)==1){
				cont++;
				if(atividade.id == id) 
				{
					flag = cont;
					break;
				}
			}
		}
		fclose(arq);
	}
	return flag;
}

//	Objetivo: Apresentar os dados das Atividades, a partir de um ID especifico.
//	Parâmetros: Endereco do nome do arquivo
//	Retorno: Nenhum.
void apresentaDadosAtividadeChave(char *nomeArq)
{
	int id, matricula, dataInicio, flag;
	int nroAtividade, dia, mes, ano;
	Atividade atividade;
	
	system("cls");
	
	id = leValidaInt("Informe a ID da Atividade a pesquisar: ","\nNao houve leitura!",MIN_ID,MAX_ID);
	matricula = leValidaInt("Informe a Matricula do Frequentador da Atividade a pesquisar: ","\nNao houve leitura!",MIN_ID,MAX_ID);
	dataInicio = leValidaData("Informe Data de Inicio da Atividade: ");
	nroAtividade = obtemNroAtividade(id, matricula, dataInicio, nomeArq);
	system("cls");
	if (nroAtividade == 0){
		printf("Atividade nao cadastrada\n");
	} else {
		atividade = obtemDadosAtividade(nroAtividade, nomeArq, &flag);
		if (flag == 1 ){
			apresentaDadosAcademia();
			printf("%-20.20s %-10.10s %-10.10s %-10.10s\n","MATRICULA FREQ","ID SERIE","DATA","HORA");
			transformaIntData(atividade.dataInicio,&dia,&mes,&ano);
				printf("%-20d %-10d %02d/%02d/%d %2.2d:%2.2d:%2.2d\n", atividade.matricula, atividade.id,dia,mes,ano, atividade.hora, atividade.minutos, atividade.segundos);
		}
	}

	getch();
}
