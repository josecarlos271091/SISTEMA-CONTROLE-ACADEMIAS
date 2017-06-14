#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

#include "frequentadores.h"
#include "estruturas.h"
#include "biblioteca.h"
#include "funcoesBasicas.h"
#include "apresentaDadosAcademia.h"
#include "atividades.h"
#include "series.h"

#define MIN_MATRICULA 0
#define MAX_MATRICULA 50000
#define MIN_PESO 10
#define MAX_PESO 500
#define MIN_DIAS 1
#define MAX_DIAS 1000
#define NOME_ARQ "frequentadores.txt"
#define NOME_ARQ_ATIV "atividades.txt"
#define NOME_ARQ_SERIES "series.txt"

//	Objetivo: Ler os dados de um Frequentador.
//	Parâmetros: Endereço de momoria do nome do arquivo
//	Retorno: Nenhum.
void leDados(char *nomeArq)
{
	FILE *arq;
	int flag = 0;
	Frequentador freq;
	srand(time(NULL)); //inicializando semente de gerador de numeros aleatorios
	int dia, mes, ano;

    system("cls");
    
	//Obtendo e Validando Matricula do Frequentador
	do{
		freq.matricula = rand() % MAX_MATRICULA;
		flag = obtemNroFreq(freq.matricula, nomeArq);
	}while(flag!=0);

	//Obtendo e Validando CPF
	leValidaTexto("Informe CPF (somente numeros): ","Dados Invalidos!",freq.CPF,TAM_CPF);
	flag = validaCPF(freq.CPF);
	if(flag!=1)
	{
		printf("CPF Invalido!\n");
		getch();
		return;
	}
			
	//Obtendo e Validando Nome, Peso e Sexo
	leValidaTexto("Nome: ","\nNao houve leitura!",freq.nome,TAM_NOME);
	freq.peso = leValidaFloat("Peso em kg: ","\nValor invalido!",MIN_PESO,MAX_PESO);
	freq.sexo = leValidaOpcao("Sexo (M/F): ","Valor invalido!","MF");
	
	//Obtendo data de ingresso
	obtemDataAtual(&dia,&mes,&ano);
	freq.dataIngresso = transformaDataInt(dia,mes,ano);
	
	//Gravando no Arquivo
	arq = fopen(nomeArq,"ab");
	if(arq!=NULL) {
		if(fwrite(&freq,sizeof(Frequentador),1,arq)==1) {
			printf("Dados salvos com sucesso.\n");
			getch();
		}else{
			printf("Erro ao gravar dados no arquivo.\n");
			getch();
		}
		system("cls");
		fclose(arq);
	}else{
		printf("\nNão foi possivel abrir o arquivo.\n");
		getch();
	}
	system("cls");

}
//	Objetivo: Apresentar os dados dos frequentadores sem ordenar.
//	Parâmetros: Endereco de memoria do nome do arquivo.
//	Retorno: Nenhum.
void apresentaDadosFreq(char *nomeArq)
{
	FILE *arq;
	Frequentador freq;
	int dia, mes, ano;

	arq = fopen(nomeArq,"rb");
	if(arq!=NULL){
		printf("%-9.9s %-20.20s %-12.12s %-10.10s %-10.10s %-13.13s\n","MATRICULA","NOME DO FREQUENTADOR","CPF","PESO","SEXO","DATA INGRESSO");
		while(!feof(arq)){
			if(fread(&freq,sizeof(Frequentador),1,arq)==1){
				transformaIntData(freq.dataIngresso, &dia, &mes, &ano);
				printf("%-9d %-20.20s %-12.12s %-10.2f %-10c %2.2d/%2.2d/%2.2d\n", freq.matricula, freq.nome, freq.CPF, freq.peso, freq.sexo, dia, mes, ano);
			}
		}
		getch();
		fclose(arq);
	}
}
//	Objetivo: Verificar se uma matricula é repetida.
//	Parâmetros: Matricula do frequentador e endereco de memoria do nome do arquivo.
//	Retorno:0 - nao existe, N - nro do frequentador
int obtemNroFreq(int matricula, char *nomeArq)
{
	FILE *arq;
	int contFreq = 0, flag =0;
	Frequentador freq;

	arq = fopen(nomeArq,"rb");
	if(arq != NULL) {
		while(!feof(arq)) {

			if(fread(&freq,sizeof(Frequentador),1,arq)==1){
				contFreq++;
				if(freq.matricula == matricula) {
					flag = contFreq;
					break;
				}
			}
		}
		fclose(arq);
	}
	return flag;
}

