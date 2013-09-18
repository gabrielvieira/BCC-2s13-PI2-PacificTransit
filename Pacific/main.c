#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <stdio.h>
#include <stdbool.h>
   
 //Define o tamanho da tela
const int LARGURA_TELA = 640;
const int ALTURA_TELA = 480;
 
// Variaveis especiais do ALLEGRO 
ALLEGRO_DISPLAY *janela = NULL;
ALLEGRO_EVENT_QUEUE *fila_eventos = NULL;
ALLEGRO_BITMAP *fundo = NULL;
ALLEGRO_BITMAP *carro = NULL;
ALLEGRO_FONT *fonte = NULL;
ALLEGRO_KEYBOARD_STATE *estado_teclado = NULL;
 
// Inicializar as variaveis
bool inicializar()
{
    if (!al_init())
    {
        fprintf(stderr, "Falha ao inicializar a Allegro.\n");
        return false;
    }
 
    al_init_font_addon();
 
    if (!al_init_ttf_addon())
    {
        fprintf(stderr, "Falha ao inicializar add-on allegro_ttf.\n");
        return false;
    }
 
    if (!al_init_primitives_addon())
    {
        fprintf(stderr, "Falha ao inicializar add-on allegro_primitives.\n");
        return false;
    }

    if (!al_init_image_addon())
    {
        fprintf(stderr, "Falha ao inicializar add-on allegro_image.\n");
        return false;
    }
 
    if (!al_install_keyboard())
    {
        fprintf(stderr, "Falha ao inicializar o teclado.\n");
        return false;
    }
 
    janela = al_create_display(LARGURA_TELA, ALTURA_TELA);
    if (!janela)
    {
        fprintf(stderr, "Falha ao criar janela.\n");
        return false;
    }
 
    al_set_window_title(janela, "Pacific Transit 1.0");
 
    fonte = al_load_font("SourceCodePro-Regular.ttf", 72, 0);
    if (!fonte)
    {
        fprintf(stderr, "Falha ao carregar \"fonte comic.ttf\".\n");
        al_destroy_display(janela);
        return false;
    }
 
    fila_eventos = al_create_event_queue();
    if (!fila_eventos)
    {
        fprintf(stderr, "Falha ao criar fila de eventos.\n");
        al_destroy_display(janela);
        return false;
    }
 
    fundo = al_load_bitmap("bg.png");
    if (!fundo)
    {
        fprintf(stderr, "Falha ao carregar imagem de fundo.\n");
        al_destroy_display(janela);
        al_destroy_event_queue(fila_eventos);
        return false;
    }
 
    carro = al_load_bitmap("carro.png");
    if (!carro)
    {
        fprintf(stderr, "Falha ao carregar imagem do carro .\n");
        al_destroy_display(janela);
        al_destroy_event_queue(fila_eventos);
        return false;
    }

    al_register_event_source(fila_eventos, al_get_keyboard_event_source());
    al_register_event_source(fila_eventos, al_get_display_event_source(janela));
 
    return true;
}


void movimentar(int tecla, float *x, float *y, float *posx , float *posy,float *tamx , float *tamy)
{
    float temp;

    if (*x >= LARGURA_TELA)
    {
        *x = 30.0;
    }
    else if (*x <= 0)
    {
        *x = LARGURA_TELA - 30;
    }

    if (*y >= ALTURA_TELA)
    {
        *y = 30.0;
    }
    else if (*y <= 0)
    {
        *y = ALTURA_TELA - 30;
    }

    if (tecla == 1 || tecla == 2 )
    {
        if (*tamy < *tamx)
        {
            temp = *tamx;
            *tamx = *tamy;
            *tamy = temp;
        }
    }
    else if (tecla == 3 || tecla == 4)
    {
        if (*tamy > *tamx)
        {
            temp = *tamx;
            *tamx = *tamy;
            *tamy = temp;
        }
    }

    if (tecla)
    {
        al_draw_bitmap(fundo, 0, 0, 0);
 
        switch (tecla)
        {
        case 1:
             *y = *y - 1.5;
             *posx = 15;
             *posy = 202;
        break;
        case 2:
        *y = *y + 1.5;
            *posx = 16;
             *posy = 5;
        break;
        case 3:
        *x = *x - 1.5;
        *posx = 5;
             *posy = 81;
         break;
        case 4:
             *x = *x + 1.5;
             *posx = 5;
             *posy = 148;
           break;
        }
 
        // tecla = 0;
    }
}
 
int main(void)
{
    bool sair = false;
    int tecla = 0;
    float raio = 30.0;
    float x = raio;
    float y = raio;
    float posx = 16;
    float posy = 5;
    float tamx = 36;
    float tamy = 60;

   // al_convert_mask_to_alpha(carro, al_map_rgb(106,70,47));

    if (!inicializar())
    {
        return -1;
    }
 
    al_draw_bitmap(fundo, 0, 0, 0);
    
    while (!sair)
    {

            while(!al_is_event_queue_empty(fila_eventos))
            {
                ALLEGRO_EVENT evento;
                al_wait_for_event(fila_eventos, &evento);
                
                    if(evento.type == ALLEGRO_EVENT_KEY_DOWN)
                    {
                        switch(evento.keyboard.keycode)
                        {
                        case ALLEGRO_KEY_UP:
                            tecla = 1;
                            printf("tecla1\n");
                            break;
                        case ALLEGRO_KEY_DOWN:
                            tecla = 2;
                            printf("tecla2\n");
                            break;
                        case ALLEGRO_KEY_LEFT:
                            tecla = 3;
                            printf("tecla3\n");
                            break;
                        case ALLEGRO_KEY_RIGHT:
                            tecla = 4;
                            printf("tecla4\n");
                            break;
                        }
                    }
                    else if(evento.type == ALLEGRO_EVENT_KEY_UP)
                    {
                        printf("parou\n");
                        tecla = 0;
                    }
                    
                    if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
                    {
                        sair = true;
                    } 
                
            }
 
        movimentar(tecla,&x,&y,&posx,&posy,&tamx,&tamy);
       
        al_draw_bitmap_region(carro, posx, posy, tamx , tamy , x ,y ,0);
        //al_draw_filled_circle(x, y, raio, al_map_rgb(255, 0, 0));
        al_flip_display();

        al_rest(0.005);
    }
 
    al_destroy_display(janela);
    al_destroy_event_queue(fila_eventos);
 
    return 0;
}
 
