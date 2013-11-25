//
//  Created by GABRIEL VIEIRA on 10/09/13.
//  Copyright (c) 2013 GABRIEL VIEIRA. All rights reserved.
//

int RandomInteger(int low, int high)
{
    int k;
    double d;
    d = (double) rand( ) / ((double) RAND_MAX + 1);
    k = d * (high - low + 1);
    return low + k;
}

void swap_position(Car *car)
{
    int r = RandomInteger(0,5); 
    int temp = car->position;
    //trocar posição do carro na pista_livre
    car->position = pista_livre;
    pista_livre = temp;
    car->image.x = positions[car->position];
    //alterar velocidade do carro na pista_livre
    car->speed = car_speed[r];
}

void swap_position_obj(Object *obj)
{
    int temp = obj->position;
    use_positions_obj[temp] = 0;
    int r = RandomInteger(0,5); 

    while(use_positions_obj[r] != 0)
    {
        r = (r+1)%6; 
    }

    
    use_positions_obj[r] = 1;
    //troobj posição do objro na pista_livre
    obj->position = r;
    //qqqqpista_livre = temp;
    obj->image.x = positions[obj->position];
    //alterar velocidade do objro na pista_livre
    obj->speed = car_speed[r];
}

void screen_limit_down(Object *obj)
{
    if (obj->image.y >= 645)
    {
        int r = RandomInteger(0,7);
        obj->image.y = -45;
        swap_position_obj(obj);
        //printf("randomizou velo %f\n",obj->speed);
        //printf("placa %d\n",r );
        obj->image.image = placas[r];

        //countBatida = 10;
    }
}
//MOVIMENTAÇÃO DOS OBSTACULOS

void init_object(Object *obj)
{  
    int r ;
    r = RandomInteger(0,5);

    while(use_positions_obj[r] != 0)
    {
        r = (r+1)%6; 
    }

    use_positions_obj[r] = 1;

    obj->image.imageX = 0;
    obj->image.imageY = 0;
    obj->image.x = positions[r];
    obj->image.y = 0;
    //obj->image.image = beerqq;
    obj->position = r;
    obj->speed = car_speed[r];

}


void move_beer(Object *obj)
{
    screen_limit_down(obj);
    obj->image.y += obj->speed;
    al_draw_scaled_bitmap(beer,0,0,400,400, obj->image.x,obj->image.y, 45,45,0);  
}

void move_phone(Object *obj)
{
    screen_limit_down(obj);
    obj->image.y += obj->speed;
    al_draw_scaled_bitmap(phone,0,0,512,512, obj->image.x,obj->image.y, 45,45,0);  
}

void move_plate(Object *obj)
{
    screen_limit_down(obj);
    obj->image.y += obj->speed;
    al_draw_scaled_bitmap(obj->image.image,0,0,150,150, obj->image.x,obj->image.y, 45,45,0);  
}
//MOVIMENTAÇÃO DOS CARROS

void colision_car(Car *car_player , Car *auto_car)
{ 
    if ((auto_car->position == car_player->position) 
    && ((auto_car->image.y - car_player->image.y) < 60 && (auto_car->image.y - car_player->image.y) > -60))
    {
        printf("Colidiu pista_livre %d\n",auto_car->position );
        
    }
}

void colision_bad_obj(Car *car_player , Object *obj)
{ 
    if ((obj->position == car_player->position) 
    && ((obj->image.y - car_player->image.y) < 45 && (obj->image.y - car_player->image.y) > -45))
    {   
       if (obj->type == 2)
       {
            //printf("colidiu com a cerveja \n");
            al_draw_bitmap(lost2, 0, 0, 0);
            state = 4;
       }
       else
       {
           //printf("colidiu com o celular\n");
            al_draw_bitmap(lost1, 0, 0, 0);
            state = 4;
       }
       
    }
}

void colision_good_obj(Car *car_player , Object *obj)
{ 
    int perder = 0;
    int i;

    if ((obj->position == car_player->position) 
    && ((obj->image.y - car_player->image.y) < 45 && (obj->image.y - car_player->image.y) > -45))
    {
        for (i = 4; i < 8; ++i)
        {
            //printf("passei\n");
            if (obj->image.image == placas[i])
            {
                perder = 1;

            }
        }

        if (!perder)
        {
             //printf("Colidiu bom obj %d\n",obj->position );
             //contar batidas
            if(countBatida != obj->position)
            {
                countBatida = obj->position;
                pontuacao += 50;
            }

            obj->image.image = transparent;
        }
        else
        {
            al_draw_bitmap(perdeuFalsa, 0, 0, 0);
            al_draw_bitmap(obj->image.image, 330, 300, 0);
            state = 4;
        }
       
    }
}

