#include <genesis.h>
#include "gfx.h"

typedef struct
{
    int hp;
    unsigned char type;
    int posX;
    int posY;
    unsigned int speed;
    unsigned int diarect;
    unsigned char effect;
    u16 beh;
    Sprite *sprite;
} Tobj;
Tobj entities[20];
int kk = 0;
void addPlayer(int playn, int x, int y)
{
    Sprite *spr;
    entities[kk].hp = 5;
    entities[kk].speed = 3;
    entities[kk].effect = 0b00000000;
    entities[kk].type = playn;
    entities[kk].posY = y;
    entities[kk].posX = x;
    entities[kk].beh = 0;
    switch (playn)
    {
    case 0:
        spr = SPR_addSprite(&spr_cat0, entities[kk].posX, entities[kk].posY, TILE_ATTR(PAL3, 0, FALSE, FALSE));
        entities[kk].sprite = spr;
        break;
    case 1:
        spr = SPR_addSprite(&spr_catplay, entities[kk].posX, entities[kk].posY, TILE_ATTR(PAL0, 0, FALSE, FALSE));
        entities[kk].sprite = spr;
    }
    kk++;
}
void addHealth(int x, int y)
{
    Sprite *spr;
    entities[kk].hp = 1;
    entities[kk].speed = 0;
    entities[kk].effect = 0b00000000;
    entities[kk].type = 5;
    entities[kk].posY = y;
    entities[kk].posX = x;
    entities[kk].beh = 0;
    spr = SPR_addSprite(&spr_aptechka1, entities[kk].posX, entities[kk].posY, TILE_ATTR(PAL1, 0, FALSE, FALSE));
    entities[kk].sprite = spr;
    kk++;
}
void addRock(int x, int y)
{
    Sprite *spr;
    entities[kk].hp = 2;
    entities[kk].speed = 0;
    entities[kk].effect = 0b00000000;
    entities[kk].type = 6;
    entities[kk].posY = y;
    entities[kk].posX = x;
    entities[kk].beh = 0;
    spr = SPR_addSprite(&spr_kustik0, entities[kk].posX, entities[kk].posY, TILE_ATTR(PAL1, 0, FALSE, FALSE));
    entities[kk].sprite = spr;
    kk++;
}

void handleInput1(int *x, int *y)
{
    u16 value = JOY_readJoypad(JOY_1);
    if (value & BUTTON_LEFT)
    {
        *x = *x - 3;
    }
    else if (value & BUTTON_RIGHT)
    {
        *x = *x + 3;
    }
    else if (value & BUTTON_UP)
    {
        *y = *y - 3;
    }
    else if (value & BUTTON_DOWN)
    {
        *y = *y + 3;
    }
}
void handleInput2(int *x, int *y)
{
    u16 value = JOY_readJoypad(JOY_2);
    if (value & BUTTON_LEFT)
    {
        *x = *x - 3;
    }
    else if (value & BUTTON_RIGHT)
    {
        *x = *x + 3;
    }
    else if (value & BUTTON_UP)
    {
        *y = *y - 3;
    }
    else if (value & BUTTON_DOWN)
    {
        *y = *y + 3;
    }
}
int main()
{
    SPR_init();
    PAL_setPalette(PAL3, spr_cat0.palette->data, CPU);
    PAL_setPalette(PAL2, spr_kustik0.palette->data, CPU);
    PAL_setPalette(PAL1, spr_aptechka1.palette->data, CPU);
    PAL_setPalette(PAL0, spr_cat0.palette->data, CPU);
    addPlayer(1, 50, 50);
    addPlayer(2, 100, 50);
    addRock(30, 45);
    addRock(80, 60);
    addRock(170, 135);
    while (1)
    {
        handleInput1(&entities[0].posX, &entities[0].posY);
        handleInput2(&entities[1].posX, &entities[1].posY);
        SPR_setPosition(entities[0].sprite, entities[0].posX, entities[0].posY);
        R_setPosition(entities[1].sprite, entities[1].posX, entities[1].posY);
        SPR_update();
        SYS_doVBlankProcess();
    }
    return 0;
}
