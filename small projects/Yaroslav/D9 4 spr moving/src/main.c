#include <genesis.h>
#include "gfx.h"
// #include <stdlib.h>

#define MAX_UNITS 8

typedef struct
{
    Sprite *sprite;
    s16 posX;
    s16 posY;
    u16 speed;
    u16 sprite_width;
    u16 sprite_height;
    u16 beh;
} TCup;
u16 myrand()
{
    return random() % 5 + 1;
};
u16 randX(){
    return random() % 275 + 6;
}
u16 randY(){
    return random() % 200 + 1;
}
TCup units[MAX_UNITS];
int main()
{
    SPR_init();
    PAL_setPalette(PAL0, spr_cat0.palette->data, CPU);
    PAL_setPalette(PAL1, spr_kustik0.palette->data, CPU);
    PAL_setPalette(PAL2, spr_catplay.palette->data, CPU);
    for (u16 i = 0; i < MAX_UNITS; i++)
    {
        // cup[i] = {NULL, 0, 0, myrand(), myrand(), 32, 32};

        if(i < 3){
            Sprite *spr = SPR_addSprite(&spr_kustik0, units[i].posX, units[i].posY, TILE_ATTR(PAL1, 0, FALSE, FALSE));
        //                             (&spr_cat0, entities[l].posX, entities[l].posY, TILE_ATTR(PAL1, 0, FALSE, FALSE));
            units[i].sprite = spr;
            units[i].posX = randX();
            units[i].posY = randY();
            units[i].speed = 0;
        }
        else if(i < MAX_UNITS){
            Sprite *spr = SPR_addSprite(&spr_cat0, units[i].posX, units[i].posY, TILE_ATTR(PAL0, 0, FALSE, FALSE));
            units[i].sprite = spr;
            units[i].posX = 0;
            units[i].posY = randY();
            units[i].speed = myrand();
        }
       else {
            Sprite *spr = SPR_addSprite(&spr_catplay, units[i].posX, units[i].posY, TILE_ATTR(PAL2, 0, FALSE, FALSE));
            units[i].sprite = spr;
            units[i].posX = 0;
            units[i].posY = 0;
            units[i].speed = 4;
       }
    }
    while (1)
    {
        for (u16 i = 0; i < MAX_UNITS; i++)
        {
            switch (units[i].beh)
            {
            case 0:
                units[i].posY += units[i].speed;
                if (units[i].posY > 200){
                    units[i].beh = 1;
                }
                break;
            case 1:
                units[i].posX += units[i].speed;
                if (units[i].posX > 270){
                    units[i].beh = 2;
                }
                break;
            case 2:
                units[i].posY -= units[i].speed;
                if (units[i].posY < 0){
                    units[i].beh = 3;
                }
                break;
            case 3:
                units[i].posX -= units[i].speed;
                if (units[i].posX < 5){
                    units[i].beh = 0;
                }
                break;
            default:
                units[i].beh = 0;
            }
            SPR_setPosition(units[i].sprite, units[i].posX, units[i].posY);
        }
        SPR_update();
        SYS_doVBlankProcess();
    }
    return 0;
}
// моя лучшая разрабортка