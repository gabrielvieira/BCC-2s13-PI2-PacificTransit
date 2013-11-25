//
//  Created by GABRIEL VIEIRA on 10/09/13.
//  Copyright (c) 2013 GABRIEL VIEIRA. All rights reserved.
//



int RandomInteger(int low, int high);

char* devolveCaminho();
int *four_random_numbers();
void aloca_palcas(int* random_numbers);

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
 
    al_set_window_title(janela, "Pacific Transit 1.3.5");
 
    fonte = al_load_font("font/SourceCodePro-Regular.ttf", 60, 0);
    fonte2 = al_load_font("font/SourceCodePro-Regular.ttf", 30, 0);
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
 
    fundo = al_load_bitmap("img/back.png");
    if (!fundo)
    {
        fprintf(stderr, "Falha ao carregar imagem de fundo.\n");
        al_destroy_display(janela);
        al_destroy_event_queue(fila_eventos);
        return false;
    }

    menu = al_load_bitmap("img/menu.jpg");
    if (!menu)
    {
        fprintf(stderr, "Falha ao carregar imagem de menu.\n");
        al_destroy_display(janela);
        al_destroy_event_queue(fila_eventos);
        return false;
    }

    //imagens
    carro = al_load_bitmap("img/carro.png");
    if (!carro)
    {
        fprintf(stderr, "Falha ao carregar imagem do carro .\n");
        al_destroy_display(janela);
        al_destroy_event_queue(fila_eventos);
        return false;
    }

    carro2 = al_load_bitmap("img/carro2.png");
    if (!carro2)
    {
        fprintf(stderr, "Falha ao carregar imagem do carro2 .\n");
        al_destroy_display(janela);
        al_destroy_event_queue(fila_eventos);
        return false;
    }

    beer = al_load_bitmap("img/beer.png");
    if (!beer)
    {
        fprintf(stderr, "Falha ao carregar imagem da cerveja .\n");
        al_destroy_display(janela);
        al_destroy_event_queue(fila_eventos);
        return false;
    }

    phone = al_load_bitmap("img/phone.png");
    if (!phone)
    {
        fprintf(stderr, "Falha ao carregar imagem da cerveja .\n");
        al_destroy_display(janela);
        al_destroy_event_queue(fila_eventos);
        return false;
    }

   


    transparent = al_load_bitmap("img/transparent.png");
    if (!transparent)
    {
        fprintf(stderr, "Falha ao carregar imagem das placas .\n");
        al_destroy_display(janela);
        al_destroy_event_queue(fila_eventos);
        return false;
    }

    lost1 = al_load_bitmap("img/lost1.jpg");
    if (!lost1)
    {
        fprintf(stderr, "Falha ao carregar imagem das placas .\n");
        al_destroy_display(janela);
        al_destroy_event_queue(fila_eventos);
        return false;
    }

    lost2 = al_load_bitmap("img/lost2.jpg");
    if (!lost1)
    {
        fprintf(stderr, "Falha ao carregar imagem das placas .\n");
        al_destroy_display(janela);
        al_destroy_event_queue(fila_eventos);
        return false;
    }

    if(!al_install_audio())
    {
     fprintf(stderr, "Falha ao inicializar o audio.\n");
        return false;
     }
    
    if(!al_init_acodec_addon())
    {
        fprintf(stderr, "Falha ao iniciar o audio codec.!\n");
      return false;
    }
    
    if (!al_reserve_samples(1))
    {
        fprintf(stderr, "Falha ao alocar canais de audio.\n");
        return false;
    }

    som = al_load_sample("sound/song.wav"); 

   
 //IMAGENS DE EXPLICAÇÃO
    
    ex1 = al_load_bitmap("img/ex1.png");
    if (!ex1)
    {
        fprintf(stderr, "Falha ao carregar imagem das placas .\n");
        al_destroy_display(janela);
        al_destroy_event_queue(fila_eventos);
        return false;
    }


    ex2 = al_load_bitmap("img/ex2.png");
    if (!ex2)
    {
        fprintf(stderr, "Falha ao carregar imagem das placas .\n");
        al_destroy_display(janela);
        al_destroy_event_queue(fila_eventos);
        return false;
    }

    final = al_load_bitmap("img/final.png");
    if (!final)
    {
        fprintf(stderr, "Falha ao carregar imagem das placas .\n");
        al_destroy_display(janela);
        al_destroy_event_queue(fila_eventos);
        return false;
    }

    perdeuFalsa = al_load_bitmap("img/placaf.png");
    if (!perdeuFalsa)
    {
        fprintf(stderr, "Falha ao carregar imagem das placas .\n");
        al_destroy_display(janela);
        al_destroy_event_queue(fila_eventos);
        return false;
    }
       
    //ALOCANDO PLACAS DO POSTER    
    placas[4] = al_load_bitmap("img/placas/fake1.png");
    placas[5] = al_load_bitmap("img/placas/fake2.png");
    placas[6] = al_load_bitmap("img/placas/fake3.png");
    placas[7] = al_load_bitmap("img/placas/fake4.png");
    

    al_register_event_source(fila_eventos, al_get_keyboard_event_source());
    al_register_event_source(fila_eventos, al_get_display_event_source(janela));

    return true;
}