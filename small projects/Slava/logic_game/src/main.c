// main.c - точка входа игры

// в файле gfx.res
// SPRITE smiley "sprite.png" 8 8 NONE
// Тип картинки  имя картинки  "путь к файлу" (для спрайтов размер в тайлах)  Компрессия    Тайл = 8х8 пикселей

#include <genesis.h>
#include "gfx.h"
#include "logic.h"
//#include <stdlib.h>

T_LvlObj Level[] = {
    {T_BTN, // A
     4, 0, 0,
     FALSE, FALSE, FALSE, FALSE, FALSE, FALSE,
     FALSE, 0, 20, 20, NULL, NULL},
    {T_BTN, // B
     5, 0, 0,
     FALSE, FALSE, FALSE, FALSE, FALSE, FALSE,
     FALSE, 0, 20, 44, NULL, NULL},
    {T_BTN, // C
     5, 1, 0,
     FALSE, FALSE, FALSE, FALSE, FALSE, FALSE,
     FALSE, 0, 20, 75, NULL, NULL},

    {T_BTN, // D
     6, 1, 0,
     FALSE, FALSE, FALSE, FALSE, FALSE, FALSE,
     FALSE, 0, 20, 116, NULL, NULL},
    {T_NOT,
     4, 2, 1,
     FALSE, FALSE, FALSE, FALSE, FALSE, FALSE,
     FALSE, 0, 60, 22, NULL, NULL},
    {T_OR,
     5, 2, 1,
     FALSE, FALSE, FALSE, FALSE, FALSE, FALSE,
     FALSE, 0, 60, 70, NULL, NULL},
    {T_NOT,
     7, 2, 1,
     FALSE, FALSE, FALSE, FALSE, FALSE, FALSE,
     FALSE, 0, 60, 116, NULL, NULL},
    {T_NOT,
     8, 2, 1,
     FALSE, FALSE, FALSE, FALSE, FALSE, FALSE,
     FALSE, 0, 100, 116, NULL, NULL},

    {T_ARROW, // Arrow
     0, 0, 0,
     FALSE, FALSE, FALSE, FALSE, FALSE, FALSE,
     FALSE, 0, 4, 20, NULL, NULL},

    // Pipe from A
    {T_PIPE,
     0, 5, 1,
     FALSE, FALSE, FALSE, FALSE, FALSE, FALSE,
     FALSE, P_HorizontalNonAct, 3, 3, NULL, NULL},

    // Pipe from B
    {T_PIPE,
     1, 3, 1,
     FALSE, FALSE, FALSE, FALSE, FALSE, FALSE,
     FALSE, P_HorizontalNonAct, 3, 6, NULL, NULL},
    {T_PIPE,
     1, 1, 1,
     FALSE, FALSE, FALSE, FALSE, FALSE, FALSE,
     TRUE, P_CornerVerticalNonAct, 5, 6, NULL, NULL},
    {T_PIPE,
     1, 1, 1,
     FALSE, FALSE, FALSE, FALSE, FALSE, FALSE,
     TRUE, P_CornerHorizontalNonAct, 5, 5, NULL, NULL},
    {T_PIPE,
     1, 2, 1,
     FALSE, FALSE, FALSE, FALSE, FALSE, FALSE,
     FALSE, P_HorizontalNonAct, 6, 5, NULL, NULL},

    // Pipe from C
    {T_PIPE,
     2, 1, 1,
     FALSE, FALSE, FALSE, FALSE, FALSE, FALSE,
     FALSE, P_HorizontalNonAct, 3, 10, NULL, NULL},
    {T_PIPE,
     2, 1, 1,
     FALSE, FALSE, FALSE, FALSE, FALSE, FALSE,
     TRUE, P_CornerVerticalNonAct, 4, 10, NULL, NULL},
    {T_PIPE,
     2, 1, 1,
     FALSE, FALSE, FALSE, FALSE, FALSE, FALSE,
     TRUE, P_CornerHorizontalNonAct, 4, 9, NULL, NULL},
    {T_PIPE,
     2, 2, 1,
     FALSE, FALSE, FALSE, FALSE, FALSE, FALSE,
     FALSE, P_HorizontalNonAct, 5, 9, NULL, NULL},

    // Pipe from AND gate (3)
    {T_PIPE,
     4, 4, 1,
     FALSE, FALSE, FALSE, FALSE, FALSE, FALSE,
     FALSE, P_HorizontalNonAct, 10, 4, NULL, NULL},

};

