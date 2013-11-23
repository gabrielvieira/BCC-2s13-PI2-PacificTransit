#include "tempo.h"
#include <allegro5/allegro.h>

double tempoInicial = 0;

void iniciarTimer()
{
    tempoInicial = al_get_time();
}
 
double obterTempoTimer()
{
    return al_get_time() - tempoInicial;
}