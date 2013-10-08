//
//  Created by GABRIEL VIEIRA on 10/09/13.
//  Copyright (c) 2013 GABRIEL VIEIRA. All rights reserved.
//

#include "header.h"
#include "start.h"
#include "move.h" 

int main(void)
{
    //DECLARAÇÃO DE VARIAVEIS
    bool sair = false;
    bool move_permit = true;
    int tecla = 0;
    bool menu_ativo = true;
    bool pause = false;
    float telax = 50 ,telay = 600;

    //TESTE CONVERSAO DE INT PARA STRING
    int aInt = 368;
    char str[30];
    sprintf(str, "%d", aInt);
    strcat(str, " concatena");

    // STRUCT FUNCIONANDO :)
    Car *playerCar = malloc(sizeof(Car));
    Car *autoCar = malloc(3 * sizeof(Car));
    
    //VERIFICA SE A BIBLIOTECA DO ALLEGRO FOI INICIADA CORRETAMENTE
    if (!inicializar())
    {
        return -1;
    }

    init_car(playerCar);
    init_car(&autoCar[0]);
    autoCar[0].position = 3;
    autoCar[0].image.x = positions[3];

    printf("%d\n", autoCar[0].position);
    
    
 
    //DESENHA IMAGEM DE FUNDO
    al_draw_bitmap(menu, 0, 0, 0);

    //SOM DO JOGO
    al_play_sample(som, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_LOOP,NULL);

    //LOOP PRINCIPAL DO JOGO
    while (!sair)
    {
        //FILA DE EVENTOS
        while(!al_is_event_queue_empty(fila_eventos))
        {
            ALLEGRO_EVENT evento;
            al_wait_for_event(fila_eventos, &evento);
                
            //AGUARDANDO EVENTOS DO TECLADO
            if(evento.type == ALLEGRO_EVENT_KEY_DOWN)
            {
                switch(evento.keyboard.keycode)
                {
                case ALLEGRO_KEY_UP:
                    tecla = 1;
                    break;
                case ALLEGRO_KEY_DOWN:
                    tecla = 2; 
                    break;
                case ALLEGRO_KEY_LEFT:
                    tecla = 3;                            
                    break;
                case ALLEGRO_KEY_RIGHT:
                    tecla = 4;                           
                    break;
                case ALLEGRO_KEY_ENTER:
                    menu_ativo = false;                          
                    break;
                case ALLEGRO_KEY_M:
                    menu_ativo = true;                          
                    break;    
                case ALLEGRO_KEY_ESCAPE:
                    if (pause)
                    {
                        pause = false;
                    }
                    else
                    {
                        pause = true;
                    }                        
                    break;  
                }
            }
            else if(evento.type == ALLEGRO_EVENT_KEY_UP)
            {
                tecla = 0; 
                move_permit = true;
            }
                
            //FECHAR JANELA    
            if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            {
                sair = true;
            } 
            
        }

        //PROCESSAMENTO DAS ENTRADAS RECEBIDAS PELOS USUARIOS
        if (menu_ativo)
        {
            al_draw_bitmap(menu, 0, 0, 0);
        }
        else
        {
            move_screen(&telay);
            move_auto_car(&autoCar[0]);
           // move_auto_car(&autoCar[1]);
           
            if (pause)
            {
                al_draw_text(fonte, al_map_rgb(255, 255, 255), LARGURA_TELA / 2,
                ALTURA_TELA / 2 - al_get_font_ascent(fonte) / 2,
                ALLEGRO_ALIGN_CENTRE, "Pause");
            }
            else
            {
                move_player_car(tecla,playerCar,&move_permit);
            }

            al_draw_text(fonte2, al_map_rgb(255, 0, 0), LARGURA_TELA * 0.99, ALTURA_TELA * 0.01,
            ALLEGRO_ALIGN_RIGHT, "Pontuação");
        }

        //MOSTRAR A TELA
        al_flip_display();
        //PARA CONTROLAR O TEMPO DE EECUÇÃO
        al_rest(0.003);
    }
 
    //FECHA O JOGO AO SAIR DO LOOP PRINCIPAL
    al_destroy_display(janela);
    al_destroy_event_queue(fila_eventos);
 
    return 0;
}
 

