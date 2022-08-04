#include <genesis.h>
#include "gfx.h"

Sprite *goblen;
Sprite *knigh;
s16 x1 = 0;
s16 y1 = 0;
s16 x2 = 40;
s16 y2 = 40;
s16 oldx;
s16 oldy;

int boxCollision(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2)
{
    int collid = 0;
     if (x1 < x2 + w2 &&
        x1 + w1 > x2 &&
        y1 < y2 + h2 &&
        h1 + y1 > y2) {
        collid = 1;
    }
    return collid;
}
    

    

int main()
{
    u16 ind = TILE_USER_INDEX;
    u16 idx1 = ind;
    VDP_loadTileSet(fon.tileset, ind, DMA);
    // VDP_drawImage(BG_A, &img, 0, 0);
    SPR_init();
    PAL_setPalette(PAL1, pel.palette->data, CPU);
    PAL_setPalette(PAL1, pel2.palette->data, CPU);
    goblen = SPR_addSprite(&pel, x1, y1, TILE_ATTR(PAL1, 0, FALSE, FALSE));
    knigh = SPR_addSprite(&pel2, x2, y2, TILE_ATTR(PAL1, 0, FALSE, FALSE));
    PAL_setPalette(PAL0, fon.palette->data, CPU);
    while (1)
    {
        u16 event1 = JOY_readJoypad(JOY_1);
        u16 event2 = JOY_readJoypad(JOY_2);
        if (event1 & BUTTON_LEFT)
        {
            oldx = x1;
            if (boxCollision(x1 - 1, y1, 16, 16, x2, y2, 16, 16) == 0)
            {
                x1--;
            }
            else
            {
                x1 = oldx;
            }

        }
        if (event1 & BUTTON_RIGHT)
        {
            oldx = x1;
            if (boxCollision(x1 + 1, y1, 16, 16, x2, y2, 16, 16) == 0)
            {
                x1++;
            }
            else
            {
                x1 = oldx;
            }
        }
        if (event1 & BUTTON_UP)
        {
            oldy = y1;
            if (boxCollision(x1, y1 - 1, 16, 16, x2, y2, 16, 16) == 0)
            {
                y1--;
            }
            else
            {
                y1 = oldy;
            }
        }
        if (event1 & BUTTON_DOWN)
        {
            oldy = y1;
            if (boxCollision(x1, y1 + 1, 16, 16, x2, y2, 16, 16) == 0)
            {
                y1++;
            }
            else
            {
                y1 = oldy;
            }
            
        }
        if (event2 & BUTTON_LEFT)
        {
            oldx = x2;
            if (boxCollision(x1, y1, 16, 16, x2 - 1, y2, 16, 16) == 0)
            {
                x2--;
            }
            else
            {
                x2 = oldx;
            }
            
        }
        if (event2 & BUTTON_RIGHT)
        {
            oldx = x2;
            if (boxCollision(x1, y1, 16, 16, x2 + 1, y2, 16, 16) == 0)
            {
                x2++;
            }
            else 
            {
                x2 = oldx;
            }
            
        }
        if (event2 & BUTTON_UP)
        {
            oldy = y2;
            if (boxCollision(x1, y1, 16, 16, x2, y2 - 1, 16, 16) == 0)
            {
                y2--;
            }
            else
            {
                y2 = oldy;
            }
            
        }
        if (event2 & BUTTON_DOWN)
        {
            oldy = y2;
             if (boxCollision(x1, y1, 16, 16, x2, y2 + 1, 16, 16) == 0)
            {
                y2++;
            }
             else
            {
                y2 = oldy;
            }
        }
        SPR_setPosition(goblen, x1, y1);
        SPR_setPosition(knigh, x2, y2);
        SPR_update();
        SYS_doVBlankProcess();
    }
    return (0);
}