#include <genesis.h>
#include "gfx.h"
#define MAX_UNITS 25
u16 collision(u16 x1, u16 y1, u16 h1, u16 w1, u16 x2, u16 y2, u16 h2, u16 w2);

typedef struct
{
    int hp;
    unsigned char type;
    u16 posX;
    u16 posY;
    unsigned int speed;
    unsigned int diarect;
    unsigned char effect;
    u16 beh;
    u16 hi;
    u16 we;
    Sprite *sprite;
} Tobj;
Tobj entities[25];
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
    entities[kk].hi = 32;
    entities[kk].we = 32;
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
    entities[kk].hi = 16;
    entities[kk].we = 16;
    kk++;
}
void addmine(int x, int y)
{
    SPR_addSprite(&spr_mina0, entities[kk].posX, entities[kk].posY, TILE_ATTR(PAL1, 0, FALSE, FALSE));
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
    entities[kk].hi = 24;
    entities[kk].we = 48;
    spr = SPR_addSprite(&spr_kustik0, entities[kk].posX, entities[kk].posY, TILE_ATTR(PAL1, 0, FALSE, FALSE));
    entities[kk].sprite = spr;
    kk++;
}
void addEnemy(int x, int y){
    Sprite *spr;
    entities[kk].hp = 5;
    entities[kk].speed = 3;
    entities[kk].effect = 0b00000000;
    entities[kk].type = 7;
    entities[kk].posY = y;
    entities[kk].posX = x;
    entities[kk].beh = 0;
    entities[kk].hi = 16;
    entities[kk].we = 16;
    spr = SPR_addSprite(&spr_kustik0, entities[kk].posX, entities[kk].posY, TILE_ATTR(PAL1, 0, FALSE, FALSE));
    entities[kk].sprite = spr;
    kk++;
}

void handleInput1()
{
    u16 value = JOY_readJoypad(JOY_1);
    if (value & BUTTON_LEFT)
    {
        entities[0].posX -= 3;
    }
    else if (value & BUTTON_RIGHT)
    {
        entities[0].posY += 3;
    }
    else if (value & BUTTON_UP)
    {
        entities[0].posX -= 3;
    }
    else if (value & BUTTON_DOWN)
    {
        entities[0].posY +=  3;
    }
    else if (value & BUTTON_A)
    {
        addmine(entities[0].posX + 5, entities[0].posY + 5);
    }
}
void handleInput2()
{
    u16 value = JOY_readJoypad(JOY_2);
    if (value & BUTTON_LEFT )
    {
        entities[0].posX -= 3;
    }
    else if (value & BUTTON_RIGHT)
    {
        entities[0].posX += 3;
    }
    else if (value & BUTTON_UP)
    {
        entities[0].posY -= 3;
    }
    else if (value & BUTTON_DOWN)
    {
        entities[0].posY +=  3;
    }
    else if (value & BUTTON_A)
    {
        addmine(entities[0].posX + 5, entities[0].posY + 5);
    }
}
u16 checkcol(u16 x, u16 l, u16 r){
    if(x > l && x < r) return 1;
    return 0;
}
u16 collision(u16 x1, u16 y1, u16 h1, u16 w1, u16 x2, u16 y2, u16 h2, u16 w2){
    u16 left1 = x1, right1 = x1 + w1, top1 = y1, bot1 = y1 + h1,  left2 = x2, right2 = x2 + w2, top2 = y2, bot2 = y2 + h2;
    if((checkcol(left1, left2, right2) || checkcol(right1, left2, right2)) && (checkcol(top1, top2, bot2) || checkcol(bot1, top2, bot2))) {
        return 1;
    }
    return 0;
}
u16 pepecol(u16 make, u16 from, u16 sprite){
    for(u16 i = from; i < make; i++){
        if(collision(entities[sprite].posX, entities[sprite].posY, entities[sprite].hi, entities[sprite].we, entities[i].posX, entities[i].posY, entities[i].hi, entities[i].we)) {
            entities[0].posX = 0;
        };
    }
    return 0;
}
// 
void addLevel1(){
    addPlayer(0, 10, 20);
    addPlayer(1, 100, 20);
    addRock(280, 80);
    addRock(70, 10);
    addRock(170, 130);
    addHealth(190, 70);
    addHealth(90, 150);
}
// SPR_release(ссылка на спрайт)
int main()
{
    SPR_init();
    PAL_setPalette(PAL3, spr_cat0.palette->data, CPU);
    PAL_setPalette(PAL2, spr_kustik0.palette->data, CPU);
    PAL_setPalette(PAL1, spr_aptechka1.palette->data, CPU);
    PAL_setPalette(PAL0, spr_cat0.palette->data, CPU);
    addLevel1();
    while (1){
        handleInput1();
        handleInput2();
        SPR_setPosition(entities[0].sprite, entities[0].posX, entities[0].posY);
        SPR_setPosition(entities[1].sprite, entities[1].posX, entities[1].posY);
        SPR_update();
        SYS_doVBlankProcess();
    }
    return 0;
}