void screen_limit_up(Car *car)
{
    if (car->image.y <= -60)
    {
        car->image.y = 600;
        swap_position(car);
        //printf("randomizou velo %f\n",car->speed);
    }
}

void index_position(int p , int n)
{
    int temp = number_positions[p];
    number_positions[p] = number_positions[n];
    number_positions[n] = temp;
}

void init_car(Car *car)
{  
    int r , temp;

    r = RandomInteger(car->number, 5);
    temp = r;
   
    temp = number_positions[temp];
    index_position(car->number, r); 

    car->image.imageX = 15;
    car->image.imageY = 202;
    car->image.width = LARGURA_CARRO;
    car->image.height = ALTURA_CARRO;
    car->image.x = positions[temp];
    car->image.y = LARGURA_TELA /2 - ALTURA_CARRO;
    car->image.image = carro;
    car->position = temp;
    car->speed = car_speed[car->position];

   // use_positions[temp] = 1;
   // printf("%d\n",temp );

    //if (car->number == 5)
   // {
       // pista_livre = car->position;
   // }
}

void move_screen(float *telay, float speed)
{
    *telay = *telay - speed;

    if (*telay <= 0)
    {
        *telay = 600;
    }
    al_draw_bitmap_region(fundo,0,*telay, LARGURA_TELA, ALTURA_TELA ,0,0,0);
}

void move_auto_car(Car *car)
{
    screen_limit_up(car);

    car->image.y = car->image.y - car->speed;

    al_draw_bitmap_region(carro2, car->image.imageX, car->image.imageY,
     car->image.width , car->image.height , car->image.x ,car->image.y ,0);
}

void move_player_car(int tecla,Car *car,bool *move_permit)
{

    if (*move_permit == true)
    {
        
        if (tecla)
        {
            switch (tecla)
            {
                case 3:
                   
                    if (car->position != 0)
                    {
                        car->position = car->position -1;
                        car->image.x = positions[car->position];
                    }
                        
                    *move_permit = false;
                    break;

                case 4:
                    
                    if (car->position != 5)
                    {
                        car->position = car->position +1;
                        car->image.x = positions[car->position];
                    } 
                    
                    *move_permit = false;
                    break;
            }

        }
    }       

    al_draw_bitmap_region(car->image.image, car->image.imageX, car->image.imageY,
     car->image.width , car->image.height , car->image.x ,car->image.y ,0);
}


char* devolveCaminho()
{
    char *retorno = malloc(30*sizeof(char));
    char nomeImagem[15];
    char caminho[15];
    //int r = RandomInteger(0,10);
    //char str[10];

    strcpy(caminho,"img/placas/");
    strcpy(nomeImagem,"placa");

    //sprintf(str, "%d", r);
    //sem numero por enquanto ja que a quantidade de imagens é pequenaqq
    //strcat(nomeImagem, str);
    strcat(caminho, nomeImagem);
   //strcat(caminho, ".png");

    strcpy(retorno,caminho);

    //printf("%s\n", caminho);

    return retorno;
}

int* four_random_numbers()
{
    int* random_numbers = malloc(4*sizeof(int));

    random_numbers[0] = RandomInteger(0,10);

   random_numbers[1] = random_numbers[0];
    while(random_numbers[1] == random_numbers[0])
        random_numbers[1] = RandomInteger(0,10);
    
    random_numbers[2] = random_numbers[0];
    while(random_numbers[2] == random_numbers[0])
        random_numbers[2] = RandomInteger(0,10);

    random_numbers[3] = random_numbers[1];
    while(random_numbers[3] == random_numbers[1])
        random_numbers[3] = RandomInteger(0,10);

    while(random_numbers[3] == random_numbers[2])
        random_numbers[3] = RandomInteger(0,10);

    return random_numbers;
}

    void aloca_palcas(int* random_numbers)
    {
        int i;
        for (i = 0; i < 4; ++i)
        {
            char num[2];
            sprintf(num, "%d", random_numbers[i]);
            
            char* retorno = devolveCaminho();
            strcat(retorno,num);

            char *caminhoPlaca = malloc(30*sizeof(char));
            char *caminhoSig = malloc(30*sizeof(char));

            strcpy(caminhoPlaca,retorno);
            strcpy(caminhoSig,retorno);

            strcat(caminhoPlaca,".png");
            strcat(caminhoSig,"sig.png");

            printf("%s\n", caminhoPlaca);
            printf("%s\n", caminhoSig);

            placas_sig[i] = al_load_bitmap(caminhoSig);
            placas[i] = al_load_bitmap(caminhoPlaca);

            free(retorno);
            free(caminhoPlaca);
            free(caminhoSig);
        }
    }

    void desaloca_placas(ALLEGRO_BITMAP** placas)
    {
        int i;

        for (i = 0; i < 4; ++i)
        {
             al_destroy_bitmap(placas[i]);
        }
       
    }