#include <genesis.h>
#include "gfx.h"

typedef struct
{
    u8 type;
    u16 x;
    u16 y;
    u8 hp;
    u16 direction;
    u8 speed;
    u8 perezoradka;
    Sprite *sprite;
    u8 isDead;
} Tunit;
typedef struct
{
    u8 rod;
    u8 type;
    s16 x;
    s16 y;
    u16 direction;
    u8 speed;
    Sprite *sprite;
} Bullet;

#define MAX_BULLETS 10
Bullet bullets[MAX_BULLETS];
Tunit p1;
Tunit p2;
s16 oldx;
s16 oldy;

int boxCollision(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2)
{
    int collid = 0;
    if (x1 < x2 + w2 &&
        x1 + w1 > x2 &&
        y1 < y2 + h2 &&
        h1 + y1 > y2)
    {
        collid = 1;
    }
    return collid;
}

void addBullet(s16 x, s16 y, Tunit *player)
{
    for (int i = 0; i < MAX_BULLETS; i++)
    {
        if (bullets[i].type == 0)
        {
            if (player->type == 1)
            {
                bullets[i].type = 1;
                bullets[i].rod = 2;
                bullets[i].sprite = SPR_addSprite(&bullet_sprite, x + 32, y + 16, TILE_ATTR(PAL1, 0, FALSE, FALSE));
                SPR_setPriority(bullets[i].sprite, SPR_MIN_DEPTH);
                SPR_setAnim(bullets[i].sprite, player->sprite->animInd);
                bullets[i].x = x + 16;
                bullets[i].y = y + 16;
                // SPR_setPrioruty();
                // bullets[0].append(bullletp1);
            }
            else
            {
                bullets[i].type = 1;
                bullets[i].rod = 1;
                bullets[i].sprite = SPR_addSprite(&bullet_sprite, x + 32, y + 16, TILE_ATTR(PAL1, 0, FALSE, FALSE));
                SPR_setPriority(bullets[i].sprite, SPR_MIN_DEPTH);
                SPR_setAnim(bullets[i].sprite, player->sprite->animInd);
                bullets[i].x = x + 16;
                bullets[i].y = y + 16;
            }

            // SPR_setPrioruty();
            // bullets[0].append(bullletp1);
        }
    }
}

void updateBullets()
{
    for (u16 i = 0; i < MAX_BULLETS; i++)
    {
        if (bullets[i].type == 0)
            continue;

        if (bullets[i].x > 320 || bullets[i].y > 224 || bullets[i].x < -4 || bullets[i].y < -4)
        {
            bullets[i].type = 0;
            SPR_releaseSprite(bullets[i].sprite);
            break;
        }
        if (bullets[i].sprite->animInd == 0)
        {
            bullets[i].y-=6;
        }
        if (bullets[i].sprite->animInd == 1)
        {
            bullets[i].x +=6;
        }
        if (bullets[i].sprite->animInd == 2)
        {
            bullets[i].y+=6;
        }
        if (bullets[i].sprite->animInd == 3)
        {
            bullets[i].x-=6;
        }
        SPR_setPosition(bullets[i].sprite, bullets[i].x, bullets[i].y);
        if (bullets[i].rod == 1)
        {
            if (boxCollision(bullets[i].x, bullets[i].y, 8, 8, p1.x, p1.y, 32, 32) == 1)
            { 
                p1.hp -= 1;
                SPR_releaseSprite(bullets[i].sprite);
            }
        }
        else
        {
            if (boxCollision(bullets[i].x, bullets[i].y, 8, 8, p2.x, p2.y, 32, 32) == 1)
            {
                p2.hp -= 1;
                SPR_releaseSprite(bullets[i].sprite);
            }
        }
    }
}

