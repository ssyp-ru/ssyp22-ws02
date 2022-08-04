#include <genesis.h>
#include "gfx.h"
typedef struct
{
    Sprite *sprite;
    s16 x;
    s16 y;
    u8 sprgo;

} TSlime;

// int boxCollision(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2)
// {
//     int collid = 0;
//      if (x1 < x2 + w2 &&
//         x1 + w1 > x2 &&
//         y1 < y2 + h2 &&
//         h1 + y1 > y2) {
//         collid = 1;
//     }
//     return collid;
// }

// u16 event1 = JOY_readJoypad(JOY_1);
// u16 event2 = JOY_readJoypad(JOY_2);
// if (event1 & BUTTON_LEFT)
// {
//     oldx = x1;
//     if (boxCollision(x1 - 1, y1, 16, 16, x2, y2, 16, 16) == 0)
//     {
//         x1--;
//     }
//     else
//     {
//         x1 = oldx;
//     }
// }

TSlime slime1 = {
    NULL, 0, 100, 1};

TSlime slime3 = {
    NULL, 100, 100, 1};

TSlime slime2 = {
    NULL, 100, 0, 1};

TSlime grass1 = {
    NULL, 50, 50, 1};

TSlime mine1 = {
    NULL, -40, -40, 0};

// Sprite *slime1;
// Sprite *slime2;
// s16 x1 = 0;
// s16 y1 = 0;
// s16 x2 = 0;
// s16 y2 = 32;
// sprgo = 1;
s16 speed = 1;
u8 heroN = 0;
bool canSetMine = TRUE;
u16 time = 0;
u16 canchange = 0;

int main()
{
    SPR_init();
    // PAL_setPalette(PAL1, slime2_spr.palette->data, CPU);
    // PAL_setPalette(PAL1, slime3_spr.palette->data, CPU);
    PAL_setPalette(PAL1, slime1_spr.palette->data, CPU);
    PAL_setPalette(PAL0, grass1_spr.palette->data, CPU);
    PAL_setPalette(PAL2, mine1_spr.palette->data, CPU);
    slime2.sprite = SPR_addSprite(&slime2_spr, slime2.x, slime2.y, TILE_ATTR(PAL1, 0, FALSE, FALSE));
    slime3.sprite = SPR_addSprite(&slime3_spr, slime3.x, slime3.y, TILE_ATTR(PAL1, 0, FALSE, FALSE));
    slime1.sprite = SPR_addSprite(&slime1_spr, slime1.x, slime1.y, TILE_ATTR(PAL1, 0, FALSE, FALSE));
    grass1.sprite = SPR_addSprite(&grass1_spr, grass1.x, grass1.y, TILE_ATTR(PAL0, 0, FALSE, FALSE));
    while (1)
    {
        switch (slime2.sprgo)
        {
        case 1:
            slime2.x += 2;
            if (slime2.x >= 320 - 32)
            {
                slime2.sprgo = 2;
            }
            SPR_setPosition(slime2.sprite, slime2.x, slime2.y);
            break;
        case 2:
            slime2.y += 2;
            if (slime2.y >= 224 - 32)
            {
                slime2.sprgo = 3;
            }
            SPR_setHFlip(slime2.sprite, TRUE);
            SPR_setPosition(slime2.sprite, slime2.x, slime2.y);
            break;
        case 3:
            slime2.x -= 2;
            if (slime2.x <= 0)
            {
                slime2.sprgo = 4;
                canSetMine = TRUE;
            }
            SPR_setPosition(slime2.sprite, slime2.x, slime2.y);
            break;
        case 4:
            slime2.y -= 2;
            if (slime2.y <= 0)
            {
                slime2.sprgo = 1;
            }
            SPR_setHFlip(slime2.sprite, FALSE);
            SPR_setPosition(slime2.sprite, slime2.x, slime2.y);
            break;
            time += 1;
            if (time == 120)
            {
                time = 0;
                canchange = TRUE;
            }
        }
        // rytpjioerytjkpgtrnurhtyutrd;mjudyrtjumu;jdjgudgjjuniduytnnudiytr;juybtr;umtbr;nurdybi6th
        switch (slime3.sprgo)
        {
        case 1:
            slime3.x += 1;
            if (slime3.x >= 320 - 32)
            {
                slime3.sprgo = 2;
            }
            SPR_setPosition(slime3.sprite, slime3.x, slime3.y);
            break;
        case 2:
            slime3.y += 1;
            if (slime3.y >= 224 - 32)
            {
                slime3.sprgo = 3;
            }
            SPR_setHFlip(slime3.sprite, TRUE);
            SPR_setPosition(slime3.sprite, slime3.x, slime3.y);
            break;
        case 3:
            slime3.x -= 1;
            if (slime3.x <= 0)
            {
                slime3.sprgo = 4;
                canSetMine = TRUE;
            }
            SPR_setPosition(slime3.sprite, slime3.x, slime3.y);
            break;
        case 4:
            slime3.y -= 1;
            if (slime3.y <= 0)
            {
                slime3.sprgo = 1;
            }
            SPR_setHFlip(slime3.sprite, FALSE);
            SPR_setPosition(slime3.sprite, slime3.x, slime3.y);
            break;
        }

        u16 value = JOY_readJoypad(JOY_1);
        if (value & BUTTON_LEFT)
        {
            SPR_setHFlip(slime1.sprite, TRUE);
            slime1.x -= speed;
        }
        if (value & BUTTON_RIGHT)
        {
            SPR_setHFlip(slime1.sprite, FALSE);
            slime1.x += speed;
        }
        SPR_setPosition(slime1.sprite, slime1.x, slime1.y);

        // trlyjegvrtlhuietrhegtvrvtreghovrhegtlegtrjpvegtrgveregrtvoougtegroethvsrgvehngrvehtyourig
        if (value & BUTTON_UP)
        {
            slime1.y -= speed;
        }
        if (value & BUTTON_DOWN)
        {
            slime1.y += speed;
        }
        SPR_setPosition(slime1.sprite, slime1.x, slime1.y);
        // 9kpiegu'mliughdfmldhvtlmuthmulmujdxlftdvltgljtudvrhjludjludljudhtu
        if (value & BUTTON_A)
        {
            if (canchange == 0)
            {
                heroN++;
                speed++;
                if (heroN > 4)
                {
                    heroN = 0;
                    speed = 1;
                }
                SPR_setAnim(slime1.sprite, heroN);
                canchange = 5;
            }
            if (canchange > 0)
            {
                canchange--;
            }

            // ndgrnudvrgtnupsvgnvsrgnlsvgrnelvgnrnlsgrnlhsgnlgsvnhgsercngsccgsnkscgr
        }
        if ((value & BUTTON_Z) && canSetMine)
        {
            mine1.sprite = SPR_addSprite(&mine1_spr, slime1.x, slime1.y, TILE_ATTR(PAL2, 0, FALSE, FALSE));
            canSetMine = FALSE;
        }
        SPR_update();
        SYS_doVBlankProcess();
    }
    return (0);
}