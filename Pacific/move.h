void auto_car(float *car1, float *car2)
{
    if (*car1 >= ALTURA_TELA)
    {
        *car1 = 0;
    }

    if (*car2 <= 0)
    {
        *car2 = ALTURA_TELA;
    }

    al_draw_bitmap_region(carro2, 16, 5, 36 , 60 , 147.500000 , *car1 ,0);
    al_draw_bitmap_region(carro2, 16, 202, 36 , 60 , 680.500000 , *car2 ,0);
    *car2 = *car2 - 1.0;
    *car1 = *car1 + 1.2;
}


void movimentar(int tecla, float *x, float *y, float *posx , float *posy,float *tamx , float *tamy)
{
    float temp;
    
    if (*x >= LARGURA_TELA)
    {
        *x = 0;    
    }
    else if (*x <= 0)
    {
        *x = LARGURA_TELA;
    }

    if (*y >= ALTURA_TELA)
    {
        *y = 0;    
    }
    else if (*y <= 0)
    {
        *y = ALTURA_TELA;
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

    }
}