//
//  Created by GABRIEL VIEIRA on 10/09/13.
//  Copyright (c) 2013 GABRIEL VIEIRA. All rights reserved.
//

void init_car(Car *car)
{
    car->image.imageY = 5;
    car->image.imageX = 16;
    car->image.width = LARGURA_CARRO;
    car->image.height = ALTURA_CARRO;
    car->image.x = ALTURA_TELA /2;
    car->image.y = LARGURA_TELA /2;
    car->image.image = carro;
}

void screen_limit(Car *car)
{
    if (car->image.x >= LARGURA_TELA)
    {
        car->image.x = 0;    
    }
    else if (car->image.x <= 0)
    {
        car->image.x = LARGURA_TELA;
    }

    if (car->image.y >= ALTURA_TELA)
    {
        car->image.y = 0;    
    }
    else if (car->image.y <= 0)
    {
        car->image.y = ALTURA_TELA;
    }
}

//mover carro controlado pela cpu
/*
void move_auto_car1(Car *car)
{
    screen_limit(car);
    
    car->image.y = car->image.y + 1.0;

    al_draw_bitmap_region(car->image.image,  car->image.imageX  , car->image.imageY,
    car->image.width , car->image.height ,LARGURA_TELA * 0.8 , car->image.y ,0);
}
*/

void move_player_car(int tecla,Car *car, float *telax , float *telay)
{
    float temp;
    
    screen_limit(car);

    if (tecla == 1 || tecla == 2 )
    {
        if (car->image.height < car->image.width)
        {
            temp = car->image.width;
            car->image.width = car->image.height;
            car->image.height = temp;
        }
    }
    else if (tecla == 3 || tecla == 4)
    {
        if (car->image.height > car->image.width)
        {
            temp = car->image.width;
            car->image.width = car->image.height;
            car->image.height = temp;
        }
    }

    if (tecla)
    {
        switch (tecla)
        {
            case 1:
               // car->image.y = car->image.y - 1.5;
                car->image.imageX = 15;
                car->image.imageY = 202;
                *telay = *telay -1.5;
                break;
            case 2:
                //car->image.y = car->image.y + 1.5;
                car->image.imageX = 16;
                car->image.imageY = 5;
                *telay = *telay + 1.5;
                break;
            case 3:
                //car->image.x = car->image.x - 1.5;
                car->image.imageX = 5;
                car->image.imageY = 81;
                *telax = *telax - 1.5;
                break;
            case 4:
                //car->image.x = car->image.x + 1.5;
                car->image.imageX = 5;
                car->image.imageY = 148;
                *telax = *telax + 1.5;
                break;
        }

    }

    ///printf("%f  %f\n",car->image.y, car->image.x);
    al_draw_bitmap_region(car->image.image, car->image.imageX, car->image.imageY,
     car->image.width , car->image.height , car->image.x ,car->image.y ,0);
}