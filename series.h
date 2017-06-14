#include "estruturas.h"

void leSerie(char *nomeArq);
int obtemNroSerie(int id, char *nomeArq);
void apresentaDadosSeries(char *nomeArq);
void apresentaDadosSerieID(char *nomeArq);
void alteraDadosSerie(char *nomeArq);
void excluiSerie(char *nomeArq);
void gravaSerie(Serie *serie,int numSerie, char *nomeArq);
Serie obtemDadosSerie(int nroSerie, char *nomeArq, int *flag);

