//
//  Created by GABRIEL VIEIRA on 10/09/13.
//  Copyright (c) 2013 GABRIEL VIEIRA. All rights reserved.
//

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h> 
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_primitives.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> 
#include <time.h>

 //Define o tamanho da tela
const int LARGURA_TELA = 800;
const int ALTURA_TELA = 600;

//tamanho do carro   
const float ALTURA_CARRO = 60;
const float LARGURA_CARRO = 36;

//limites da rua para printar na tela
const float LIMITE_IMG_SUP = 220;
const float LIMITE_IMG_INF = 290;

//vetor de posições fixas da tela
float positions[] = {245,298,353,415,470,523};

//teste
// Variaveis especiais do ALLEGRO 
ALLEGRO_SAMPLE *som;
ALLEGRO_DISPLAY *janela = NULL;
ALLEGRO_EVENT_QUEUE *fila_eventos = NULL;
ALLEGRO_BITMAP *fundo = NULL;
ALLEGRO_BITMAP *menu = NULL;
ALLEGRO_BITMAP *carro = NULL;
ALLEGRO_BITMAP *carro2 = NULL;
ALLEGRO_FONT *fonte = NULL;
ALLEGRO_FONT *fonte2 = NULL;

//struct para os carros
typedef struct
	{
		ALLEGRO_BITMAP *image;

		float imageX;
		float imageY;
		
		float width;
		float height;

		float x;
		float y;

	}Image;
	
	typedef struct
	{
		Image image;
		int position;
		
	}Car;

bool inicializar();


