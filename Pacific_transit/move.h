//qq
//  Created by GABRIEL VIEIRA on 10/09/13.
//  Copyright (c) 2013 GABRIEL VIEIRA. All rights reserved.
//

void colision(Car *car_player , Car *auto_car)
{ 
    if ((auto_car->position == car_player->position) 
    && ((auto_car->image.y - car_player->image.y) < 60 && (auto_car->image.y - car_player->image.y) > -60))
    {
       printf("Colidiu pista %d\n",auto_car->position );
    }
}

void screen_limit(Car *car)
{
    if (car->image.y <= -60)
    {
       car->image.y = 600;
    }
}

int RandomInteger( int low, int high)
{
    srand(time(NULL));

    int k;
    double d;
    d = (double) rand( ) / ((double) RAND_MAX + 1);
    k = d * (high - low + 1);
    return low + k;
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
   
    printf("%d %d\n",car->number ,5);
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

    use_positions[temp] = 1;
    //printf("%d\n",car->number );
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
    screen_limit(car);

    car->image.y = car->image.y - car_speed[car->position];

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