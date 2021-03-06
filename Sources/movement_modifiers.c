// Filename: movement_modifiers.c

#include "cheats.h"
#include "hid.h"

/********************************
*				*
*	Movement Modifiers	*
*				*
********************************/

int i_walkThruWalls;


// Movement menu entry
void    movementMenu(void) {
    new_spoiler("Movement");
        new_entry("Run Faster", runFaster);
        new_entry("Never Trip", neverTrip);
        i_walkThruWalls = new_entry("Walk Through Walls", walkThruWalls);
        set_note("Activate = Hold R", i_walkThruWalls);
        new_line();
    exit_spoiler();
}


// Increases run speed to 1.375x
void	runFaster(void) {
    WRITEU32(0x0039AF74, 0x3F800000);
    if (is_pressed(BUTTON_B))
		WRITEU32(0x0039AF74, 0x3FB00000);
}


// Disables occational tripping animation
void	neverTrip(void) {
	WRITEU8(0x3419833E, 0x00);
}


// Walk through wall while R is held down
void	walkThruWalls(void) {
    WRITEU32(0x0039D140, 0xEB01E7E7);
    WRITEU32(0x0039D274, 0xEB01E79A);
	if (is_pressed(BUTTON_R)) {
		WRITEU32(0x0039D140, 0xE1A00000);
		WRITEU32(0x0039D274, 0xE1A00000);
	}
}
