#include "estruturas.h"

void leAtividade(char *nomeArq);
void apresentaDadosAtividades(char *nomeArq);
int obtemNroAtividade(int id,int matricula,int dataInicio, char *nomeArq);
Atividade obtemDadosAtividade(int nroAtividade, char *nomeArq, int *flag);
void excluiAtividade(char *nomeArq);
int verificaFrequentadorAtividade(int matricula, char *nomeArq);
int verificaSerieAtividade(int id, char *nomeArq);
void apresentaDadosAtividadeChave(char *nomeArq);
