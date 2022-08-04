#include "logic.h"

    bool cutsceneEnded = FALSE;


// Управление
void handleInput(u16 joy, u16 changed, u16 state)
{

    // А начата ли уже игра?

    // Если никаке кнопки не нажаты, то всё обнуляем
    if (changed) {
    x_spd = FIX32(0);
    y_spd = FIX32(0);
    //SPR_setAnim(Level[0].spr, 0);
    //SPR_setAnim(Level[1].spr, 0);
    //SPR_setAnim(Level[2].spr, 0);
    Level[Level[1].target_id].requests = 0;
    Level[Level[2].target_id].requests = 0;
    //Level[3].gates[Level[0].target_entry] = FALSE;
    //Level[3].gates[Level[1].target_entry] = FALSE;
    //Level[4].gates[Level[2].target_entry] = FALSE;


    eventUpdate();
    }

    if (isStarted) {

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
        if (Level[index_ARROW].target_id > 0) {
            Level[index_ARROW].target_id--;
        }
        KLog_F1("Up ", 1);
    }
    else if (state & BUTTON_DOWN)
    { // Вниз
        if (Level[Level[index_ARROW].target_id+1].type == T_BTN) {
            Level[index_ARROW].target_id++;
        }
        y_spd = FIX32(10);
        KLog_F1("Down ", 1);
    }

    if (state & BUTTON_A)
    { // Кнопка A
        if (!Level[Level[index_ARROW].target_id].isActive){
                     KLog_F1("ACTIVE", FIX32(Level[Level[index_ARROW].target_id].isActive));
        SPR_setAnim(Level[Level[index_ARROW].target_id].spr, 1);
        Level[Level[Level[index_ARROW].target_id].target_id].requests += 1;
        Level[Level[Level[index_ARROW].target_id].target_id].gates[Level[Level[index_ARROW].target_id].target_entry] = TRUE;
        Level[Level[index_ARROW].target_id].isActive = TRUE;

        XGM_startPlayPCM(64, 14, SOUND_PCM_CH2);
        }

        else if (Level[Level[index_ARROW].target_id].isActive){
        SPR_setAnim(Level[Level[index_ARROW].target_id].spr, 0);
        Level[Level[Level[index_ARROW].target_id].target_id].requests -= 1;
        Level[Level[Level[index_ARROW].target_id].target_id].gates[Level[Level[index_ARROW].target_id].target_entry] = FALSE;
        Level[Level[index_ARROW].target_id].isActive = FALSE;
                 KLog_F1("NON_ACTIVE", FIX32(0));
        XGM_startPlayPCM(64, 14, SOUND_PCM_CH2);
        }
        eventUpdate();
    } else {
           // Level[0].isActive = FALSE;
        //eventUpdate();
    }
    /*if (state & changed & BUTTON_A)
        XGM_startPlayPCM(64, 15, SOUND_PCM_CH2);*/
    if (state & BUTTON_B)
    { // Кнопка B
        SPR_setAnim(Level[1].spr, 1);
        Level[Level[1].target_id].requests += 1;
        Level[3].gates[Level[1].target_entry] = TRUE;
        XGM_startPlayPCM(64, 14, SOUND_PCM_CH2);
        Level[1].isActive = TRUE;
        eventUpdate();
    } else {
    //Level[1].isActive = FALSE;
    //eventUpdate();
    }
    if (state & BUTTON_C)
    { // Кнопка C
        SPR_setAnim(Level[2].spr, 1);
        Level[Level[2].target_id].requests += 1;
        Level[4].gates[Level[2].target_entry] = TRUE;
        Level[2].isActive = TRUE;
        XGM_startPlayPCM(64, 14, SOUND_PCM_CH2);
        eventUpdate();
    } else {
    //Level[2].isActive = FALSE;
    //eventUpdate();
    }
    }
    else {
    if (state & BUTTON_START && cutsceneEnded)
    { // Кнопка START
        Start();
        VDP_clearText(14,18,26);
        VDP_clearTileMapRect(BG_B,0,8,40,20);
        isStarted = TRUE;
        eventUpdate();
    }
    if (state & BUTTON_A && !cutsceneEnded)
    { // Кнопка START
        u16 ind;
        ind = TILE_USER_INDEX;
        int idx1 = ind;

        SPR_setAnim(start_btn, 1);

        for (int p = 1; p <= 15; p++) {
            VDP_setTileMapXY(BG_B,TILE_ATTR_FULL(PAL1,0,FALSE,FALSE,11),19, 14-p);
            waitTick(10);
            SPR_update();   
            SYS_doVBlankProcess();
            
        }

        VDP_clearTileMapRect(BG_B,19,0,1,16);

        SPR_releaseSprite(start_btn);

        SPR_update();   
        SYS_doVBlankProcess();



        
        
                for (int p = 1; p <= 15; p++) {
            VDP_setTileMapXY(BG_B,TILE_ATTR_FULL(PAL1,0,FALSE,FALSE,10),19, 28-p);
            
        }
         
            VDP_setTileMapXY(BG_B,TILE_ATTR_FULL(PAL1,0,FALSE,FALSE,12),19, 12);
        VDP_setTileMapXY(BG_B,TILE_ATTR_FULL(PAL1,0,FALSE,FALSE,14),20, 12);


        for (int p = 1; p <= 15; p++) {
            VDP_setTileMapXY(BG_B,TILE_ATTR_FULL(PAL1,0,FALSE,FALSE,11),19, 28-p);
            waitTick(10);
        }
                VDP_setTileMapXY(BG_B,TILE_ATTR_FULL(PAL1,0,FALSE,FALSE,13),19, 12);
                            waitTick(10);
        VDP_setTileMapXY(BG_B,TILE_ATTR_FULL(PAL1,0,FALSE,FALSE,15),20, 12);

                VDP_clearTileMapRect(BG_B,19,12,2,16);

        //PAL_setPaletteColors(PAL1,RGB24_TO_VDPCOLOR(0xf00000), DMA);
        //u16 palette_full[16];
        //memcpy(&palette_full[0],  btn_spr.palette->data, 16 * 2);
        //PAL_setPaletteColors(PAL2,palette_all_white.palette->data, DMA);

        PAL_setColors(16, palette_all_white.palette->data, 16, DMA);

        VDP_loadTileSet(logo_ucomp.tileset, ind, DMA);
        TileMap *utmap = logo_ucomp.tilemap;
        VDP_setTileMapEx(BG_B, utmap, TILE_ATTR_FULL(PAL1, FALSE, FALSE, FALSE, idx1), 0, 8,  0, 0, 40, 20, CPU);


	

	    //PAL_fadeIn(0, 63, btn_spr.palette->data, 60, FALSE);
        
        PAL_fadePalette(1, palette_all_white.palette->data, btn_spr.palette->data, 30, FALSE);


        //Выводим Текст                                                                                              VDP_drawText("Текст", x по тайлам, y по тайлам) Тайл = 8х8 пикселей
        VDP_drawText("Press START", 14, 18);
        cutsceneEnded = TRUE;

    }}
    






}


