#include "genesis.h"

int main(bool hardReset)
{
    for (int x = 0; x < 39; x++)
    {
        VDP_drawText("#", x, 0);
    }
    for (int y = 0; y < 23; y++)
    {
        VDP_drawText("#", 0, y);
    }
    for (int x = 39; x >= 0; x--)
    {
        VDP_drawText("#", x, 23);
    }
    for (int y = 23; y >= 0; y--)
    {
        VDP_drawText("#", 39, y);
    }
    VDP_drawText("Game Logica \n START \n OPTI", 15, 12);
    while (TRUE)
    {
        SYS_doVBlankProcess();
    }

    return 0;
}