Sprite *player; // Спрайт игрока
Sprite *start_btn;
Sprite *kristal;
Sprite *platforma;
f32 x = FIX32(20);
f32 y = FIX32(20);
s16 test_x = 0; // Координаты для колизии (в будущем)
s16 test_y = 0;
f32 x_spd = FIX32(0); // Координаты для скорости
f32 y_spd = FIX32(0);
bool isStarted = FALSE;

u16 *index_BTN;
u16 *index_AND;
u16 *index_OR;
u16 *index_NOT;
u16 *index_PIPE;
u16 *index_PLATFORM;

u16 index_ARROW;

u16 count_BTN = 0;
u16 count_AND = 0;
u16 count_OR = 0;
u16 count_NOT = 0;
u16 count_PIPE = 0;

s16 almaz_x = 200;
s16 almaz_y = 40;

s16 platform_x = 184;
s16 platform_y = 72;
s16 max_vesota = 20;
s16 vesota = 0;

int isCollid(x1, y1, w1, h1, x2, y2, w2, h2)
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

void *checkNull(void *ptr)
{
    if (&ptr == NULL)
    {
        KLog_F1("Error! Out of memory!", FIX32(37));
    }
    return ptr;
}

// Создание объектов
void levelObjCreate()
{

    for (u16 i = 0; i < sizeof(Level) / sizeof(Level[0]); i++)
    {
        if (!Level[i].spr)
        {
            switch (Level[i].type)
            {
            case T_BTN:
            {
                Level[i].spr = SPR_addSprite(&btn_spr, Level[i].obj_x, Level[i].obj_y, TILE_ATTR(PAL1, 0, FALSE, FALSE));
                // VDP_drawText("A"+i, Level[i].obj_x/8, Level[i].obj_y/8);
                count_BTN++;
                break;
            }

            case T_AND:
            {
                Level[i].spr = SPR_addSprite(&and_spr, Level[i].obj_x, Level[i].obj_y, TILE_ATTR(PAL1, 0, FALSE, FALSE));
                Level[i].shadow = SPR_addSprite(&shadow_spr, Level[i].obj_x, Level[i].obj_y + 30, TILE_ATTR(PAL3, 0, FALSE, FALSE));
                count_AND++;
                break;
            }

            case T_OR:
            {
                Level[i].spr = SPR_addSprite(&or_spr, Level[i].obj_x, Level[i].obj_y, TILE_ATTR(PAL1, 0, FALSE, FALSE));
                Level[i].shadow = SPR_addSprite(&shadow_spr, Level[i].obj_x, Level[i].obj_y + 30, TILE_ATTR(PAL3, 0, FALSE, FALSE));
                count_OR++;
                break;
            }

            case T_NOT:
            {
                Level[i].spr = SPR_addSprite(&not_spr, Level[i].obj_x, Level[i].obj_y, TILE_ATTR(PAL1, 0, FALSE, FALSE));
                Level[i].shadow = SPR_addSprite(&shadow_spr, Level[i].obj_x, Level[i].obj_y + 30, TILE_ATTR(PAL3, 0, FALSE, FALSE));
                count_NOT++;
                break;
            }

            case T_ARROW:
            {
                Level[i].spr = SPR_addSprite(&arrow_spr, Level[i].obj_x, Level[i].obj_y, TILE_ATTR(PAL1, 0, FALSE, FALSE));
                // VDP_drawText("A"+i, Level[i].obj_x/8, Level[i].obj_y/8);
                // count_BTN++;
                break;
            }

            case T_PIPE:
            {
                // x
                for (int p = 1; p <= Level[i].target_entry; p++)
                {
                    VDP_setTileMapXY(BG_B, TILE_ATTR_FULL(PAL1, 0, FALSE, Level[i].isActive, Level[i].requests), Level[i].obj_x + p, Level[i].obj_y);
                }
                // y
                if (Level[i].target_out > 1)
                {
                    for (int p = 0; p < Level[i].target_out; p++)
                    {
                        VDP_setTileMapXY(BG_B, TILE_ATTR_FULL(PAL1, 0, FALSE, Level[i].isActive, Level[i].requests), Level[i].obj_x, Level[i].obj_y + p);
                    }
                }
                count_PIPE++;
                break;
            }

                /*case T_PIPE_CH:
                {
                    VDP_setTileMapXY(BG_B,TILE_ATTR_FULL(PAL1,0,TRUE,FALSE,P_CornerHorizontalNonAct),Level[i].obj_x,Level[i].obj_y);
                    break;
                }

                case T_PIPE_CV:
                {
                    VDP_setTileMapXY(BG_B,TILE_ATTR_FULL(PAL1,0,TRUE,FALSE,P_CornerVerticalNonAct),Level[i].obj_x,Level[i].obj_y);
                    break;
                }*/

            default:
            {
                VDP_drawText("UND", Level[i].obj_x, Level[i].obj_y);
                break;
            }
            }
        }
    } // (тест)
    index_BTN = checkNull(malloc(count_BTN * sizeof(u16)));
    index_AND = checkNull(malloc(count_AND * sizeof(u16)));
    KLog_F1("AND 1:  ", FIX32(count_AND));
    index_OR = checkNull(malloc(count_OR * sizeof(u16)));
    index_NOT = checkNull(malloc(count_NOT * sizeof(u16)));
    index_PIPE = checkNull(malloc(count_PIPE * sizeof(u16)));
}