int main()
{
    p1.speed = 1;
    p2.speed = 1;
    p1.type = 1;
    p2.type = 2;
    p1.isDead = 0;
    p2.isDead = 0;
    p1.hp = 2;
    p2.hp = 2;
    u16 ind = TILE_USER_INDEX;
    VDP_loadTileSet(fon.tileset, ind, DMA);
    // VDP_drawImage(BG_A, &img, 0, 0);
    SPR_init();
    PAL_setPalette(PAL1, pel.palette->data, CPU);
    // PAL_setPalette(PAL1, pel2.palette->data, CPU);
    p2.x = 100;
    p2.perezoradka = 1;
    p1.sprite = SPR_addSprite(&pel, p1.x, p1.y, TILE_ATTR(PAL1, 0, FALSE, FALSE));
    p2.sprite = SPR_addSprite(&pel2, p2.x, p2.y, TILE_ATTR(PAL1, 0, FALSE, FALSE));
    // bullet = SPR_addSprite(&bullet, ?, ?, TILE_ATTR(PAL1, 0, FALSE, FALSE))
    PAL_setPalette(PAL0, fon.palette->data, CPU);
    while (1)
    {
        u16 event1 = JOY_readJoypad(JOY_1);
        u16 event2 = JOY_readJoypad(JOY_2);
        oldx = p1.x;
        oldy = p1.y;
        if (p1.hp < 1)
        {
            p1.isDead = 1;
            SPR_releaseSprite(p1.sprite);
        }
        if (p2.hp < 1)
        {
            p2.isDead = 1;
            SPR_releaseSprite(p2.sprite);
        }
        
        if (event1 & BUTTON_LEFT)
        {
            oldx = p1.x;
            if (boxCollision(p1.x - p1.speed, p1.y, 32, 32, p2.x, p2.y, 32, 32) == 0)
            {
                SPR_setAnim(p1.sprite, 3);
                p1.x -= p1.speed;
            }
            else
            {
                p1.x = oldx;
            }
        }
        if (event1 & BUTTON_RIGHT)
        {
            oldx = p1.x;
            if (boxCollision(p1.x + p1.speed, p1.y, 32, 32, p2.x, p2.y, 32, 32) == 0)
            {
                SPR_setAnim(p1.sprite, 1);
                p1.x += p1.speed;
            }
            else
            {
                p1.x = oldx;
            }
        }
        if (event1 & BUTTON_UP)
        {
            oldy = p1.y;
            if (boxCollision(p1.x, p1.y - p1.speed, 32, 32, p2.x, p2.y, 32, 32) == 0)
            {
                SPR_setAnim(p1.sprite, 0);
                p1.y -= p1.speed;
            }
            else
            {
                p1.y = oldy;
            }
        }
        if (event1 & BUTTON_DOWN)
        {
            oldy = p1.y;
            if (boxCollision(p1.x, p1.y + p1.speed, 32, 32, p2.x, p2.y, 32, 32) == 0)
            {
                SPR_setAnim(p1.sprite, 2);
                p1.y += p1.speed;
            }
            else
            {
                p1.y = oldy;
            }
        }
        if (event1 & BUTTON_A)
        {
            if (p1.isDead == 0)
            {
                if (p1.perezoradka >= 50)
                {
                    addBullet(p1.x, p1.y, &p1);
                    p1.perezoradka = 0;
                }
            }
            
            
        }
        oldx = p2.x;
        oldy = p2.y;
        if (event2 & BUTTON_LEFT)
        {
            oldx = p2.x;
            if (boxCollision(p1.x, p1.y, 32, 32, p2.x - p2.speed, p2.y, 32, 32) == 0)
            {
                SPR_setAnim(p2.sprite, 3);
                p2.x -= p2.speed;
            }
            else
            {
                p2.x = oldx;
            }
        }
        if (event2 & BUTTON_RIGHT)
        {
            oldx = p2.x;
            if (boxCollision(p1.x, p1.y, 32, 32, p2.x + p2.speed, p2.y, 32, 32) == 0)
            {
                SPR_setAnim(p2.sprite, 1);
                p2.x += p2.speed;
            }
            else
            {
                p2.x = oldx;
            }
        }
        if (event2 & BUTTON_UP)
        {
            oldy = p2.y;
            if (boxCollision(p1.x, p1.y, 32, 32, p2.x, p2.y - p2.speed, 32, 32) == 0)
            {
                SPR_setAnim(p2.sprite, 0);
                p2.y -= p2.speed;
            }
            else
            {
                p2.y = oldy;
            }
        }
        if (event2 & BUTTON_DOWN)
        {
            oldy = p2.y;
            if (boxCollision(p1.x, p1.y, 32, 32, p2.x, p2.y + p2.speed, 32, 32) == 0)
            {
                SPR_setAnim(p2.sprite, 2);
                p2.y += p2.speed;
            }
            else
            {
                p2.y = oldy;
            }
        }
        if (event2 & BUTTON_A)
        {
            if(p2.isDead == 0)
            {
                if (p2.perezoradka >= 50)
                {
                    addBullet(p2.x, p2.y, &p2);
                    p2.perezoradka = 0;
                }
            }
            
        }

        if (p1.perezoradka < 50)
        {
            p1.perezoradka++;
        }
        if (p2.perezoradka < 50)
        {
            p2.perezoradka++;
        }
        updateBullets();

        SPR_setPosition(p1.sprite, p1.x, p1.y);
        SPR_setPosition(p2.sprite, p2.x, p2.y);
        SPR_update();
        SYS_doVBlankProcess();
    }
    return (0);
}