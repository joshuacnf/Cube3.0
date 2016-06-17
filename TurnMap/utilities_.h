#ifndef utilities_h
#define utilities_h

#include "globals_.h"
#include "cube_.h"
#include <cstring>
#include <cstdlib>

//////////////////////////////FUNCTIONS/////////////////////////////

inline void turnCube(cube *C, ui i)
{
    switch (i)
    {
        case 0: C->F(); break;
        case 1: C->B(); break;
        case 2: C->U(); break;
        case 3: C->D(); break;
        case 4: C->L(); break;
        case 5: C->R(); break;
        case 6: C->F_(); break;
        case 7: C->B_(); break;
        case 8: C->U_(); break;
        case 9: C->D_(); break;
        case 10: C->L_(); break;
        case 11: C->R_(); break;
        case 12: C->FF(); break;
        case 13: C->BB(); break;
        case 14: C->UU(); break;
        case 15: C->DD(); break;
        case 16: C->LL(); break;
        case 17: C->RR(); break;
        default: break;
    }
}

//////////////////////////////DATA STRUCTURES/////////////////////////////


#endif /* utilities_h */
