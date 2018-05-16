#ifndef _DEF_H
#define _DEF_H

#include <jo/jo.h>

/**DEF**/
//Controls
#define KEY_PRESS(id, key)  ((Smpc_Peripheral[id].data & key) == 0)
#define KEY_DOWN(id, key)   ((Smpc_Peripheral[id].push & key) == 0)

//Display
#define draw_distance (1280*10)



extern Sint32 framerate;

typedef struct
{
    FIXED position[XYZ];
    Uint16 id;
    FIXED rotationIncrement[XYZ];
    ANGLE rotation[XYZ];
    FIXED speed[XYZ];
    FIXED speedIncrement;
    jo_camera cam;
} _player;

extern _player player1;

//Main
void reset_player(_player * currentPlayer);

//Controls
void mypad();

//Display
void	draw(_player * currentPlayer);
void    init_display();

//VDP2
void	init_vdp2();

#endif // _DEF_H
