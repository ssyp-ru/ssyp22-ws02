#include "logic.h"

bool cutsceneEnded = FALSE;

// Управление
void handleInput(u16 joy, u16 changed, u16 state)
{

    // А начата ли уже игра?

    // Если никаке кнопки не нажаты, то всё обнуляем
    if (changed && isStarted)
    {
        x_spd = FIX32(0);
        y_spd = FIX32(0);
        // SPR_setAnim(Level[0].spr, 0);
        // SPR_setAnim(Level[1].spr, 0);
        // SPR_setAnim(Level[2].spr, 0);
        // Level[Level[1].target_id].requests = 0;
        // Level[Level[2].target_id].requests = 0;
        // Level[3].gates[Level[0].target_entry] = FALSE;
        // Level[3].gates[Level[1].target_entry] = FALSE;
        // Level[4].gates[Level[2].target_entry] = FALSE;

        eventUpdate();
    }

    if (isStarted)
    {

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
            if (Level[index_ARROW].target_id > 0)
            {
                Level[index_ARROW].target_id--;
            }
            KLog_F1("Up ", 1);
        }
        else if (state & BUTTON_DOWN)
        { // Вниз
            if (Level[Level[index_ARROW].target_id + 1].type == T_BTN)
            {
                Level[index_ARROW].target_id++;
            }
            y_spd = FIX32(10);
            KLog_F1("Down ", 1);
        }

        if (state & BUTTON_A)
        { // Кнопка A
            if (!Level[Level[index_ARROW].target_id].isActive)
            {
                KLog_F1("ACTIVE", FIX32(Level[Level[index_ARROW].target_id].isActive));
                SPR_setAnim(Level[Level[index_ARROW].target_id].spr, 1);
                Level[Level[Level[index_ARROW].target_id].target_id].requests += 1;
                Level[Level[Level[index_ARROW].target_id].target_id].gates[Level[Level[index_ARROW].target_id].target_entry] = TRUE;
                Level[Level[index_ARROW].target_id].isActive = TRUE;

                XGM_startPlayPCM(64, 14, SOUND_PCM_CH2);
            }

            else if (Level[Level[index_ARROW].target_id].isActive)
            {
                SPR_setAnim(Level[Level[index_ARROW].target_id].spr, 0);
                Level[Level[Level[index_ARROW].target_id].target_id].requests -= 1;
                Level[Level[Level[index_ARROW].target_id].target_id].gates[Level[Level[index_ARROW].target_id].target_entry] = FALSE;
                Level[Level[index_ARROW].target_id].isActive = FALSE;
                KLog_F1("NON_ACTIVE", FIX32(0));
                XGM_startPlayPCM(64, 14, SOUND_PCM_CH2);
            }
            eventUpdate();
        }
        else
        {
            // Level[0].isActive = FALSE;
            // eventUpdate();
        }
        /*if (state & changed & BUTTON_A)
            XGM_startPlayPCM(64, 15, SOUND_PCM_CH2);*/
        if (state & BUTTON_B)
        { // Кнопка B
            GameOver();
        }
        else
        {
            // Level[1].isActive = FALSE;
            // eventUpdate();
        }
        if (state & BUTTON_C)
        { // Кнопка C
        }
        else
        {
            // Level[2].isActive = FALSE;
            // eventUpdate();
        }
    }
    else
    {
        if (state & BUTTON_START && cutsceneEnded)
        { // Кнопка START
            Start();
            VDP_clearText(14, 18, 26);

            VDP_clearTileMapRect(BG_B, 0, 8, 40, 20);

            // eventUpdate();
        }
        if (state & BUTTON_A && !cutsceneEnded)
        { // Кнопка START
            introCut();
        }
    }
}
