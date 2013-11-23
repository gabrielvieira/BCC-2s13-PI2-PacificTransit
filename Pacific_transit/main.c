//
//  Created by GABRIEL VIEIRA on 10/09/13.qqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqq
//  Copyright (c) 2013 GABRIEL VIEIRA. All rights reserved.
//

#include "header.h"
#include "start.h"
#include "move.h" 
#include "tempo.h"

//

int main(void)
{
    //placas[0].image = imgPlate3;

    
    srand(time(NULL));
    //DECLARAÇÃO DE VARIAVEIS
    bool sair = false;
    int i;
    bool move_permit = true;
    int tecla = 0;
    int testeTime = 0;
    
    bool pause = false;
    float telay = 600;
    int frame = 0;
    bool limitado = true;
    
     

    //TESTE CONVERSAO DE INT PARA STRING
    char stringPontuacao[40] = "Pontuação ";
    char str[10];

    // STRUCT FUNCIONANDO :)
    //Iniciando os carros e objetos
    Car *playerCar = malloc(sizeof(Car));
   // Car *autoCar = malloc(5 * sizeof(Car));
    Object *beer = malloc(sizeof(Object));
    Object *phone = malloc(sizeof(Object));
    Object *plate1 = malloc(sizeof(Object));
    Object *plate2 = malloc(sizeof(Object));
    
    //VERIFICA SE A BIBLIOTECA DO ALLEGRO FOI INICIADA CORRETAMENTEqqq
    //al_draw_bitmap(preMenu, 0, 0, 0);
    //al_flip_display(); 

    if (!inicializar())
    {
        return -1;
    }

     
    //DESENHA IMAGEM DE FUNDO
    al_draw_bitmap(menu, 0, 0, 0);
    al_flip_display();
    //SOM DO JOGO
    al_play_sample(som, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_LOOP,NULL);

    //LOOP PRINCIPAL DO JOGO
    while (!sair)
    {
    	//tempo para controle de fps
        iniciarTimer();

        //gerar pontiação
        strcpy(stringPontuacao,"Pontuação ");
        sprintf(str, "%d", pontuacao);
    	strcat(stringPontuacao, str);

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
                    tecla = 5;  
                   // menu_ativo = false;                          
                    break;
                case ALLEGRO_KEY_BACKSPACE:
                    tecla = 6;                        
                    break;
                case ALLEGRO_KEY_R:
                    //perder = false; 
                    //reset = false;                         
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
        if (state == 0)
        {

            al_draw_bitmap(menu, 0, 0, 0);
            if (reset)
            {
                int r1 = RandomInteger(0,4);
                int r2 = RandomInteger(0,4);

                for (i = 0; i < 6; ++i)
                {
                    use_positions[i] = 0;
                    use_positions_obj[i] = 0;
                }

                playerCar->number = 5;
                init_car(playerCar);
                init_object(beer);
                init_object(phone);

                init_object(plate1);
                init_object(plate2);
                
                phone->type = 1;
                beer->type = 2;

                plate1->image.image = placas[r1];
                plate1->type = 3;

                plate2->image.image = placas[r2];
                plate2->type = 3;

                reset = false;
                countBatida = 10;
                pontuacao = 0;
            }

            if (tecla == 5)
            {
                state++;
            }
            
            tecla = 0;
        }
        
        if (state == 1)
        {
            al_draw_bitmap(ex1, 0, 0, 0);
            if (tecla == 5)
            {
                state++;
            }

            if (tecla == 6)
            {
                state--;
            }
            
            tecla = 0;
        }    

        if (state == 2)
        {
            al_draw_bitmap(ex2, 0, 0, 0);
            if (tecla == 5)
            {
                state++;
            }
            
            if (tecla == 6)
            {
                state--;
            }

            tecla = 0;
        }   

        if(state == 3)
        {
            if (pause)
            {
                al_draw_text(fonte, al_map_rgb(255, 255, 255), LARGURA_TELA / 2,
                ALTURA_TELA / 2 - al_get_font_ascent(fonte) / 2,
                ALLEGRO_ALIGN_CENTRE, "Pause");
            }    
            else
            {
                move_screen(&telay);
                move_player_car(tecla,playerCar,&move_permit);
                
                move_beer(beer);
                move_phone(phone);

                move_plate(plate1);
                move_plate(plate2);

                colision_bad_obj(playerCar,beer);
                colision_bad_obj(playerCar,phone);
                
                colision_good_obj(playerCar,plate1);
                colision_good_obj(playerCar,plate2);
            }
           
            al_draw_text(fonte2, al_map_rgb(255, 0, 0), LARGURA_TELA * 0.99, ALTURA_TELA * 0.01,
            ALLEGRO_ALIGN_RIGHT, stringPontuacao);
        }

        if (state == 4)
        {
            if (tecla == 5)
            {
               state++;
            }

            tecla = 0;
        }

         if (state == 5)
        {
            float x1 = 120;
            float x2 = 480;
            float y1 = 110;
            float y2 = 350;

            al_draw_bitmap(final, 0, 0, 0);
            al_draw_bitmap(placas_sig[0], x1, y1, 0);
            al_draw_bitmap(placas_sig[1], x2, y1, 0);
            al_draw_bitmap(placas_sig[2], x1, y2, 0);
            al_draw_bitmap(placas_sig[3], x2, y2, 0);
            if (tecla == 5)
            {
               state = 0;
               reset = true;
            }

            tecla = 0;
        }
        
        //PARA CONTROLAR O TEMPO DE EECUÇÃO
        frame++;
        if (limitado && (obterTempoTimer() < 1.0 / FRAMES_POR_SEGUNDO))
        {
            al_rest((1.0 / FRAMES_POR_SEGUNDO) - obterTempoTimer());
        }
        al_flip_display();    
    }
 
    //FECHA O JOGO AO SAIR DO LOOP PRINCIPAL
    al_destroy_display(janela);
    al_destroy_event_queue(fila_eventos);
 
    return 0;
}
 

