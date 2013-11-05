//
//  Created by GABRIEL VIEIRA on 10/09/13.
//  Copyright (c) 2013 GABRIEL VIEIRA. All rights reserved.
//

void lose()
{
    perder = true;
    menu_ativo = true;
    reset = true;
}

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
    int r2;
    int r = RandomInteger(0,5); 

    while(use_positions_obj[r] != 0)
    {
        r = (r+1)%6; 
    }

    int temp = obj->position;
    use_positions_obj[temp] = 0;
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
        obj->image.y = -45;
        swap_position_obj(obj);
        printf("randomizou velo %f\n",obj->speed);
        if (obj->type == 3)
        {
            obj->image.image = imgPlate2;
            countBatida = 10;
        }
    }

    //{
      // obj->image.image = imgPlate2;
    //}
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

void move_plate2(Object *obj)
{
    screen_limit_down(obj);
    obj->image.y += obj->speed;
    al_draw_scaled_bitmap(obj->image.image,360,240,124,124, obj->image.x,obj->image.y, 45,45,0);  
}
//MOVIMENTAÇÃO DOS CARROS

void colision_car(Car *car_player , Car *auto_car)
{ 
    if ((auto_car->position == car_player->position) 
    && ((auto_car->image.y - car_player->image.y) < 60 && (auto_car->image.y - car_player->image.y) > -60))
    {
        printf("Colidiu pista_livre %d\n",auto_car->position );
        lose();
    }
}

void colision_bad_obj(Car *car_player , Object *obj)
{ 
    if ((obj->position == car_player->position) 
    && ((obj->image.y - car_player->image.y) < 45 && (obj->image.y - car_player->image.y) > -45))
    {
        printf("Colidiu obj %d\n",obj->position );
        lose();
    }
}

void colision_good_obj(Car *car_player , Object *obj)
{ 
    if ((obj->position == car_player->position) 
    && ((obj->image.y - car_player->image.y) < 45 && (obj->image.y - car_player->image.y) > -45))
    {
        printf("Colidiu bom obj %d\n",obj->position );
        //contar batidas
        if(countBatida != obj->position)
        {
            countBatida = obj->position;
            pontuacao += 50;
        }

        obj->image.image = transparent;
    }
}

void screen_limit_up(Car *car)
{
    if (car->image.y <= -60)
    {
        car->image.y = 600;
        swap_position(car);
        printf("randomizou velo %f\n",car->speed);
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

    use_positions[temp] = 1;
    printf("%d\n",temp );

    if (car->number == 5)
    {
        pista_livre = car->position;
    }
}

void move_screen(float *telay)
{
    *telay -= 4;

    if (*telay == 0)
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
