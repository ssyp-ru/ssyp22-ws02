#include <genesis.h>
#include "gfx.h"
#include <timer.h>
#pragma once


//#include "level.c"

// Определяем id типов блоков
enum types
{
    T_BTN,      // 0
    T_AND,
    T_OR,
    T_NOT,
    T_PIPE,
    T_PLATFORM,
    T_ARROW
};

enum pipesAnim
{
    // Act - Active
    P_HorizontalNonAct = 1,             // 1
    P_HorizontalAct,
    P_CornerHorizontalNonAct,           // →↓   FLIPPED: ↑→
    P_CornerHorizontalAct,
    P_VerticalNonAct,
    P_VerticalAct,
    P_CornerVerticalNonAct,             // ↓→   FLIPPED: →↑
    P_CornerVerticalAct, 
};

// Определяем тип массива
typedef struct
{
    int type;           // тип
    int target_id;      // id target блока
    int target_entry;   // id входа в блок (для кнопки) или кол-во входов (для блока) или ширину / высоту (для верт и гориз проводов)
    int target_out;     // кол-во выходов (для блоков) (для кнопок 0)
    bool gates[6];      // состояния лампочек (блок) или провода
    bool isActive;      // состояния объектов или flip трубы
    int requests;       // кол-во обращений к включению или тайл трубы
    int obj_x;
    int obj_y;
    Sprite *spr;
    Sprite *shadow;
} T_LvlObj;

// Массив
extern T_LvlObj Level[];

// Переменные игрока
extern Sprite *player;         // Спрайт игрока
extern Sprite *start_btn; 
extern f32 x;
extern f32 y;
extern s16 test_x;         // Координаты для колизии (в будущем)
extern s16 test_y;
extern f32 x_spd;   // Координаты для скорости
extern f32 y_spd;
extern s16 almaz_x;
extern s16 almaz_y;
extern s16 platform_x;
extern s16 platform_y;

extern bool isStarted;
//extern bool cutsceneEnded;

extern u16* index_BTN;
extern u16* index_AND;
extern u16* index_OR;
extern u16* index_NOT;
extern u16* index_PIPE;

extern u16 index_ARROW;

extern u16 count_BTN;
extern u16 count_AND;
extern u16 count_OR;
extern u16 count_NOT;
extern u16 count_PIPE;

extern u16* index_PLATFORM;
extern u16 amount_index_PLATFORM;

void handleInput(u16 joy, u16 changed, u16 state);
void levelObjCreate();
void Start();
//void* checkNull(void* ptr);
//void logicUpdate();