// находим типы элементов и записываем в соответсвующий массив
void levelObjIndex()
{
    u16 amount_BTN = 0;
    u16 amount_AND = 0;
    u16 amount_OR = 0;
    u16 amount_NOT = 0;
    u16 amount_PIPE = 0;

    for (u16 i = 0; i < sizeof(Level) / sizeof(Level[0]); i++)
    {
        switch (Level[i].type)
        {
        case T_BTN:
        {
            index_BTN[amount_BTN] = i;
            amount_BTN++;
            break;
        }

        case T_AND:
        {
            index_AND[amount_AND] = i;
            amount_AND++;
            break;
        }

        case T_OR:
        {
            index_OR[amount_OR] = i;
            amount_OR++;
            break;
        }

        case T_NOT:
        {
            index_NOT[amount_NOT] = i;
            amount_NOT++;
            break;
        }

        case T_PIPE:
        {
            index_PIPE[amount_PIPE] = i;
            amount_PIPE++;
            break;
        }

        case T_ARROW:
        {
            index_ARROW = i;
        }
        }
    }
}

void Start()
{
    levelObjCreate();
    levelObjIndex();
    // Добавляем спрайт                                                                                          Спрайт = SPR_addSprite(&картинка в формате SPRITE, x, y, TILE_ATTR(Палитра, Приоритет, Отраж. Верт., Отраж. Гориз.)
    // player = SPR_addSprite(&smiley, fix32ToInt(x), fix32ToInt(y), TILE_ATTR(PAL3, 0, FALSE, FALSE));
}
// Главная, стартовая функция
int main(bool hard)
{

    SPR_init(); //выделение памяти для спрайтов

    // disable interrupt when accessing VDP
    SYS_disableInts();

    // initialization
    VDP_setScreenWidth320();

    // Инициализация управления и последующая привязка handleInput к нажатию клавиш
    JOY_init();
    JOY_setEventHandler(&handleInput);

    // выставляем цвета палитры                                                                        PAL_setPalette(Палитра, цвет палитры, CPU)
    // PAL_setPalette(PAL0, palette_white, CPU); // 1(0) Палитра - синяя
    PAL_setPalette(PAL1, btn_spr.palette->data, CPU);
    PAL_setPalette(PAL3, almazik.palette->data, CPU); // 4(3) Палтра - палитра спрайта игрока
    // PAL_setPalette(PAL3, CPU);

    VDP_loadTileSet(&start_tube_ts, 10, DMA);
    VDP_loadTileSet(&tubes_tileset, 1, DMA);

    start_btn = SPR_addSprite(&start_btn_spr, 140, 100, TILE_ATTR(PAL1, 0, FALSE, FALSE));
    for (int p = 1; p <= 15; p++)
    {
        VDP_setTileMapXY(BG_B, TILE_ATTR_FULL(PAL1, 0, FALSE, FALSE, 10), 19, 14 - p);
    }

    // void VDP_fillTileMapRect(BG_B, TILE_ATTR_FULL(PAL1,0,FALSE,FALSE,1), Level[5].obj_x, Level[5].obj_y, Level[5].obj_x, Level[5].obj_y);
    // VDP_setTileMapXY(BG_B,TILE_ATTR_FULL(PAL1,0,FALSE,FALSE,1),2,2);

    // Выводим изображение (сбивает все палитры)                                                                 VDP_drawImage(BG_Слой (А или B), &картинка в формате IMAGE, x тайлы, y тайлы)
    // VDP_drawImage(BG_B, &logo_ucomp, 1 , 1);

    // VDP_setPaletteColor(15,RGB24_TO_VDPCOLOR(0xff0000));

    // VDP process done, we can re enable interrupts
    SYS_enableInts();

    // Музыка
    // XGM_startPlay(xgm_1);

    // Загружаем звуковые эффекты в память                                                                                         XGM_setPCM(id_семпла (звуковые эффекты 64-255) , сэмпл, размер_сэмпла_в_байтах);
    XGM_setPCM(64, pcm_impact1, sizeof(pcm_impact1));
    XGM_setPCM(65, pcm_explode1, sizeof(pcm_explode1));

    kristal = SPR_addSprite(&almazik, almaz_x, almaz_y, TILE_ATTR(PAL3, 0, FALSE, FALSE));
    SPR_setVisibility(kristal, HIDDEN);
    // platforma = SPR_addSprite(&platform, platform_x, platform_y, TILE_ATTR(PAL1, 0, FALSE, FALSE));
    // SPR_setVisibility(platforma, HIDDEN);
    // VISIBLE

    // Бесконечный цикл
    while (TRUE)
    {
        // Скорость игрока
        x += x_spd;
        y += y_spd;
        if (isStarted == TRUE)
        {
            if (SPR_getVisibility(platforma) == FALSE)
            {
                SPR_setVisibility(platforma, TRUE);
                SPR_setVisibility(kristal, TRUE);
            }
            
        }
        
        if (isStarted == TRUE)
        {
            if (isCollid(almaz_x, almaz_y, 32, 32, platform_x, platform_y, 32, 8) == 0)
            {
                almaz_y += 3;
                vesota += 1;
                if (vesota > max_vesota)
                {
                    SPR_setAnim(kristal, 1);
                }
                
            }
            else
            {
                max_vesota = 0;
            }
        }

        //Если заходим за экран, то появляемся на другой его стороне
        /* if (x > FIX32(320) - FIX32(64) || x < FIX32(0))
             x_spd *= FIX32(-1);
         if (y > FIX32(240) - FIX32(64) || y < FIX32(0))
             y_spd *= FIX32(-1); */

        SPR_setPosition(kristal, almaz_x, almaz_y); // Позиция игрока
        SPR_setPosition(Level[index_ARROW].spr, Level[Level[index_ARROW].target_id].obj_x - 22, Level[Level[index_ARROW].target_id].obj_y);
        SPR_update(); // Обновление спрайтов

        // Функции обновления экрана
        SYS_doVBlankProcess();
        VDP_waitVInt();
    }

    return 0;
}
