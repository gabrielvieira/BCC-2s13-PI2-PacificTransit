#include "header.h"
#include "start.h"
#include "move.h" 

int main(void)
{
    //DECLARAÇÃO DE VARIAVEIS
    bool sair = false;
    int tecla = 0;
    float raio = 30.0;
    float x = raio;
    float y = raio;
    float posx = 16;
    float posy = 5;
    float tamx = 36;
    float tamy = 60;
    float car1 = 30;
    float car2 = 200;
    float car3 = 200;
    bool menu_ativo = true;
    bool key_release = true;
    bool pause = false;
    //TESTE CONVERSAO DE INT PARA STRING
    int aInt = 368;
    char str[30];
    sprintf(str, "%d", aInt);
    strcat(str, " concatena");

    //VERIFICA SE A BIBLIOTECA DO ALLEGRO FOI INICIADA CORRETAMENTE
    if (!inicializar())
    {
        return -1;
    }
    //DESENHA IMAGEM DE FUNDO
    al_draw_bitmap(menu, 0, 0, 0);
    //SOM DO JOGO
    //al_play_sample(som, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_LOOP,NULL);
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
            if (pause)
            {
                al_draw_text(fonte, al_map_rgb(255, 255, 255), LARGURA_TELA / 2,
                ALTURA_TELA / 2 - al_get_font_ascent(fonte) / 2,
                ALLEGRO_ALIGN_CENTRE, "Pause");
            }
            else
            {
                al_draw_bitmap_region(fundo, 70, 1, LARGURA_TELA , ALTURA_TELA , 0 ,0 ,0);
                auto_car(&car1,&car2,&car3);
                player_car(tecla,&x,&y,&posx,&posy,&tamx,&tamy);
            }
            
        }
        
        //MOSTRAR A TELA
        al_flip_display();
        //PARA CONTROLAR O TEMPO DE EECUÇÃO
        al_rest(0.005);
    }
 
    //FECHA O JOGO AO SAIR DO LOOP PRINCIPAL
    al_destroy_display(janela);
    al_destroy_event_queue(fila_eventos);
 
    return 0;
}
 
