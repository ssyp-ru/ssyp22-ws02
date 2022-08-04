// main.c - точка входа игры

// в файле gfx.res
// SPRITE smiley "sprite.png" 8 8 NONE
// Тип картинки  имя картинки  "путь к файлу" (для спрайтов размер в тайлах)  Компрессия    Тайл = 8х8 пикселей

#include <genesis.h>
#include "gfx.h"

// Определяем id типов блоков
enum types
{
    T_BTN, // 0
    T_AND,
    T_OR,
    T_NOT,
    T_PLATFORM
};

// Определяем тип массива
typedef struct
{
    int type;         // тип
    int target_id;    // id target блока
    int target_entry; // id входа в блок (для кнопки) или кол-во входов (для блока)
    int target_out;   // кол-во выходов (для блоков) (для кнопок 0)
    bool gates[6];
    int requests; // кол-во обращений к включению
    int obj_x;
    int obj_y;
    Sprite *spr;
    Sprite *shadow;
} T_LvlObj;

// Массив
T_LvlObj Level[] = {
    {T_BTN, // A
     3, 0, 0,
     FALSE, FALSE, FALSE, FALSE, FALSE, FALSE,
     0, 20, 20, NULL, NULL},
    {T_BTN, // B
     3, 1, 0,
     FALSE, FALSE, FALSE, FALSE, FALSE, FALSE,
     0, 20, 40, NULL, NULL},
    {T_BTN, // C
     4, 0, 0,
     FALSE, FALSE, FALSE, FALSE, FALSE, FALSE,
     0, 20, 80, NULL, NULL},
    {T_AND,
     3, 2, 1,
     FALSE, FALSE, FALSE, FALSE, FALSE, FALSE,
     0, 60, 25, NULL, NULL},
    {T_OR,
     4, 2, 1,
     FALSE, FALSE, FALSE, FALSE, FALSE, FALSE,
     0, 60, 70, NULL, NULL},
};

// Переменные игрока
Sprite *player; // Спрайт игрока
f32 x = FIX32(0);
f32 y = FIX32(0);
s16 test_x = 0; // Координаты для колизии (в будущем)
s16 test_y = 0;
f32 x_spd = FIX32(0); // Координаты для скорости
f32 y_spd = FIX32(0);

// Логика
void logicUpdate()
{
    // AND
    if (Level[3].gates[0] && Level[3].gates[1])
    {
        KLog_F1("AND Gate: ", 1);
        XGM_startPlayPCM(65, 15, SOUND_PCM_CH3);
        SPR_setAnim(Level[3].spr, 3);
    }
    if (Level[3].gates[0] && !Level[3].gates[1])
    {
        SPR_setAnim(Level[3].spr, 1);
    }
    if (!Level[3].gates[0] && Level[3].gates[1])
    {
        SPR_setAnim(Level[3].spr, 2);
    }
    if (!Level[3].gates[0] && !Level[3].gates[1])
    {
        SPR_setAnim(Level[3].spr, 0);
    }

    /*else{
        PAL_setPalette(PAL0, palette_blue, CPU);}*/

    // OR
    if (Level[4].gates[0] && !Level[4].gates[1])
    {
        SPR_setAnim(Level[4].spr, 1);
        KLog_F1("OR Gate: ", 1);
        XGM_startPlayPCM(65, 15, SOUND_PCM_CH3);
    }

    if (!Level[4].gates[0] && Level[4].gates[1])
    {
        SPR_setAnim(Level[4].spr, 2);
        KLog_F1("OR Gate: ", 2);
        XGM_startPlayPCM(65, 15, SOUND_PCM_CH3);
    }

    if (Level[4].gates[0] && Level[4].gates[1])
    {
        SPR_setAnim(Level[4].spr, 3);
        KLog_F1("OR Gate: ", 1);
        XGM_startPlayPCM(65, 15, SOUND_PCM_CH3);
    }

    if (!Level[4].gates[0] && !Level[4].gates[1])
    {
        SPR_setAnim(Level[4].spr, 0);
    }
    /*else{
        PAL_setPalette(PAL0, palette_blue, CPU);}*/
}

