#include "logic.h"
#include "gfx.h"



// Логика
void eventUpdate()
{
    // AND
    for (u16 i = 0; i < 1; i++) 
    {
        //KLog_F1("i:  ", FIX32(i));
        //KLog_F1("count_AND:  ", FIX32(count_AND));
    if (Level[index_AND[i]].gates[0] && Level[index_AND[i]].gates[1])
    {
        Level[Level[index_AND[i]].target_id].isActive = TRUE;
        KLog_F1("AND Gate: ", 1);

        KLog_F1("type: 1&1 ", FIX32(Level[index_AND[i]].type));

        XGM_startPlayPCM(65, 15, SOUND_PCM_CH3);
        SPR_setAnim(Level[index_AND[i]].spr, 3);
    }
    if (Level[index_AND[i]].gates[0] && !Level[index_AND[i]].gates[1])
    {
        Level[Level[index_AND[i]].target_id].isActive = FALSE;
        SPR_setAnim(Level[index_AND[i]].spr, 1);
                KLog_F1("type: 1&0 ", FIX32(Level[index_AND[i]].type));
    }
    if (!Level[index_AND[i]].gates[0] && Level[index_AND[i]].gates[1])
    {
        Level[Level[index_AND[i]].target_id].isActive = FALSE;
        SPR_setAnim(Level[index_AND[i]].spr, 2);
                KLog_F1("type: 0&1 ", FIX32(Level[index_AND[i]].type));
    }
    if (!Level[index_AND[i]].gates[0] && !Level[index_AND[i]].gates[1])
    {
        Level[Level[index_AND[i]].target_id].isActive = FALSE;
        SPR_setAnim(Level[index_AND[i]].spr, 0);
                KLog_F1("type: 0&0 ", FIX32(Level[index_AND[i]].type));
    }    

    /*else{
        PAL_setPalette(PAL0, palette_blue, CPU);}*/

    // OR
    for (u16 i = 0; i < count_OR; i++) 
    {
    if (Level[index_OR[i]].gates[0] && !Level[index_OR[i]].gates[1])
    {
        Level[Level[index_OR[i]].target_id].isActive = TRUE;
        SPR_setAnim(Level[index_OR[i]].spr, 1);
        KLog_F1("OR Gate: ", 1);
        XGM_startPlayPCM(65, 15, SOUND_PCM_CH3);
    }
    if (!Level[index_OR[i]].gates[0] && Level[index_OR[i]].gates[1])
    {
        Level[Level[index_OR[i]].target_id].isActive = TRUE;        
        SPR_setAnim(Level[index_OR[i]].spr, 2);
        KLog_F1("OR Gate: ", 2);
        XGM_startPlayPCM(65, 15, SOUND_PCM_CH3);
    }
    if (Level[index_OR[i]].gates[0] && Level[index_OR[i]].gates[1])
    {
        Level[Level[index_OR[i]].target_id].isActive = TRUE;
        SPR_setAnim(Level[index_OR[i]].spr, 3);
        KLog_F1("OR Gate: ", 1);
        XGM_startPlayPCM(65, 15, SOUND_PCM_CH3);
    }
    if (!Level[index_OR[i]].gates[0] && !Level[index_OR[i]].gates[1])
    {
        Level[Level[index_OR[i]].target_id].isActive = FALSE;
        SPR_setAnim(Level[index_OR[i]].spr, 0);
    }
}
    /*else{
        PAL_setPalette(PAL0, palette_blue, CPU);}*/

    for (u16 i = 0; i < count_NOT; i++) {
        if (Level[index_NOT[i]].requests > 0) {
            Level[Level[index_NOT[i]].target_id].requests = 0;
            Level[index_NOT[i]].isActive = FALSE;
            SPR_setAnim(Level[index_NOT[i]].spr, 1);
        }
    else if (Level[index_NOT[i]].requests <= 0) {
            KLog_F1("NOT Gate: ", 1);
            Level[index_NOT[i]].isActive = TRUE;
            
            Level[Level[index_NOT[i]].target_id].requests = 1;
            SPR_setAnim(Level[index_NOT[i]].spr, 0);
            XGM_startPlayPCM(65, 15, SOUND_PCM_CH3);
        }
    }

    // PIPE
    for (u16 i = 0; i < count_PIPE; i++) 
    {
    if(Level[Level[index_PIPE[i]].target_id].isActive) 
    {
                        //x
                for (int p = 1; p <= Level[index_PIPE[i]].target_entry; p++) {
                    if(Level[Level[index_PIPE[i]].target_id].isActive) 
                         VDP_setTileMapXY(BG_B,TILE_ATTR_FULL(PAL1,0,FALSE,Level[index_PIPE[i]].isActive,Level[index_PIPE[i]].requests+1),Level[index_PIPE[i]].obj_x+p,Level[index_PIPE[i]].obj_y);
                }
                //y
                if (Level[index_PIPE[i]].target_out > 1) {
                for (int p = 0; p < Level[index_PIPE[index_PIPE[i]]].target_out; p++) {
                    if(Level[Level[index_PIPE[i]].target_id].isActive) 
                         VDP_setTileMapXY(BG_B,TILE_ATTR_FULL(PAL1,0,FALSE,Level[index_PIPE[i]].isActive,Level[index_PIPE[i]].requests+1),Level[index_PIPE[i]].obj_x,Level[index_PIPE[i]].obj_y+p);
                }}
        /*for (int p = 0; p < Level[index_PIPE[i]].target_entry; p++) {
            VDP_setTileMapXY(BG_B,TILE_ATTR_FULL(PAL1,0,FALSE,FALSE,P_HorizontalAct),Level[index_PIPE[i]].obj_x+p,Level[index_PIPE[i]].obj_y);
        }*/
    }
    if(!Level[Level[index_PIPE[i]].target_id].isActive) 
    {
        /*for (int p = 0; p < Level[index_PIPE[i]].target_entry; p++) {
            VDP_setTileMapXY(BG_B,TILE_ATTR_FULL(PAL1,0,FALSE,FALSE,P_HorizontalNonAct),Level[index_PIPE[i]].obj_x+p,Level[index_PIPE[i]].obj_y);
        }*/
                                //x
                for (int p = 1; p <= Level[index_PIPE[i]].target_entry; p++) {
                    //if(!Level[Level[index_PIPE[i]].target_id].isActive) 
                        VDP_setTileMapXY(BG_B,TILE_ATTR_FULL(PAL1,0,FALSE,Level[index_PIPE[i]].isActive,Level[index_PIPE[i]].requests),Level[index_PIPE[i]].obj_x+p,Level[index_PIPE[i]].obj_y);
                }
                //y
                if (Level[index_PIPE[i]].target_out > 1) {
                for (int p = 0; p < Level[index_PIPE[index_PIPE[i]]].target_out; p++) {
                    //if(!Level[Level[index_PIPE[i]].target_id].isActive)
                        VDP_setTileMapXY(BG_B,TILE_ATTR_FULL(PAL1,0,FALSE,Level[index_PIPE[i]].isActive,Level[index_PIPE[i]].requests),Level[index_PIPE[i]].obj_x,Level[index_PIPE[i]].obj_y+p);
                }}
    }
    }
    }
}


