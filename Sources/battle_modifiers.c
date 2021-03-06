// Filename: battle_modifiers.c

#include "cheats.h"
#include "hid.h"

/********************************
 *                              *
 *      Battle Modifiers        *
 *                              *
 ********************************/

int  i_shinyPokemon,
     i_maxBattleStats,
     i_zMoves;

char statusBattleStats[40] = "Undefined",
     statusZMove[40] = "Undefined",
     statusShiny[40] = "Undefined";


// Battle menu entry
void    battleMenu(void) {
    updateZMove();
    updateBattleStats();
    updateShiny();
    new_spoiler("Battle");
        //new_entry("Alola Rattata", alolaRat);
        new_entry("100% Capture Rate", catch100);
        i_shinyPokemon = new_entry(statusShiny, shinyPokemon);
        i_maxBattleStats = new_entry(statusBattleStats, maxBattleStats);
        i_zMoves = new_entry(statusZMove, zMoves);
        new_line();
    exit_spoiler();
}

// Alola Ratatta
void    alolaRat(void) {
    u32 offset = 0x341C87B8;
    WRITEU16(0x0000 + offset, 0x0013);
    WRITEU8(0x0004 + offset, 0x0005);
    WRITEU8(0x0005 + offset, 0x0001);
}


//Sets all in-battle stats to +6 ranks
void    updateBattleStats(void) {
    if (READU32(0x0029A048) != 0xEA0BEE6C)
        xsprintf(statusBattleStats, "Enable  Stat Stages +6");
    else
        xsprintf(statusBattleStats, "Disable Stat Stages +6");
}

void    maxBattleStats(void) {
    u32    offset;
    u32    address;
    static u32  original;

    if (READU32(0x0029A048) != 0xEA0BEE6C) {
        original = READU32(0x0029A048);

        offset = 0x00595A00;
        static const u8    buffer[] =
        {
            0x80, 0x20, 0x9F, 0xE5, 0x0E, 0x00, 0x52, 0xE1,
            0x1D, 0x00, 0x00, 0x1A, 0x1F, 0x00, 0x2D, 0xE9,
            0x74, 0x20, 0x9F, 0xE5, 0xD0, 0x00, 0x94, 0xE5,
            0x04, 0x30, 0x80, 0xE2, 0x1C, 0x40, 0x80, 0xE2,
            0x04, 0x10, 0x93, 0xE4, 0x00, 0x00, 0x51, 0xE3,
            0xEA, 0x21, 0xC1, 0x15, 0xEB, 0x21, 0xC1, 0x15,
            0xEC, 0x21, 0x81, 0x15, 0xF0, 0x21, 0xC1, 0x15,
            0x04, 0x00, 0x53, 0xE1, 0xF7, 0xFF, 0xFF, 0x1A,
            0x2C, 0x00, 0x9D, 0xE5, 0x88, 0x0A, 0x90, 0xE5,
            0x01, 0x0A, 0x80, 0xE2, 0x08, 0x08, 0x90, 0xE5,
            0x0C, 0x00, 0x90, 0xE5, 0x08, 0x00, 0x90, 0xE5,
            0x04, 0x30, 0x80, 0xE2, 0x1C, 0x40, 0x80, 0xE2,
            0x04, 0x10, 0x93, 0xE4, 0x00, 0x00, 0x51, 0xE3,
            0xEA, 0x21, 0xC1, 0x15, 0xEB, 0x21, 0xC1, 0x15,
            0xEC, 0x21, 0x81, 0x15, 0xF0, 0x21, 0xC1, 0x15,
            0x04, 0x00, 0x53, 0xE1, 0xF7, 0xFF, 0xFF, 0x1A,
            0x1F, 0x00, 0xBD, 0xE8, 0x70, 0x11, 0xF4, 0xEA,
            0xA4, 0x77, 0x6E, 0x00, 0x0C, 0x0C, 0x0C, 0x0C
        };

        address = 0x00;
        memcpy((void *)(address + offset), buffer, 0x90);

        WRITEU32(0x0029A048, 0xEA0BEE6C);
    } else {
        WRITEU32(0x0029A048, original);
    }
    updateBattleStats();
    disableCheat(i_maxBattleStats);
}

// 100% Catch rate for Pokemon
void	catch100(void) {
	WRITEU32(0x0059585C, 0xE5D00008);
	WRITEU32(0x00595860, 0xE92D4003);
	WRITEU32(0x00595864, 0xE59D0010);
	WRITEU32(0x00595868, 0xE59F100C);
	WRITEU32(0x0059586C, 0xE1510000);
	WRITEU32(0x00595870, 0x024000F8);
	WRITEU32(0x00595874, 0x058D0010);
	WRITEU32(0x00595878, 0xE8BD8003);
	WRITEU32(0x0059587C, 0x006D839C);
	WRITEU32(0x0048F1E0, 0xEB04199D);
}

// Updates status of cheat in menu
void    updateShiny(void) {
    if (READU32(0x003183EC) == 0xEA00001C)
        xsprintf(statusShiny, "Disable Wild Pokemon Shiny");
    else
        xsprintf(statusShiny, "Enable  Wild Pokemon Shiny");
}


// Make wild Pokemon shiny. Activate with START+L and deactivate with START+R
void	shinyPokemon(void) {
	if (READU32(0x003183EC) == 0xEA00001C)
		WRITEU32(0x003183EC, 0x0A00001C);
    else
        WRITEU32(0x003183EC, 0xEA00001C);
    updateShiny();
    disableCheat(i_shinyPokemon);
}


// Use Z-Moves without the need of a Z-Crystal
void    zMoves(void) {
    u32 offset = 0x00595900;
    u32 address = 0x00;

    static const u8    buffer[] =
    {
        0x05, 0x40, 0x2D, 0xE9, 0x06, 0x00, 0xA0, 0xE1,
        0x00, 0x00, 0x00, 0xEA, 0x05, 0x40, 0x2D, 0xE9,
        0x50, 0x20, 0x9D, 0xE5, 0x0C, 0x10, 0x9F, 0xE5,
        0x02, 0x00, 0x51, 0xE1, 0xB4, 0x10, 0xD5, 0x01,
        0x00, 0x10, 0xA0, 0x11, 0x05, 0x80, 0xBD, 0xE8,
        0x28, 0xBA, 0x78, 0x00
    };

    memcpy((void *)(address + offset), buffer, 0x2C);

    if (READU32(0x0036D0EC) != 0xE3A00001) {
        WRITEU32(0x00313DC0, 0xEB0A06CE);
        WRITEU32(0x00313E30, 0xEB0A06B5);
        WRITEU32(0x0036D0EC, 0xE3A00001);
    } else {
        WRITEU32(0x00313DC0, 0xE1D510B4);
        WRITEU32(0x00313E30, 0xE1D510B4);
        WRITEU32(0x0036D0EC, 0xE3A00000);
    }

    updateZMove();
    disableCheat(i_zMoves);
}


// Updates menu text for Z-Move cheat
void    updateZMove(void) {
    if (READU32(0x0036D0EC) != 0xE3A00001)
        xsprintf(statusZMove, "Enable  Z-Moves w/o Z-Crystal");
    else
        xsprintf(statusZMove, "Disable Z-Moves w/o Z-Crystal");
}
