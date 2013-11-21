//
//  Created by GABRIEL VIEIRA on 10/09/13.
//  Copyright (c) 2013 GABRIEL VIEIRA. All rights reserved.
//

// Inicializar as variaveis

int RandomInteger(int low, int high);

char* devolveCaminho()
{
    char *retorno = malloc(30*sizeof(char));
    char nomeImagem[15];
    char caminho[15];
    int r = RandomInteger(1,4);
    char str[10];

    strcpy(caminho,"img/placas/");
    strcpy(nomeImagem,"placa");

    sprintf(str, "%d", r);
    strcat(nomeImagem, str);
    strcat(caminho, nomeImagem);
    strcat(caminho, ".png");

    strcpy(retorno,caminho);

    printf("%s\n", caminho);

    return retorno;
}

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
        

    //ALOCAR IMAGENS DAS PLACAS
    //GAMBIARRAS
    
    //funcao que devolve um caminho aleatorio 
    //de caminho de imagem , buscando uma futura expanção de imagens
    //devolveCaminho();

    imgPlate1 = al_load_bitmap("img/placas/placa1.png");
    if (!imgPlate1)
    {
        fprintf(stderr, "Falha ao carregar imagem das placas .\n");
        al_destroy_display(janela);
        al_destroy_event_queue(fila_eventos);
        return false;
    }

    imgPlate2 = al_load_bitmap("img/placas/placa2.png");
    if (!imgPlate2)
    {
        fprintf(stderr, "Falha ao carregar imagem das placas .\n");
        al_destroy_display(janela);
        al_destroy_event_queue(fila_eventos);
        return false;
    }

    imgPlate3 = al_load_bitmap("img/placas/placa3.png");
    if (!imgPlate2)
    {
        fprintf(stderr, "Falha ao carregar imagem das placas .\n");
        al_destroy_display(janela);
        al_destroy_event_queue(fila_eventos);
        return false;
    }

    imgPlate4 = al_load_bitmap("img/placas/placa4.png");
    if (!imgPlate2)
    {
        fprintf(stderr, "Falha ao carregar imagem das placas .\n");
        al_destroy_display(janela);
        al_destroy_event_queue(fila_eventos);
        return false;
    }

    imgFake1 = al_load_bitmap("img/placas/fake1.png");
    if (!imgFake1)
    {
        fprintf(stderr, "Falha ao carregar imagem das fake .\n");
        al_destroy_display(janela);
        al_destroy_event_queue(fila_eventos);
        return false;
    }

    

    placas[0] = imgPlate1;
    placas[1] = imgPlate2;
    placas[2] = imgPlate3;
    placas[3] = imgPlate4;
    placas[4] = imgFake1;
    
    al_register_event_source(fila_eventos, al_get_keyboard_event_source());
    al_register_event_source(fila_eventos, al_get_display_event_source(janela));

    return true;
}