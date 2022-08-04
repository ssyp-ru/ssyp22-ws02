#include <genesis.h>

#include "gfx.h"
// #include "dma.h"

int main(bool hard)
{
    u16 ind;

    // disable interrupt when accessing VDP
    SYS_disableInts();
    // initialization
    VDP_setScreenWidth320();

    // set all palette to black
    PAL_setPalette(0, (u16*) palette_black, CPU);

    // load background tilesets in VRAM
    ind = TILE_USER_INDEX;
    int idx1 = ind;
    VDP_loadTileSet(logo1.tileset, ind, DMA);
    ind += logo1.tileset->numTile;
  // This one is not packed
// Unpack the packed tilemap
    TileMap *ctmap = unpackTileMap(logo1.tilemap, NULL);

    // draw backgrounds
    VDP_setTileMapEx(BG_A, ctmap, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, idx1), 0, 0,  0, 0, 8, 8, CPU);
    // VDP_setTileMapEx(BG_A, utmap, TILE_ATTR_FULL(PAL1, FALSE, FALSE, FALSE, idx2), 0, 12, 0, 0, 30, 12, CPU);

   VDP_setTileMapEx(BG_A, ctmap, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, idx1), 12, 0,  0, 0, 9, 9, CPU);

    PAL_setPalette(PAL0,  (u16*)logo1.palette->data, CPU);
	// VDP process done, we can re enable interrupts
    SYS_enableInts();

    while(TRUE)
    {
        VDP_waitVInt();
    }

    return FALSE;
}



