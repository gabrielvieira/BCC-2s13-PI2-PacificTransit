#include "tempo.h"
#include <allegro5/allegro.h>

double tempoInicial = 0;

//INICIA A CONTAGEM DE TEMPO
void iniciarTimer()
{
    tempoInicial = al_get_time();
}

//OBTER DIFERENÇA DE TEMPO 
double obterTempoTimer()
{
    return al_get_time() - tempoInicial;
}