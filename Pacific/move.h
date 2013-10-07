//
//  Created by GABRIEL VIEIRA on 10/09/13.
//  Copyright (c) 2013 GABRIEL VIEIRA. All rights reserved.
//

void init_car(Car *car)
{   
    srand(time(NULL));
    int r = rand() & 5;

    car->image.imageX = 15;
    car->image.imageY = 202;
    car->image.width = LARGURA_CARRO;
    car->image.height = ALTURA_CARRO;
    car->image.x = positions[r];
    car->image.y = LARGURA_TELA /2 - ALTURA_CARRO;
    car->image.image = carro;
    car->position = r;
}

void move_screen(float *telay)
{
    *telay -= 1;

    if (*telay == 0)
    {
        *telay = 2400;
    }

    al_draw_bitmap_region(fundo,0,*telay, LARGURA_TELA, ALTURA_TELA ,0,0,0);
}


//mover carro controlado pela cpu
/*
void move_auto_car1(Car *car)
{
    screen_limit(car);qqqqqqqq
    
    car->image.y = car->image.y + 1.0;

    al_draw_bitmap_region(car->image.image,  car->image.imageX  , car->image.imageY,
    car->image.width , car->image.height ,LARGURA_TELA * 0.8 , car->image.y ,0);
}
*/

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

    
    //printf("%d \n", r);
}