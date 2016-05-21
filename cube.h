#ifndef cube_h
#define cube_h

#include "globals.h"

struct cube
{
    ull S, C;
    //side & corner cubies
    
    inline cube(): S(0), C(0)
    {
        for (ull i = 0; i < 12; i++) S |= i << (5 * i);
        for (ull i = 0; i < 8; i++) C |= i << (5 * i);
    }
    
    inline bool solved()
    {
        return S == 0x05a928398a418820ULL &&
                C == 0x000000398a418820ULL;
    }
    
    inline void turn(uc u)
    {
        S = (ull)sM[u][S & MASK20] | ((ull)sM[u][(S >> 20) & MASK20] << 20) | ((ull)sM[u][(S >> 40) & MASK20] << 40);
        C = (ull)cM[u][C & MASK20] | ((ull)cM[u][(C >> 20) & MASK20] << 20);
    }
};

#endif /* cube_h */