// Управление
void handleInput(u16 joy, u16 changed, u16 state)
{

    // Если никаке кнопки не нажаты
    x_spd = FIX32(0);
    y_spd = FIX32(0);
    SPR_setAnim(Level[0].spr, 0);
    SPR_setAnim(Level[1].spr, 0);
    SPR_setAnim(Level[2].spr, 0);
    Level[Level[1].target_id].requests = 0;
    Level[Level[2].target_id].requests = 0;
    Level[3].gates[Level[0].target_entry] = FALSE;
    Level[3].gates[Level[1].target_entry] = FALSE;
    Level[4].gates[Level[2].target_entry] = FALSE;
    logicUpdate();

    if (state & BUTTON_RIGHT)
    { // Право
        x_spd = FIX32(10);
        KLog_F1("Right ", 1);
    }
    else if (state & BUTTON_LEFT)
    { // Лево
        x_spd = FIX32(-10);
        KLog_F1("Left ", 1);
    }

    if (state & BUTTON_UP)
    { // Вверх
        y_spd = FIX32(-10);
        KLog_F1("Up ", 1);
    }
    else if (state & BUTTON_DOWN)
    { // Вниз
        y_spd = FIX32(10);
        KLog_F1("Down ", 1);
    }

    if (state & BUTTON_A)
    { // Кнопка A
        SPR_setAnim(Level[0].spr, 1);
        Level[3].requests += 1;
        Level[3].gates[Level[0].target_entry] = TRUE;
        XGM_startPlayPCM(64, 14, SOUND_PCM_CH2);
        logicUpdate();
    }
    /*if (state & changed & BUTTON_A)
        XGM_startPlayPCM(64, 15, SOUND_PCM_CH2);*/
    if (state & BUTTON_B)
    { // Кнопка B
        SPR_setAnim(Level[1].spr, 1);
        Level[3].gates[Level[1].target_entry] = TRUE;
        XGM_startPlayPCM(64, 14, SOUND_PCM_CH2);
        logicUpdate();
    }
    if (state & BUTTON_C)
    { // Кнопка C
        SPR_setAnim(Level[2].spr, 1);
        Level[Level[2].target_id].requests += 1;
        Level[4].gates[Level[2].target_entry] = TRUE;
        XGM_startPlayPCM(64, 14, SOUND_PCM_CH2);
        logicUpdate();
    }
}

// Главная, стартовая функция
int main(bool hard)
{
    SPR_init(); //выделение памяти для спрайтов

    // disable interrupt when accessing VDP
    SYS_disableInts();

    // initialization
    VDP_setScreenWidth320();

    // Управление
    JOY_init();
    JOY_setEventHandler(&handleInput);

    // выставляем цвета палитры                                                                                   PAL_setPalette(Палитра, цвет палитры, CPU)
    PAL_setPalette(PAL0, palette_blue, CPU); // 1(0) Палитра - синяя
    PAL_setPalette(PAL1, btn_spr.palette->data, CPU);
    PAL_setPalette(PAL3, smiley.palette->data, CPU); // 4(3) Палтра - палитра спрайта игрока

    // Создание объектов
    for (u16 i = 0; i < sizeof(Level) / sizeof(Level[0]); i++)
    {
        if (!Level[i].spr)
        {
            switch (Level[i].type)
            {
            case T_BTN:
            {
                Level[i].spr = SPR_addSprite(&btn_spr, Level[i].obj_x, Level[i].obj_y, TILE_ATTR(PAL3, 0, FALSE, FALSE));
                // VDP_drawText("A"+i, Level[i].obj_x/8, Level[i].obj_y/8);
                break;
            }

            case T_AND:
            {
                Level[i].spr = SPR_addSprite(&and_spr, Level[i].obj_x, Level[i].obj_y, TILE_ATTR(PAL3, 0, FALSE, FALSE));
                Level[i].shadow = SPR_addSprite(&shadow_spr, Level[i].obj_x, Level[i].obj_y + 30, TILE_ATTR(PAL3, 0, FALSE, FALSE));
                break;
            }

            case T_OR:
            {
                Level[i].spr = SPR_addSprite(&or_spr, Level[i].obj_x, Level[i].obj_y, TILE_ATTR(PAL3, 0, FALSE, FALSE));
                Level[i].shadow = SPR_addSprite(&shadow_spr, Level[i].obj_x, Level[i].obj_y + 30, TILE_ATTR(PAL3, 0, FALSE, FALSE));
                break;
            }

            default:
            {
                VDP_drawText("UND", Level[i].obj_x, Level[i].obj_y);
                break;
            }
            }
        }
    }

    //Выводим Текст                                                                                              VDP_drawText("Текст", x по тайлам, y по тайлам) Тайл = 8х8 пикселей
    VDP_drawText("Logic Test!", 14, 13);

    // Выводим изображение (сбивает все палитры)                                                                 VDP_drawImage(BG_Слой (А или B), &картинка в формате IMAGE, x тайлы, y тайлы)
    // VDP_drawImage(BG_B, &logo_ucomp, 1 , 1);

    // Добавляем спрайт                                                                                          Спрайт = SPR_addSprite(&картинка в формате SPRITE, x, y, TILE_ATTR(Палитра, Приоритет, Отраж. Верт., Отраж. Гориз.)
    player = SPR_addSprite(&smiley, fix32ToInt(x), fix32ToInt(y), TILE_ATTR(PAL3, 0, FALSE, FALSE));

    // VDP_setPaletteColor(15,RGB24_TO_VDPCOLOR(0xff0000));

    // VDP process done, we can re enable interrupts
    SYS_enableInts();

    // Музыка
    // XGM_startPlay(xgm_1);

    // Звуковые эффекты                                                                                         XGM_setPCM(id_семпла (звуковые эффекты 64-255) , сэмпл, размер_сэмпла_в_байтах);
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
        SPR_update();                                          // Обновление спрайтов

        // Функции обновления экрана
        SYS_doVBlankProcess();
        VDP_waitVInt();
    }

    return 0;
}
