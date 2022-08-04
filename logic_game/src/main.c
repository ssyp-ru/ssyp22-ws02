// main.c - точка входа игры

// в файле gfx.res
// SPRITE smiley "sprite.png" 8 8 NONE
// Тип картинки  имя картинки  "путь к файлу" (для спрайтов размер в тайлах)  Компрессия    Тайл = 8х8 пикселей

#include <genesis.h>
#include "gfx.h"
#include "logic.h"
//#include <stdlib.h>

T_LvlObj Level[] = {
    {T_BTN, // A 0
     6, 0, 0,
     FALSE, FALSE, FALSE, FALSE, FALSE, FALSE,
     FALSE, 0, 20, 20, NULL, NULL},
    {T_BTN, // B 1
     6, 1, 0,
     FALSE, FALSE, FALSE, FALSE, FALSE, FALSE,
     FALSE, 0, 20, 44, NULL, NULL},
    {T_BTN, // C 2
     7, 0, 0,
     FALSE, FALSE, FALSE, FALSE, FALSE, FALSE,
     FALSE, 0, 20, 75, NULL, NULL},
    {T_BTN, // D 3
     8, 0, 0,
     FALSE, FALSE, FALSE, FALSE, FALSE, FALSE,
     FALSE, 0, 20, 108, NULL, NULL},
    {T_BTN, // E 4
     8, 1, 0,
     FALSE, FALSE, FALSE, FALSE, FALSE, FALSE,
     FALSE, 0, 20, 132, NULL, NULL},
    {T_BTN, // F 5
     9, 1, 0,
     FALSE, FALSE, FALSE, FALSE, FALSE, FALSE,
     FALSE, 0, 20, 172, NULL, NULL},

    {T_AND, // 6
     6, 2, 1,
     FALSE, FALSE, FALSE, FALSE, FALSE, FALSE,
     FALSE, 0, 60, 22, NULL, NULL},
    {T_NOT,
     12, 2, 1,
     FALSE, FALSE, FALSE, FALSE, FALSE, FALSE,
     FALSE, 0, 60, 69, NULL, NULL},
    {T_OR,
     12, 2, 1,
     FALSE, FALSE, FALSE, FALSE, FALSE, FALSE,
     FALSE, 0, 60, 118, NULL, NULL},
    {T_NOT,
     10, 2, 1,
     FALSE, FALSE, FALSE, FALSE, FALSE, FALSE,
     FALSE, 0, 60, 165, NULL, NULL},
    {T_NOT,
     11, 2, 1,
     FALSE, FALSE, FALSE, FALSE, FALSE, FALSE,
     FALSE, 0, 100, 165, NULL, NULL},
    {T_NOT,
     12, 2, 1,
     FALSE, FALSE, FALSE, FALSE, FALSE, FALSE,
     FALSE, 0, 140, 165, NULL, NULL},

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
     2, 4, 1,
     FALSE, FALSE, FALSE, FALSE, FALSE, FALSE,
     FALSE, P_HorizontalNonAct, 3, 10, NULL, NULL},

    // Pipe from D

    {T_PIPE,
     3, 2, 1,
     FALSE, FALSE, FALSE, FALSE, FALSE, FALSE,
     FALSE, P_HorizontalNonAct, 2, 14, NULL, NULL},
    {T_PIPE,
     3, 1, 1,
     FALSE, FALSE, FALSE, FALSE, FALSE, FALSE,
     FALSE, P_CornerHorizontalNonAct, 4, 14, NULL, NULL},
    {T_PIPE,
     3, 1, 1,
     FALSE, FALSE, FALSE, FALSE, FALSE, FALSE,
     FALSE, P_CornerVerticalNonAct, 4, 15, NULL, NULL},
    {T_PIPE,
     3, 2, 1,
     FALSE, FALSE, FALSE, FALSE, FALSE, FALSE,
     FALSE, P_HorizontalNonAct, 5, 15, NULL, NULL},

    // Pipe from E
    {T_PIPE,
     4, 4, 1,
     FALSE, FALSE, FALSE, FALSE, FALSE, FALSE,
     FALSE, P_HorizontalNonAct, 3, 17, NULL, NULL},

    // Pipe from F
    {T_PIPE,
     5, 4, 1,
     FALSE, FALSE, FALSE, FALSE, FALSE, FALSE,
     FALSE, P_HorizontalNonAct, 3, 22, NULL, NULL},

    // Pipe from AND gate (6)
    {T_PIPE,
     6, 16, 1,
     FALSE, FALSE, FALSE, FALSE, FALSE, FALSE,
     FALSE, P_HorizontalNonAct, 10, 4, NULL, NULL},

    // Pipe from NOT1 gate (7)
    {T_PIPE,
     7, 16, 1,
     FALSE, FALSE, FALSE, FALSE, FALSE, FALSE,
     FALSE, P_HorizontalNonAct, 10, 10, NULL, NULL},

    // Pipe from OR gate (8)
    {T_PIPE,
     8, 16, 1,
     FALSE, FALSE, FALSE, FALSE, FALSE, FALSE,
     FALSE, P_HorizontalNonAct, 10, 16, NULL, NULL},

    // NOT chain
    {T_PIPE,
     9, 2, 1,
     FALSE, FALSE, FALSE, FALSE, FALSE, FALSE,
     FALSE, P_HorizontalNonAct, 10, 22, NULL, NULL},
    {T_PIPE,
     10, 2, 1,
     FALSE, FALSE, FALSE, FALSE, FALSE, FALSE,
     FALSE, P_HorizontalNonAct, 15, 22, NULL, NULL},
    {T_PIPE,
     11, 6, 1,
     FALSE, FALSE, FALSE, FALSE, FALSE, FALSE,
     FALSE, P_HorizontalNonAct, 20, 22, NULL, NULL},

};
#define mySize 30

