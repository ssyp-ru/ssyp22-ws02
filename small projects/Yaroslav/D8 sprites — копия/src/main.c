#include <genesis.h>
typedef struct
{
	Sprite *sprite;
	s16 posX;
	s16 posY;
	s16 x_spd;
	s16 y_spd;
	u16 sprite_width;
	u16 sprite_height;
} Cup;
#include "gfx.h"
void handleInput1()
{
    u16 value = JOY_readJoypad(JOY_1);
    x_speed1 = 0;
    if (value & BUTTON_LEFT)
    {
        x_speed1 += -speed;
    }
    if (value & BUTTON_RIGHT)
    {
        x_speed1 += speed;
    }
    if (value & BUTTON_UP)
    {
        y_speed1 += -speed;
    }
    if (value & BUTTON_DOWN)
    {
        y_speed1 += speed;
    }
}
void handleInput2()
{
    u16 value = JOY_readJoypad(JOY_2);
    x_speed1 = 0;
    if (value & BUTTON_LEFT)
    {
        x_speed1 = -speed;
    }
    if (value & BUTTON_RIGHT)
    {
        x_speed1 = speed;
    }
    if (value & BUTTON_UP)
    {
        y_speed1 = -speed;
    }
    if (value & BUTTON_DOWN)
    {
        y_speed1 = speed;
    }
}
int main(bool hard)
{
    SPR_init();
    PAL_setPalette(PAL3, spr_diamond.palette->data, CPU);
    diamond_obj = SPR_addSprite(&spr_diamond, x1, y1, TILE_ATTR(PAL3, 0, FALSE, FALSE));
    diamond_objlol = SPR_addSprite(&spr_diamondlol, x2, y2, TILE_ATTR(PAL3, 0, FALSE, FALSE));
    while (1)
    {
        x1 += x_speed1;
        y1 += y_speed1;
        if (x_speed1 > 0)
            x_speed1 -= 1;
        if (x_speed1 < 0)
            x_speed1 += 1;
        if (y_speed1 > 0)
            y_speed1 -= 1;
        if (y_speed1 < 0)
            y_speed1 += 1;
        x2 += x_speed2;
        y2 += y_speed2;
        if (x_speed2 > 0)
            x_speed2 -= 1;
        if (x_speed2 < 0)
            x_speed2 += 1;
        if (y_speed2 > 0)
            y_speed2 -= 1;
        if (y_speed2 < 0)
            y_speed2 += 1;
        // if (y_speed1 > 0)
        //     y_speed1 -= 00.1;
        handleInput1();
        handleInput2();
        // if(x > 320-cup_width || x < 0)
        //     x_speed1 = 0;
        // if(y > 240-cup_height || y < 0)
        //     y_speed1 = 0;
        SPR_setPosition(diamond_obj, x1, y1);
        SPR_update();
        SYS_doVBlankProcess();
    }
    return 0;
}
