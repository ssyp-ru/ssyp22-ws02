#include <genesis.h>

#include "gfx.h"
// #include "dma.h"

int main(bool hard)
{
    u16 ind;   
    VDP_setScreenWidth320();

    // set all palette to black
    PAL_setPalette(0, (u16*) palette_black, CPU);

    // load background tilesets in VRAM
    ind = TILE_USER_INDEX;
    int idx1 = ind;
    VDP_loadTileSet(mr_pel.tileset, ind, DMA);
    int idx2 = ind;
    VDP_loadTileSet(mr_pel20.tileset, ind, DMA);
    ind += mr_pel20.tileset->numTile;
    TileMap *ctmap = mr_pel.tilemap;
    TileMap *ctmap2 = mr_pel20.tilemap;
    
    VDP_setTileMapEx(BG_A, ctmap, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, idx1), 0, 0,  0, 0, 8, 8, CPU);
    VDP_setTileMapEx(BG_A, ctmap, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, idx1), 320 / 8 - 8, 0,  0, 0, 8, 8, CPU);
    VDP_setTileMapEx(BG_A, ctmap2, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, idx2), 0, 224 / 8 - 8,  0, 0, 8, 8, CPU);
    VDP_setTileMapEx(BG_A, ctmap2, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, idx2), 320 / 8 - 8,  224 / 8 - 8,  0, 0, 8, 8, CPU);
    PAL_setPalette(PAL0,  (u16*)mr_pel.palette->data, CPU);
    PAL_setPalette(PAL1,  (u16*)mr_pel20.palette->data, CPU);
    // SYS_enableInts();

    while(TRUE)
    {
        VDP_waitVInt();
    }

    return FALSE;
}



