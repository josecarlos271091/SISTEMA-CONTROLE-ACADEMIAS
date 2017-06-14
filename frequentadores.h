#include "estruturas.h"

void leDados(char *nomeArq);
void apresentaDadosFreq(char *nomeArq);
int obtemNroFreq(int matricula, char *nomeArq);
void apresentaDadosMat(char *nomeArq);
void alteraDadosFreq(char *nomeArq);
void excluiFreq(char *nomeArq);
void gravaFrequentador(Frequentador *frequentador,int nrFreq, char *nomeArq);
Frequentador obtemDadosFreq(int nroFreq, char *nomeArq, int *flag);
int obtemQtdeFrequentadores(char *nomeArq);
void apresentaOrdenadosFrequentadores(char *nomeArq);
void pesquisaFrequentadores(char *nomeArq);
void ordenarFrequentador(Frequentador *freq, int qtdFreq);
int verificaOrdenacaoNome(const void *p1, const void *p2);
void apresentaFrequentadoresExecSerie(char *nomeArq);
void informaAtivFreq(char *nomeArq);
void utilizaAcademiaFreq();
void naoUtilizaAcademiaFreq();
int maiorDataUtilizacao(Frequentador freq);