//	Objetivo: Apresentar os dados dos frequentadores, a partir de uma matricula especifica.
//	Parâmetros: Endereco do nome do arquivo
//	Retorno: Nenhum.
void apresentaDadosMat(char *nomeArq)
{
	int matricula, flag, nroFreq, dia, mes, ano;
	Frequentador freq;

	system("cls");
	matricula = leValidaInt("Informe a matricula do Frequentador a pesquisar: ","\nNao houve leitura!",MIN_MATRICULA,MAX_MATRICULA);
	nroFreq = obtemNroFreq(matricula, nomeArq);
	system("cls");
	if (nroFreq == 0){
		printf("Frequentador nao cadastrado\n");
	} else {
		freq = obtemDadosFreq(nroFreq, nomeArq, &flag);
		transformaIntData(freq.dataIngresso, &dia, &mes, &ano);
		if (flag == 1 ){
			apresentaDadosAcademia();
			printf("%-9.9s %-20.20s %-12.12s %-10.10s %-10.10s %-13.13s\n","MATRICULA","NOME DO FREQUENTADOR","CPF","PESO","SEXO","DATA INGRESSO");
			printf("%-9d %-20.20s %-12.12s %-10.2f %-10c %2.2d/%2.2d/%2.2d\n", freq.matricula, freq.nome, freq.CPF, freq.peso, freq.sexo, dia, mes, ano);
		}
	}

	getch();
}
//  Objetivo: alterar os dados de um frequentador
//  Parâmetros: Endereco de memoria do nome do aarquivo.
//  Retorno: nenhum
void alteraDadosFreq(char *nomeArq)
{
    int matricula, numFreq, flag;
    char opcao;
    Frequentador freq;
    FILE *arq;

    system("cls");
    apresentaOrdenadosFrequentadores(nomeArq);
    matricula = leValidaInt("\nInforme a matricula do Frequentador: ", "MATRICULA INVALIDA!!", MIN_MATRICULA, MAX_MATRICULA);
    numFreq = obtemNroFreq(matricula,nomeArq);
    if(numFreq == 0){
        printf("Frequentador nao cadastrado...");
        getch();
        return;
    }else{
        system("cls");
        printf("\n Frequentador n%c %02d", 167, numFreq);
        freq = obtemDadosFreq(numFreq, nomeArq, &flag);
        if(flag == 1){
            printf("\n\tNOME: %s\n\tMATRICULA: %d\n\t", freq.nome, freq.matricula);
            opcao = leValidaOpcao("Confirma o Frequentador <S/N> ? ", "ERRO", "SN");
            if (opcao == 'S'){
                system("cls");
                
                leValidaTexto("Informe o novo nome: ", "Nome Invalido", freq.nome, TAM_NOME);
                leValidaTexto("Informe novo CPF (somente numeros): ","Dados Invalidos!",freq.CPF,TAM_CPF);
			flag = validaCPF(freq.CPF);
			if(flag!=1)
			{
				printf("CPF Invalido!\n");
				getch();
				return;
			}
					
			//Obtendo e Validando Nome, Peso e Sexo
			freq.peso = leValidaFloat("Novo Peso em kg: ","\nValor invalido!",MIN_PESO,MAX_PESO);
			freq.sexo = leValidaOpcao("Novo Sexo (M/F): ","Valor invalido!","MF");
			
			//Gravando Novo Frequentador em arquivo
			gravaFrequentador(&freq, numFreq, nomeArq);
		    }
		}
	}
}
// Objetivo: Excluir um frequentador
// Parâmetros: Endereco ao nome do arquivo
// Retorno: 
void excluiFreq(char *nomeArq)
{
	int matricula, numFreq, flag, existeErro;
    char opcao;
    Frequentador freq;
    FILE *arq, *arqAux;
	
	system("cls");
    apresentaOrdenadosFrequentadores(nomeArq);
    matricula = leValidaInt("\nInforme a matricula do frequentador: ", "MATRICULA INVALIDA!!", MIN_MATRICULA, MAX_MATRICULA);
    numFreq = obtemNroFreq(matricula,nomeArq);
    if(numFreq == 0){
        printf("Frequentador nao cadastrado...");
    }else{
    	//Verificando se o Frequentador frequentou a academia
    	if(verificaFrequentadorAtividade(matricula,NOME_ARQ_ATIV) != 0)
    	{
    		printf("Impossivel excluir Frequentador!, Atividades estao sendo executadas por ele!\n");
    		getch();
    		return;
		}
        system("cls");
        printf("\n Frequentador n%c %02d", 167, numFreq);
        freq = obtemDadosFreq(numFreq, nomeArq, &flag);
        if(flag == 1){
            printf("\n\tNOME: %s\n\tMATRICULA: %d\n\t", freq.nome, freq.matricula);
            opcao = leValidaOpcao("Confirma o Frequentador <S/N> ? ", "ERRO", "SN");
            if (opcao == 'S'){
                system("cls");
                existeErro = 0;
            	if((arq = abreArquivo(NOME_ARQ, "rb")) != NULL){
            		if((arqAux = abreArquivo("frequentadorTemp.txt", "wb")) != NULL){
            			while(!feof(arq)){
            				if(fread(&freq, sizeof(Frequentador), 1, arq) == 1){
            					if (freq.matricula != matricula){
            						if(fwrite(&freq, sizeof(Frequentador), 1, arqAux) != 1){
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
					
	            if (existeErro == 1)
				{
					printf("Não foi possivel remover o funcionario...\n");
				}else
				{
					if(remove(nomeArq) == 0){
						if(rename("frequentadorTemp.txt", nomeArq) == 0){
							printf("Frequentador excluido com sucesso!\n");
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
// Objetivo :  Gravar o dado do frequentador no arquivo
// Parâmetros: Endereco da variavel frequentador, o numero do frequentador e o nome do arqivo
//Retorno :   Nenhum
void gravaFrequentador(Frequentador *frequentador,int nrFreq, char *nomeArq)
{
	FILE *arq;
	arq=fopen(nomeArq, "r+b");
	if(arq!=NULL){
		if(fseek(arq, sizeof(Frequentador)*(nrFreq-1), SEEK_SET)==0){
			if(fwrite(frequentador, sizeof(Frequentador),1,arq)==1){
				printf("Sucesso!");
			}else
				printf("Erro ao escrever os dados no arquivo!");
		}else
			printf("Erro ao posicionar os dados no arquivo!");
		fclose(arq);
	}
}
//  Objetivo: Dado um número do frequentador obter os seus dados
//  Parâmetros: número do frequentador, endereço de memória com o nome do arquivo
//			endereço do flag (0 - erro, 1 - correto)
//  Retorno: Estrutura com os dados do frequentador
Frequentador obtemDadosFreq(int nroFreq, char *nomeArq, int *flag)
{
	FILE *arq;
	Frequentador frequentador;
	int cont = 0;

	arq = fopen (nomeArq, "rb");

	if (arq == NULL){
		printf("Nao foi possivel abrir o arquivo");
		*flag = 0;
	} else {
		*flag = 1;
		if(fseek(arq, sizeof(Frequentador)*(nroFreq-1), SEEK_SET) != 0) {
			printf("erro a posicionar arquivo\n");
			*flag = 0;
			getch();
		} else {
			if (fread(&frequentador, sizeof(Frequentador), 1, arq)!=1){
				printf("erro ao ler o frequentador\n");
				*flag = 0;
				getch();
			}
		}
		fclose(arq);
	}

	return frequentador;
}
// Objetivo: obter a qtde de Frequentadores cadastrados
// Parâmetros: endereco de memoria com o nome do arquivo
// Retorno: qtde de Frequentadores
int obtemQtdeFrequentadores(char *nomeArq)
{
	FILE *arq;
	int qtdFrequentadores = 0;
	Frequentador freq;
	if((arq = abreArquivo(nomeArq,"rb")) != NULL){
			if(fseek(arq,0,SEEK_END) == 0){
				qtdFrequentadores = ftell(arq)/sizeof(Frequentador);
			}
	fclose(arq);
	}
	return qtdFrequentadores;	
}

//Objetivo: Apresentar Frequentadores ordenados por nome
//Parametros: Endereco do nome do arquivo a ordenar e apresentar
//Retorno: Nenhum
void apresentaOrdenadosFrequentadores(char *nomeArq)
{
	FILE *arq;
	Frequentador *freq;
	int qtdFreq, cont=0, dia, mes, ano;

	qtdFreq= obtemQtdeFrequentadores(nomeArq);
	
	freq=(Frequentador* )malloc(sizeof(Frequentador)*qtdFreq);
	system("cls");
	if ((arq=abreArquivo(nomeArq, "rb")) != NULL)
	{
		if(fread(freq, sizeof(Frequentador), qtdFreq, arq)!=0)
		{
			qsort(freq,qtdFreq,sizeof(Frequentador),verificaOrdenacaoNome);
			apresentaDadosAcademia(); 
			printf("%-9.9s %-20.20s %-12.12s %-10.10s %-10.10s %-13.13s\n","MATRICULA","NOME DO FREQUENTADOR","CPF","PESO","SEXO","DATA INGRESSO");
			for(cont=0; cont < qtdFreq; cont++){
				transformaIntData(freq[cont].dataIngresso, &dia, &mes, &ano);
				printf("%-9d %-20.20s %-12.12s %-10.2f %-10c %2.2d/%2.2d/%2.2d\n", freq[cont].matricula, freq[cont].nome, freq[cont].CPF, freq[cont].peso, freq[cont].sexo, dia, mes, ano);
			}
			free(freq);
		}
		fclose (arq);
	}	
	getch();
}

//Objetivo: Pesquisar e apresentar  os frequentadores em ordem alfabetica
//Parametro: Endereço de memoria de uma string com nome do arquivo
//Saida: Nenhum
void pesquisaFrequentadores(char *nomeArq)
{
	FILE *arq;
	Frequentador *freq=NULL, *freqAux, freqLido;
	int qtdFreq=0, cont=0, dia, mes, ano;
	char nomePesquisa [TAM_NOME];
	system("cls");
	leValidaTexto("\nDigite o Nome para ser Pesquisado:", "Nome Invalido", nomePesquisa, TAM_NOME);
			
	if ((arq=abreArquivo(nomeArq, "rb")) != NULL){
		while (!feof(arq)){
			if(fread(&freqLido, sizeof(Frequentador), 1, arq) == 1)
			{
				if(strIstr(freqLido.nome ,nomePesquisa)!= NULL)	{
					freqAux= (Frequentador* ) realloc(freq, sizeof(Frequentador)*(qtdFreq+1));
					if (freqAux != NULL ){
						freq=freqAux;
						freq[qtdFreq]=freqLido;
						qtdFreq++;
					}
				}
			}
		}
		
		fclose (arq);
	} 
	
	if (qtdFreq != 0 )
	{
		ordenarFrequentador(freq, qtdFreq);
		apresentaDadosAcademia();
		printf("%-9.9s %-20.20s %-12.12s %-10.10s %-10.10s %-13.13s\n","MATRICULA","NOME DO FREQUENTADOR","CPF","PESO","SEXO","DATA INGRESSO");
		for (cont=0; cont < qtdFreq ; cont++)
		{
			transformaIntData(freq[cont].dataIngresso, &dia, &mes, &ano);
			printf("%-9d %-20.20s %-12.12s %-10.2f %-10c %2.2d/%2.2d/%2.2d\n", freq[cont].matricula, freq[cont].nome, freq[cont].CPF, freq[cont].peso, freq[cont].sexo, dia, mes, ano);
		}
		getch();
		free(freq);
	} else {
		printf("Nome nao encontrado!\n");
		getch();
	}	
}


//Objetivo : Ordenar os dados dos frequentadores por nome
//Parametros: Endereço inicial do vetor de frequentadores e quantidade de frequentadores  
//Retorno : Nenhum
void ordenarFrequentador(Frequentador *freq, int qtdFreq)
{
	qsort(freq,qtdFreq,sizeof(Frequentador),verificaOrdenacaoNome);
}

//Objetivo: Verificar se os dados devem ser trocados pela Qsort.
//Parametros: Dois enderecos de memoria.
//Retorno: 0, >0 ou <0.
int verificaOrdenacaoNome(const void *p1, const void *p2)
{
	Frequentador *freq1, *freq2;
	
	freq1 =(Frequentador*)p1;
	freq2 =(Frequentador*)p2;
	
	return stricmp(freq1->nome, freq2->nome);
}

//Objetivo: Apresentar Dados de Frequentadores que executram pelo menos uma serie de exercicios na academia
//Parametros: Endereco string nome arquivo frequentadores
//Retorno: Nenhum
void apresentaFrequentadoresExecSerie(char *nomeArq)
{
	FILE *arq;
	Frequentador freq;
	int dia, mes, ano;
	
	system("cls");
	if ((arq=abreArquivo(nomeArq, "rb")) != NULL)
	{
		apresentaDadosAcademia(); 
		printf("FREQUENTADORES QUE EXECUTARAM PELO MENOS UMA SERIE:\n\n");
		printf("%-9.9s %-20.20s %-12.12s %-10.10s %-10.10s %-13.13s\n","MATRICULA","NOME DO FREQUENTADOR","CPF","PESO","SEXO","DATA INGRESSO");
		while (!feof(arq))
		{
			if(fread(&freq, sizeof(Frequentador), 1, arq)!=0)
			{
				//Verificando se o Frequentador executou pelo menos uma serie
		    	if(verificaFrequentadorAtividade(freq.matricula,NOME_ARQ_ATIV) != 0)
		    	{
						transformaIntData(freq.dataIngresso, &dia, &mes, &ano);
						printf("%-9d %-20.20s %-12.12s %-10.2f %-10c %2.2d/%2.2d/%2.2d\n", freq.matricula, freq.nome, freq.CPF, freq.peso, freq.sexo, dia, mes, ano);
				}	
			}
		}
		fclose (arq); 
	}	
	getch();
}

//Objetivo: Informar Atividades Desenvolvidas por um Frequentadorem uma faixa de datas dia/mes/ano de .. ate ...
//Parametros: Endereco da String com o nome do Arquivo de Frequentadores
//Retorno: Nenhum
void informaAtivFreq(char *nomeArq)
{
	FILE *arqAtiv;
	Frequentador freq;
	Serie serie;
	Atividade atividade;
	int matricula, nroFreq, nroSerie, flag, dataDe, dataAte, dia, mes, ano;
	int qtdTempo=0;
	float calorias=0;
	
	//Lendo o Frequentador
	apresentaOrdenadosFrequentadores(nomeArq);
	matricula = leValidaInt("\nInforme a matricula do Frequentador a pesquisar: ","\nNao houve leitura!",MIN_MATRICULA,MAX_MATRICULA);
	nroFreq = obtemNroFreq(matricula, nomeArq);
	system("cls");
	if (nroFreq == 0){
		printf("Frequentador nao cadastrado\n");
		getch();
		return;
	}
	else 
	{
		freq = obtemDadosFreq(nroFreq, nomeArq, &flag);
		if (flag == 1 )
		{
			//Verificando se o frequentador fez alguma atividade
			if(verificaFrequentadorAtividade(matricula,NOME_ARQ_ATIV)==0)
			{
				printf("Frequentador nao fez nenhuma atividade!\n");
				getch();
				return;
			}
			
			//Obtendo as datas de... ate...
			dataDe = leValidaData("Informe Data de Inicio de Pesquisa:");
			dataAte = leValidaData("Informe Data de Final de Pesquisa:");
			
			system("cls");
			//Apresentando dados do frequentador
			transformaIntData(freq.dataIngresso, &dia, &mes, &ano);
			apresentaDadosAcademia();
			printf("FREQUENTADOR:\n\n");
			printf("%-9.9s %-20.20s %-12.12s %-10.10s %-10.10s %-13.13s\n","MATRICULA","NOME DO FREQUENTADOR","CPF","PESO","SEXO","DATA INGRESSO");
			printf("%-9d %-20.20s %-12.12s %-10.2f %-10c %2.2d/%2.2d/%2.2d\n", freq.matricula, freq.nome, freq.CPF, freq.peso, freq.sexo, dia, mes, ano);
			
			//Obtendo dados Atividades
			arqAtiv = abreArquivo(NOME_ARQ_ATIV,"rb");
			if(arqAtiv != NULL) 
			{
				printf("\n\nATIVIDADES DESENVOLVIDAS:\n\n");
				printf("%-10.10s %-10.10s %-10.10s\n","ID SERIE","DATA","HORA");
				while(!feof(arqAtiv))
				{
					if(fread(&atividade,sizeof(Atividade),1,arqAtiv)==1)
					{
						if(atividade.matricula == matricula && atividade.dataInicio>=dataDe && atividade.dataInicio<=dataAte)
						{
							//Apresentando Atividades que fez o frequentador
							transformaIntData(atividade.dataInicio,&dia,&mes,&ano);
							printf("%-10d %02d/%02d/%d %2.2d:%2.2d:%2.2d\n", atividade.id,dia,mes,ano, atividade.hora, atividade.minutos, atividade.segundos);
						
							//Obtendo dados das series
							nroSerie = obtemNroSerie(atividade.id,NOME_ARQ_SERIES);
							serie = obtemDadosSerie(nroSerie,NOME_ARQ_SERIES,&flag);
							if(flag==1)
							{
								qtdTempo+=serie.duracao;
								calorias+=serie.calorias;
							}
						}
					}
				}
			printf("\n\nTEMPO DE TREINAMENTO: %d Minutos\nCALORIAS QUEIMADAS: %.2f\n",qtdTempo,calorias);	
			fclose(arqAtiv);
			}
		} 
	getch();
	}
}

//Objetivo: Listar todos os frequentadores que utilizaram a academia em uma faixa de datas (de ... ate...) (dia/mes/ano)
//Parametros: Nenhum
//Retorno: Nenhum
void utilizaAcademiaFreq()
{
	FILE *arq;
	Frequentador *freq=NULL, *freqAux, freqLido;
	int qtdFreq=0, cont=0, nroFreq, flag, flagRep=0, dataDe, dataAte, dia, mes, ano;
	Atividade atividade;
	
	//Obtendo as datas de... ate...
	dataDe = leValidaData("Informe Data de Inicio de Pesquisa:");
	dataAte = leValidaData("Informe Data de Final de Pesquisa:");
	
	system("cls");
			
	if ((arq=abreArquivo(NOME_ARQ_ATIV, "rb")) != NULL)
	{
		while(!feof(arq))
		{
			if(fread(&atividade, sizeof(Atividade), 1, arq) == 1)
			{
				if(atividade.dataInicio>=dataDe && atividade.dataInicio<=dataAte)	
				{
					nroFreq = obtemNroFreq(atividade.matricula,NOME_ARQ);
					freqLido = obtemDadosFreq(nroFreq,NOME_ARQ,&flag);
					if(flag == 1)
					{
						//Verificando se o Frequentador esta repetido no vetor
						for(cont=0;cont<qtdFreq;cont++)
						{
							if(freq[cont].matricula==freqLido.matricula)
							{
								flagRep=1;
								break;
							}
						}
						if(flagRep!=1)
						{
							freqAux= (Frequentador* ) realloc(freq, sizeof(Frequentador)*(qtdFreq+1));
							if (freqAux != NULL)
							{
								freq=freqAux;
								freq[qtdFreq]=freqLido;
								qtdFreq++;
							}
						}
					}
				}
			}
		flagRep=0;
		}
		
		fclose (arq);
	} 
	
	if (qtdFreq != 0 )
	{
		ordenarFrequentador(freq, qtdFreq);
		apresentaDadosAcademia();
		printf("%-9.9s %-20.20s %-12.12s %-10.10s %-10.10s %-13.13s\n","MATRICULA","NOME DO FREQUENTADOR","CPF","PESO","SEXO","DATA INGRESSO");
		for (cont=0; cont < qtdFreq ; cont++)
		{
			transformaIntData(freq[cont].dataIngresso, &dia, &mes, &ano);
			printf("%-9d %-20.20s %-12.12s %-10.2f %-10c %2.2d/%2.2d/%2.2d\n", freq[cont].matricula, freq[cont].nome, freq[cont].CPF, freq[cont].peso, freq[cont].sexo, dia, mes, ano);
		}
		getch();
		free(freq);
	}else
	{
		printf("Nenhum Frequentador utilizou a Academia na faixa de datas informadas!\n");
		getch();
	}	
}

//Objetivo: Obter Maior Data de utilizacao de academia dado um Frequetador
//Parametros: Frequentador
//Retorno: Maior Data ou -1 se o frequentador nao fez nenhum atividade
int maiorDataUtilizacao(Frequentador freq)
{
	FILE *arq;
	int dataTemp = 0, qtdAtiv=0;
	Atividade ativ;
	
	arq = abreArquivo(NOME_ARQ_ATIV,"rb");
	if(arq!=NULL)
	{
		while(!feof(arq))
		{
			if(fread(&ativ,sizeof(Atividade),1,arq) == 1)
			{
				if(freq.matricula == ativ.matricula && ativ.dataInicio>dataTemp)
				{
					dataTemp = ativ.dataInicio;
					qtdAtiv++;
				}
			}
		}
	fclose(arq);
	}
	if(qtdAtiv == 0)
	{
		return -1;
	}
	return dataTemp;
}

//Objetivo: Apresentar Frequentadores que nao utilizam a academia a uma quantidade de dias definida pelo usuario
//Parametros: Nenhum
//Retorno: Nenhum
void naoUtilizaAcademiaFreq()
{
	FILE *arq;
	Frequentador *freq=NULL, *freqAux, freqLido;
	Atividade atividade;
	int qtdFreq=0, qtdDias, cont=0, nroFreq, flag, flagRep=0, dia, mes, ano, dataComparar;
	
	//Obtendo qtd de dias e data atual do sistema
	obtemDataAtual(&dia,&mes,&ano);
	qtdDias = leValidaInt("Informe Quantidade de Dias a pesquisar: ","Dados invalidos!, Digite Novamente",MIN_DIAS,MAX_DIAS);
	restaDiasData(&dia,&mes,&ano,qtdDias);
	dataComparar= transformaDataInt(dia,mes,ano);
	
	system("cls");
			
	if ((arq=abreArquivo(NOME_ARQ, "rb")) != NULL){
		while (!feof(arq)){
			if(fread(&freqLido, sizeof(Frequentador), 1, arq) == 1)
			{
				if(dataComparar>maiorDataUtilizacao(freqLido))	
				{
					freqAux= (Frequentador* ) realloc(freq, sizeof(Frequentador)*(qtdFreq+1));
					if (freqAux != NULL ){
						freq=freqAux;
						freq[qtdFreq]=freqLido;
						qtdFreq++;
					}
				}
			}
		}
		
		fclose (arq);
	} 
	
	if (qtdFreq != 0 )
	{
		ordenarFrequentador(freq, qtdFreq);
		apresentaDadosAcademia();
		printf("%-9.9s %-20.20s %-12.12s %-10.10s %-10.10s %-13.13s\n","MATRICULA","NOME DO FREQUENTADOR","CPF","PESO","SEXO","DATA INGRESSO");
		for (cont=0; cont < qtdFreq ; cont++)
		{
			transformaIntData(freq[cont].dataIngresso, &dia, &mes, &ano);
			printf("%-9d %-20.20s %-12.12s %-10.2f %-10c %2.2d/%2.2d/%2.2d\n", freq[cont].matricula, freq[cont].nome, freq[cont].CPF, freq[cont].peso, freq[cont].sexo, dia, mes, ano);
		}
		getch();
		free(freq);
	} else {
		printf("Pesquisa nao retornou nenhum dado!\n");
		getch();
	}
}