// test_t array1[1024];

// test_t *myArray;
// myArray= &array1[0];
//T_LvlObj(*Level__[]) = &Level1;

Sprite *player; // Спрайт игрока
Sprite *start_btn;
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

    for (u16 i = 0; i < mySize; i++)
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

    for (u16 i = 0; i < mySize; i++)
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
    SPR_update(); // Обновление спрайтов
    SYS_doVBlankProcess();
    eventUpdate();
    isStarted = TRUE;
    // Добавляем спрайт                                                                                          Спрайт = SPR_addSprite(&картинка в формате SPRITE, x, y, TILE_ATTR(Палитра, Приоритет, Отраж. Верт., Отраж. Гориз.)
    //player = SPR_addSprite(&smiley, fix32ToInt(x), fix32ToInt(y), TILE_ATTR(PAL3, 0, FALSE, FALSE));
}

void GameOver()
{
    isStarted = FALSE;
    SPR_init();
    VDP_clearTileMapRect(BG_B, 0, 0, 40, 28);
    VDP_drawText("Game Over", 14, 12);

    SPR_update(); // Обновление спрайтов
    SYS_doVBlankProcess();
    waitTick(600);
    for (u16 i = 0; i < sizeof(Level) / sizeof(Level[0]); i++)
    {
        Level[i].spr = NULL;

        if (Level[i].type != T_PIPE)
        {
            Level[i].requests = 0;
            Level[i].isActive = FALSE;
            for (int j = 0; j < 6; j++)
                Level[i].gates[j] = NULL;
        }
    }
    VDP_clearText(14, 12, 26);
    count_BTN = 0;
    count_AND = 0;
    count_OR = 0;
    count_NOT = 0;
    count_PIPE = 0;
    free(index_BTN);
    free(index_AND);
    free(index_OR);
    free(index_NOT);
    free(index_PIPE);
    Start();
}
// Главная, стартовая функция
int main(bool hard)
{
    // VDP process done, we can re enable interrupts
    SYS_enableInts();

    VDP_loadTileSet(&start_tube_ts, 10, DMA);
    VDP_loadTileSet(&tubes_tileset, 1, DMA);

    SPR_init(); //выделение памяти для спрайтов

    // disable interrupt when accessing VDP
    // SYS_disableInts();

    // initialization
    VDP_setScreenWidth320();

    // Инициализация управления и последующая привязка handleInput к нажатию клавиш
    JOY_init();
    JOY_setEventHandler(&handleInput);

    // выставляем цвета палитры                                                                        PAL_setPalette(Палитра, цвет палитры, CPU)
    // PAL_setPalette(PAL0, palette_white, CPU); // 1(0) Палитра - синяя
    PAL_setPalette(PAL1, btn_spr.palette->data, CPU);
    PAL_setPalette(PAL3, smiley.palette->data, CPU); // 4(3) Палтра - палитра спрайта игрока

    start_btn = SPR_addSprite(&start_btn_spr, 140, 100, TILE_ATTR(PAL1, 0, FALSE, FALSE));
    for (int p = 1; p <= 15; p++)
    {
        VDP_setTileMapXY(BG_B, TILE_ATTR_FULL(PAL1, 0, FALSE, FALSE, 10), 19, 14 - p);
    }

    VDP_drawText("(c) ssyp, 2022", 12, 20);
    VDP_drawText("Saikou Egor", 14, 21);
    VDP_drawText("Sudnik Ruslan", 13, 22);

    // void VDP_fillTileMapRect(BG_B, TILE_ATTR_FULL(PAL1,0,FALSE,FALSE,1), Level[5].obj_x, Level[5].obj_y, Level[5].obj_x, Level[5].obj_y);
    // VDP_setTileMapXY(BG_B,TILE_ATTR_FULL(PAL1,0,FALSE,FALSE,1),2,2);

    // Выводим изображение (сбивает все палитры)                                                                 VDP_drawImage(BG_Слой (А или B), &картинка в формате IMAGE, x тайлы, y тайлы)
    // VDP_drawImage(BG_B, &logo_ucomp, 1 , 1);

    // VDP_setPaletteColor(15,RGB24_TO_VDPCOLOR(0xff0000));

    // Музыка
    // XGM_startPlay(xgm_1);

    // Загружаем звуковые эффекты в память                                                                                         XGM_setPCM(id_семпла (звуковые эффекты 64-255) , сэмпл, размер_сэмпла_в_байтах);
    XGM_setPCM(64, pcm_impact1, sizeof(pcm_impact1));
    XGM_setPCM(65, pcm_explode1, sizeof(pcm_explode1));

    // Бесконечный цикл
    while (TRUE)
    {
        // Скорость игрока
        x += x_spd;
        y += y_spd;

        //Если заходим за экран, то появляемся на другой его стороне
        /* if (x > FIX32(320) - FIX32(64) || x < FIX32(0))
             x_spd *= FIX32(-1);
         if (y > FIX32(240) - FIX32(64) || y < FIX32(0))
             y_spd *= FIX32(-1); */

        SPR_setPosition(player, fix32ToInt(x), fix32ToInt(y)); // Позиция игрока
        SPR_setPosition(Level[index_ARROW].spr, Level[Level[index_ARROW].target_id].obj_x - 22, Level[Level[index_ARROW].target_id].obj_y);

        SPR_update(); // Обновление спрайтов

        // Функции обновления экрана
        SYS_doVBlankProcess();
        VDP_waitVInt();
    }

    return 0;
}
