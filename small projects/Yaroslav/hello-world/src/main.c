#include "genesis.h"
u16 daca_pepe [20][20];

int main(bool hardReset)
{
    for(u16 i = 0; i < 20; i++){
        for(u16 j = 0; j < 20; j++){
            VDP_drawText(daca_pepe[i][j], 12, 12);
        }
    }
for(u16 i = 0; i < 20; i++){
        for(u16 j = 0; j < 20; j++){
        	if(i == 0 || j == 0 || i == 19 || j == 19) dacha_pepe[i][j] = 6;
		else daca_pepe[i][j] = 0;
        }
    }
    while(TRUE)
    {
        // nothing to do here
        // ...

        // always call this method at the end of the frame
        SYS_doVBlankProcess();
    }

    return 0;
}
