#include "logic.h"

void introCut()
{
    u16 ind;
    ind = TILE_USER_INDEX;
    int idx1 = ind;

                VDP_clearText(12, 20, 26);
            VDP_clearText(14, 21, 26);
            VDP_clearText(11, 22, 26);

    XGM_startPlayPCM(64, 14, SOUND_PCM_CH2);
    SPR_setAnim(start_btn, 1);

    for (int p = 1; p <= 15; p++)
    {
        VDP_setTileMapXY(BG_B, TILE_ATTR_FULL(PAL1, 0, FALSE, FALSE, 11), 19, 14 - p);
        waitTick(10);
        SPR_update();
        SYS_doVBlankProcess();
    }

    VDP_clearTileMapRect(BG_B, 19, 0, 1, 16);

    SPR_releaseSprite(start_btn);

    SPR_update();
    SYS_doVBlankProcess();

    for (int p = 1; p <= 15; p++)
    {
        VDP_setTileMapXY(BG_B, TILE_ATTR_FULL(PAL1, 0, FALSE, FALSE, 10), 19, 28 - p);
    }

    VDP_setTileMapXY(BG_B, TILE_ATTR_FULL(PAL1, 0, FALSE, FALSE, 12), 19, 12);
    VDP_setTileMapXY(BG_B, TILE_ATTR_FULL(PAL1, 0, FALSE, FALSE, 14), 20, 12);

    for (int p = 1; p <= 15; p++)
    {
        VDP_setTileMapXY(BG_B, TILE_ATTR_FULL(PAL1, 0, FALSE, FALSE, 11), 19, 28 - p);
        waitTick(10);
    }
    VDP_setTileMapXY(BG_B, TILE_ATTR_FULL(PAL1, 0, FALSE, FALSE, 13), 19, 12);
    waitTick(10);
    VDP_setTileMapXY(BG_B, TILE_ATTR_FULL(PAL1, 0, FALSE, FALSE, 15), 20, 12);

    VDP_clearTileMapRect(BG_B, 19, 12, 2, 16);

    // PAL_setPaletteColors(PAL1,RGB24_TO_VDPCOLOR(0xf00000), DMA);
    // u16 palette_full[16];
    // memcpy(&palette_full[0],  btn_spr.palette->data, 16 * 2);
    // PAL_setPaletteColors(PAL2,palette_all_white.palette->data, DMA);

    PAL_setColors(16, palette_all_white.palette->data, 16, DMA);
    XGM_startPlayPCM(65, 15, SOUND_PCM_CH3);
    VDP_loadTileSet(logo_ucomp.tileset, ind, DMA);
    TileMap *utmap = logo_ucomp.tilemap;
    VDP_setTileMapEx(BG_B, utmap, TILE_ATTR_FULL(PAL1, FALSE, FALSE, FALSE, idx1), 0, 8, 0, 0, 40, 20, CPU);

    // PAL_fadeIn(0, 63, btn_spr.palette->data, 60, FALSE);

    PAL_fadePalette(1, palette_all_white.palette->data, btn_spr.palette->data, 30, FALSE);

    //Выводим Текст                                                                                              VDP_drawText("Текст", x по тайлам, y по тайлам) Тайл = 8х8 пикселей
    VDP_drawText("Press START", 14, 18);

    cutsceneEnded = TRUE;
}